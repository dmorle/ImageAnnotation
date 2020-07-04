#define _WDAS_API_SOURCE
#define _WDAS_API_SOURCE_IREQUEST

#include <WDASAPI/stdafx.h>
#include <WDASAPI/WDASAPI.h>

#define UINFO_BUF 256

DAS_RESULT sendUserInfo(PCSTR uname, PCSTR passw)
{
	char buf[UINFO_BUF];
	char* pC,* pBuf = buf;

	for (pC = uname; *pC != 0; pC++)
		*pBuf++ = *pC++;
	*pBuf++ = 0;

	for (pC = uname; *pC != 0; pC++)
		*pBuf++ = *pC++;
	*pBuf++ = 0;

	return sendRaw(buf, pBuf - buf + 1);
}

DAS_RESULT das_login(PCSTR uname, PCSTR passw)
{
	DAS_RESULT dr = sendHeader(DAS_LOGIN, DAS_USER);

	if (DAS_RSUCCEEDED(dr))
		dr = sendUserInfo(uname, passw);

	return dr;
}
