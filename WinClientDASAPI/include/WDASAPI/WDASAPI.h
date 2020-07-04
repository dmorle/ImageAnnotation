#ifndef WDAS_API_H
#define WDAS_API_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <windows.h>

typedef BYTE DAS_RESULT;

#define DAS_RSUCCEEDED(RES) ((DAS_RESULT)((~RES) & 0x80))
#define DAS_RFAILED(RES)    ((DAS_RESULT)(  RES  & 0x80))

DAS_RESULT das_connect();
DAS_RESULT das_disconnect();

DAS_RESULT das_login(PCSTR uname, PCSTR passw);

#ifndef WDAS_API_NOERRORS

#define DAS_ELEVEL(RES)     ((DAS_RESULT)(RES & 0xC0))

#define DAS_RINFO           ((DAS_RESULT)0x00)       // no issues occurred
#define DAS_RWARNING        ((DAS_RESULT)0x40)       // potential issue, in most cases there is no issue
#define DAS_RERROR          ((DAS_RESULT)0x80)       // an error has occurred, the error was non-critical
#define DAS_RCRITICAL       ((DAS_RESULT)0xC0)       // a critical error has occurred, do not continue

#define DAS_RCODE(RES)      ((DAS_RESULT)(RES & 0x3F))

#define DAS_RNOERR          ((DAS_RESULT)0x00)       // no errors have occurred
#define DAS_RUNKWN          ((DAS_RESULT)0x01)       // unknown error
#define DAS_RSYS            ((DAS_RESULT)0x02)       // system error, use errno to diagnose
#define DAS_RMEM            ((DAS_RESULT)0x03)       // out of memory error
#define DAS_RNIMP           ((DAS_RESULT)0x04)       // not implemented error
#define DAS_RDIO            ((DAS_RESULT)0x05)       // disk IO error
#define DAS_RDREAD          ((DAS_RESULT)0x06)       // disk read error
#define DAS_RDWRITE         ((DAS_RESULT)0x07)       // disk write error
#define DAS_RSIO            ((DAS_RESULT)0x08)       // socket IO error
#define DAS_RSREAD          ((DAS_RESULT)0x09)       // socket read error
#define DAS_RSWRITE         ((DAS_RESULT)0x0A)       // socket write error
#define DAS_RFINV           ((DAS_RESULT)0x0B)       // invalid file type
#define DAS_RBUF            ((DAS_RESULT)0x0C)       // buffer overflow
#define DAS_RUSUP           ((DAS_RESULT)0x0D)       // unsupported data type or operation
#define DAS_RUINIT          ((DAS_RESULT)0x0E)       // attempted to access uninitialized memory

#define DAS_ROK	            DAS_RINFO | DAS_RNOERR   // everything went well

#endif // WDAS_API_NOERRORS

#ifdef _WDAS_API_SOURCE

#ifdef _WDAS_API_SOURCE_IREQUEST
// internal request interface

enum DAS_Action
{
	DAS_LOGIN,
	DAS_PUT,
	DAS_GET,
	DAS_CREATE,
	DAS_DELETE,
	DAS_LIST
};

enum DAS_Element
{
	DAS_USER,
	DAS_STREAM,
	DAS_JOB,
	DAS_DATA,
	DAS_PIPELINE,
	DAS_MODEL,
	DAS_SALIENCE
};

DAS_RESULT sendRaw(const BYTE* pBuf, int n);
DAS_RESULT sendHeader(enum DAS_Action, enum DAS_Element);

DAS_RESULT sendUserInfo(PCSTR uname, PCSTR passw);

#endif // _WDAS_API_IREQUEST_SOURCE

#ifdef _WDAS_API_SOURCE_IRESPONSE
// internal response interface

int getRaw(BYTE* pBuf, int n);

#endif // _WDAS_API_IRESPONSE_SOURCE

#endif // _WDAS_API_SOURCE

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WDAS_API_H
