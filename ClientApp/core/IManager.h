#ifndef IMANAGER_H
#define IMANAGER_H

#include <WDASAPI/WDASAPI.h>

#include "IRequest.h"
#include "IResponse.h"

class IManager
{
protected:
	// sends a request via the windows data annotation system api
	virtual DAS_RESULT sendRq(const IRequest* pReq, IResponse** ppRes) = 0;
};

#endif
