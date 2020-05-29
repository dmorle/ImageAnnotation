#ifndef SERVER_INTERFACE_H
#define SERVER_INTERFACE_H

#ifndef SECURITY_WIN32 
#define SECURITY_WIN32 
#endif

#include <windows.h>
#include <sspi.h>

#ifndef NETWORK_H
#include "../Parameters.h"
#endif

class ServerInterface
{
public:
	ServerInterface(PCSTR pNodeName);

	~ServerInterface();

private:
	// client endpoint
	SOCKET            clientSocket;
	CredHandle        hCred;
	struct _SecHandle hCtxt;

	void handleError(const char *s);
};

#endif
