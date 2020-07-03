#define _WDAS_API_SOURCE
#define _WDAS_API_SOURCE_IREQUEST

#include <WDASAPI/stdafx.h>
#include <WDASAPI/WDASAPI.h>

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

int sendHeader(enum DAS_Action action, enum DAS_Element elem)
{
	BYTE head = 0;

	switch (action)
	{
	case DAS_LOGIN:
		head |= WDASAPI_ACTION_LIN;
		break;
	case DAS_PUT:
		head |= WDASAPI_ACTION_PUT;
		break;
	case DAS_GET:
		head |= WDASAPI_ACTION_GET;
		break;
	case DAS_CREATE:
		head |= WDASAPI_ACTION_CRT;
		break;
	case DAS_DELETE:
		head |= WDASAPI_ACTION_DEL;
		break;
	case DAS_LIST:
		head |= WDASAPI_ACTION_LST;
		break;
	default:
		return DAS_RUSUP | DAS_RERROR;
	}

	switch (elem)
	{
	case DAS_USER:
		head |= WDASAPI_ELEMENT_USR;
		break;
	case DAS_STREAM:
		head |= WDASAPI_ELEMENT_STR;
		break;
	case DAS_JOB:
		head |= WDASPAI_ELEMENT_JOB;
		break;
	case DAS_DATA:
		head |= WDASAPI_ELEMENT_DTA;
		break;
	case DAS_PIPELINE:
		head |= WDASAPI_ELEMENT_PLN;
		break;
	case DAS_MODEL:
		head |= WDASAPI_ELEMENT_MDL;
		break;
	case DAS_SALIENCE:
		head |= WDASAPI_ELEMENT_SAL;
		break;
	default:
		return DAS_RUSUP | DAS_RERROR;
	}

	return sendRaw(&head, 1);
}
