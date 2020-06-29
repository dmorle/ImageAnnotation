#include "pch.h"
#include "DASAPI.h"

#define HOSTNAME "localhost"
#define DEFAULT_PORT "8080"

static SOCKET server;

BOOL connect()
{
    WSADATA wsaData;
    server = INVALID_SOCKET;
    struct addrinfo
        * result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", iResult);
        return FALSE;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(HOSTNAME, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        fprintf(stderr, "getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return FALSE;
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
            return FALSE;
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
        return FALSE;
    }

    return TRUE;
}

BOOL sendRaw(const char* pBuf, SIZE_T n)
{
    // Send an initial buffer
    int iResult = send(server, pBuf, n, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return FALSE;
    }
    return TRUE;
}

int getRaw(char* pBuf, SIZE_T n)
{
    // Retrieve the data
    int iResult = recv(server, pBuf, n, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
    }
    return iResult;
}

BOOL disconnect()
{
    // shutdown the connection since no more data will be sent
    int iResult = shutdown(server, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        fprintf(stderr, "shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return FALSE;
    }

    // cleanup
    closesocket(server);
    WSACleanup();
    return TRUE;
}

BOOL login(PCSTR uname, PCSTR passw)
{
    return FALSE;
}
