#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\MwString.h"

class MwWebServer;
class MwTcpIpConnection;

class MWDLLCLASS MwWebRequest
{
public:
	bool supported;
	MwWebServer *server;
	MwTcpIpConnection *connection;
	MwString fullRequest, path, originalPath, methodName, hostName, 
		authenticationTypeName, authenticationUserName, authenticationUserPassword;
	bool receivedSessionId;
	unsigned int sessionId;
	void *session;

	MwWebRequest(MwWebServer *server, MwTcpIpConnection *connection, MwString requestString);
	~MwWebRequest(void);
};

