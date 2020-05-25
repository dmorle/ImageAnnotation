#include "ServerInterface.h"

#define BUFFER_SIZE 1024

#ifndef SECURITY_WIN32 
#define SECURITY_WIN32 
#endif

#include "sspiUtil.h"



ServerInterface::ServerInterface(PCSTR pNodeName)
{
    BYTE              Data[BIG_BUFF];
    PCHAR             pMessage;
    WSADATA           wsaData;
    SECURITY_STATUS   ss;
    DWORD             cbRead;
    ULONG             cbMaxSignature;
    ULONG             cbSecurityTrailer;
    SecPkgContext_Sizes            SecPkgContextSizes;
    SecPkgContext_NegotiationInfo  SecPkgNegInfo;
    BOOL DoAuthentication(SOCKET s);

    //-------------------------------------------------------------------
    //  Initialize the socket and the SSP security package.

    if (WSAStartup(0x0101, &wsaData))
        handleError("Could not initialize winsock ");

    //--------------------------------------------------------------------
    //  Connect to a server.

    if (!ConnectAuthSocket(&clientSocket, &hCred, &hCtxt))
        handleError("Authenticated server connection ");

    //--------------------------------------------------------------------
    //   An authenticated session with a server has been established.
    //   Receive and manage a message from the server.
    //   First, find and display the name of the negotiated
    //   SSP and the size of the signature and the encryption 
    //   trailer blocks for this SSP.

    ss = QueryContextAttributes(&hCtxt, SECPKG_ATTR_NEGOTIATION_INFO, &SecPkgNegInfo);

    if (!SEC_SUCCESS(ss))
        handleError("QueryContextAttributes failed ");
    else
        printf("Package Name: %s\n", SecPkgNegInfo.PackageInfo->Name);

    ss = QueryContextAttributes(
        &hCtxt,
        SECPKG_ATTR_SIZES,
        &SecPkgContextSizes);

    if (!SEC_SUCCESS(ss))
        handleError("Query context ");

    cbMaxSignature = SecPkgContextSizes.cbMaxSignature;
    cbSecurityTrailer = SecPkgContextSizes.cbSecurityTrailer;

    printf("InitializeSecurityContext result = 0x%08x\n", ss);

    if (!ReceiveBytes(clientSocket, Data, BIG_BUFF, &cbRead))
        handleError("No response from server ");

    if (cbRead == 0)
        handleError("Zero bytes received ");

    pMessage = (PCHAR)DecryptThis(Data, &cbRead, &hCtxt, cbSecurityTrailer);

    printf("The message from the server is \n ->  %.*s \n", cbRead, pMessage);
}

ServerInterface::~ServerInterface()
{
    //--------------------------------------------------------------------
    //  Terminate socket and security package.

    DeleteSecurityContext(&hCtxt);
    FreeCredentialHandle(&hCred);
    shutdown(clientSocket, 2);
    closesocket(clientSocket);
    if (SOCKET_ERROR == WSACleanup())
        handleError("Problem with socket cleanup ");
}

void ServerInterface::handleError(const char *s)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s error. Exiting.\n", s);

    MessageBoxA(Parameters::hwnd, buffer, "Critical Error", MB_OK | MB_ICONERROR);
    
    exit(EXIT_FAILURE);
}
