#ifndef WDAS_API_H
#define WDAS_API_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <windows.h>

BOOL das_connect(PCSTR hostname, PCSTR port);
BOOL das_connect();

BOOL das_disconnect();

BOOL das_login(PCSTR uname, PCSTR passw);

#ifdef _DAS_API_SOURCE
// internal functions for the data annotation system api

int sendRaw(BYTE* pBuf, SIZE_T n);
int getRaw(BYTE* pBuf, SIZE_T n);

#ifdef _DAS_API_SOURCE_IREQUEST
// internal request interface

#define WDASAPI_ACTION      0xE0  // [6, 8]
#define WDASAPI_ACTION_LIN  0x00  // 0 >> 5 -- login
#define WDASAPI_ACTION_PUT  0x20  // 1 >> 5 -- put
#define WDASAPI_ACTION_GET  0x40  // 2 >> 5 -- get
#define WDASAPI_ACTION_CRT  0x60  // 3 >> 5 -- create
#define WDASAPI_ACTION_DEL  0x80  // 4 >> 5 -- delete
#define WDASAPI_ACTION_LST  0xA0  // 5 >> 5 -- list

#define WDASAPI_ELEMENT     0x1F  // [1, 5]
#define WDASAPI_ELEMENT_USR 0x00  // 0 -- user
#define WDASAPI_ELEMENT_STR 0x01  // 1 -- stream
#define WDASPAI_ELEMENT_JOB 0x02  // 2 -- job
#define WDASAPI_ELEMENT_DTA 0x03  // 3 -- data
#define WDASAPI_ELEMENT_PLN 0x04  // 4 -- pipeline
#define WDASAPI_ELEMENT_MDL 0x05  // 5 -- model
#define WDASAPI_ELEMENT_SAL 0x06  // 6 -- salience detection

#endif // _DAS_API_SOURCE_IREQUEST

#ifdef _DAS_API_SOURCE_IRESPONSE
// internal response interface

#endif // _DAS_API_SOURCE_IRESPONSE

#endif // _DAS_API_SOURCE

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WDAS_API_H
