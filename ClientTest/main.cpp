#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#else
#ifdef __linux__
typedef int SOCKET
typedef const char * PCSTR
#error This OS is not supported
#else
#error This OS is not supported
#endif
#endif

#include <stdio.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define HOST_NAME "ec2-3-128-7-131.us-east-2.compute.amazonaws.com"
#define MSG_BUFFER_SIZE (size_t)1024

SOCKET OpenConnection(PCSTR hostname, int port)
{
#ifdef _WIN32
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;          // ipv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    int iResult = getaddrinfo(HOST_NAME, "443", &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
#endif
}

SSL_CTX* InitCTX(void)
{
    const SSL_METHOD* method;
    SSL_CTX* ctx;
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = SSLv23_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if (ctx == NULL)
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void ShowCerts(SSL* ssl)
{
    X509* cert;
    char* line;
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if (cert != NULL)
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("Info: No client certificates configured.\n");
}

int main(int count, char* strings[])
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        fprintf(stderr, "WSAStartup failed: %d\n", iResult);
        exit(1);
    }

    SSL_library_init();

#ifdef _DEBUG
    SSL_load_error_strings();
#endif

    SSL_CTX* pCtx = InitCTX();
    SOCKET server = OpenConnection(HOST_NAME, 443);
    SSL* pSsl = SSL_new(pCtx);
    SSL_set_fd(pSsl, server);
    if (SSL_connect(pSsl) == -1)
        ERR_print_errors_fp(stderr);
    else
    {
        ShowCerts(pSsl);

        char clientMsg[] = "hello from client";
        SSL_write(pSsl, clientMsg, sizeof(clientMsg));
        BYTE buf[MSG_BUFFER_SIZE];
        UINT16 nBytes = SSL_read(pSsl, buf, MSG_BUFFER_SIZE);
        buf[nBytes] = 0;
        printf("Recieved %s\n", buf);
        SSL_free(pSsl);
    }

#ifdef _WIN32
    iResult = closesocket(server);
    if (iResult != 0)
    {
        fprintf(stderr, "error closing socket, error: %d\n", iResult);
        exit(1);
    }
#endif

    SSL_CTX_free(pCtx);
    return 0;
}