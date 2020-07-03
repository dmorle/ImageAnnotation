#define _WDAS_API_SOURCE
#define _WDAS_API_SOURCE_IREQUEST
#define _WDAS_API_SOURCE_IRESPONSE

#include <WDASAPI/stdafx.h>
#include <WDASAPI/WDASAPI.h>

#define DEFAULT_HOSTNAME ((PCSTR)"localhost")
#define DEFAULT_PORT ((PCSTR)"8080")

static SOCKET server;
static WSADATA wsaData;

static BOOL wsaInit = FALSE;
static BOOL apiInit = FALSE;

DAS_RESULT das_connect_explicit(PCSTR hostname, PCSTR port)
{
    server = INVALID_SOCKET;
    struct addrinfo
        * result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    // Initialize Winsock
    if (!wsaInit)
    {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            fprintf(stderr, "WSAStartup failed with error: %d\n", iResult);
            return DAS_RSYS | DAS_RCRITICAL;
        }

        wsaInit = TRUE;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(hostname, port, &hints, &result);
    if (iResult != 0) {
        fprintf(stderr, "getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return DAS_RSIO | DAS_RERROR;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        server = socket(
            ptr->ai_family,
            ptr->ai_socktype,
            ptr->ai_protocol
        );
        if (server == INVALID_SOCKET) {
            fprintf(stderr, "socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return DAS_RSIO | DAS_RERROR;
        }

        // Connect to server.
        iResult = connect(server, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            iResult = WSAGetLastError();
            closesocket(server);
            server = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (server == INVALID_SOCKET) {
        fprintf(stderr, "Unable to connect to server!\n");
        WSACleanup();
        return DAS_RSIO | DAS_RERROR;
    }

    return DAS_ROK;
}

DAS_RESULT das_connect_default()
{
    return das_connect_explicit(DEFAULT_HOSTNAME, DEFAULT_PORT);
}

DAS_RESULT das_disconnect()
{
    // shutdown the connection since no more data will be sent
    int iResult = shutdown(server, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        fprintf(stderr, "shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return DAS_RSIO | DAS_RWARNING;
    }

    // cleanup
    closesocket(server);
    WSACleanup();
    return DAS_ROK;
}

int sendRaw(const BYTE* pBuf, int n)
{
    if (!apiInit)
        return DAS_RUINIT | DAS_RERROR;

    // Send an initial buffer
    int iResult = send(server, pBuf, n, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return DAS_RSWRITE | DAS_RERROR;
    }
    return DAS_ROK;
}

int getRaw(BYTE* pBuf, int n)
{
    if (!apiInit)
        return DAS_RUINIT | DAS_RERROR;

    // Retrieve the data
    int iResult = recv(server, pBuf, n, 0);
    if (iResult == SOCKET_ERROR) {
        printf("recv failed with error: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return DAS_RSREAD | DAS_RERROR;
    }
    return DAS_ROK;
}
