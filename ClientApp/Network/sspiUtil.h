#ifndef SSPI_UTIL_H
#define SSPI_UTIL_H

#define BIG_BUFF   2048
#define SEC_SUCCESS(Status) ((Status) >= 0)

#ifndef SECURITY_WIN32 
#define SECURITY_WIN32 
#endif

#include <windows.h>
#include <sspi.h>

BOOL SendMsg(SOCKET s, PBYTE pBuf, DWORD cbBuf);
BOOL ReceiveMsg(SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD* pcbRead);
BOOL SendBytes(SOCKET s, PBYTE pBuf, DWORD cbBuf);
BOOL ReceiveBytes(SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD* pcbRead);

BOOL GenClientContext(
    BYTE* pIn,
    DWORD cbIn,
    BYTE* pOut,
    DWORD* pcbOut,
    BOOL* pfDone,
    CHAR* pszTarget,
    CredHandle* hCred,
    struct _SecHandle* hcText
);

BOOL EncryptThis(
    PBYTE pMessage,
    ULONG cbMessage,
    BYTE** ppOutput,
    LPDWORD pcbOutput,
    ULONG securityTrailer
);

PBYTE DecryptThis(
    PBYTE achData,
    LPDWORD pcbMessage,
    struct _SecHandle* hCtxt,
    ULONG   cbSecurityTrailer
);

BOOL SignThis(
    PBYTE pMessage,
    ULONG cbMessage,
    BYTE** ppOutput,
    LPDWORD pcbOutput
);

PBYTE VerifyThis(
    PBYTE pBuffer,
    LPDWORD pcbMessage,
    struct _SecHandle* hCtxt,
    ULONG   cbMaxSignature
);

void PrintHexDump(DWORD length, PBYTE buffer);

BOOL ConnectAuthSocket(
    SOCKET* s,
    CredHandle* hCred,
    struct _SecHandle* hcText
);

BOOL DoAuthentication(SOCKET s);

void MyHandleError(char* s);

#endif
