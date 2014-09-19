#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwTcpIpListener.h"
#include "MwTcpIpConnection.h"

#include "..\..\MwList.h"
#include "..\..\Threading\MwThread.h"
#include "..\..\Threading\MwMutex.h"
#include "..\..\Threading\MwThreadsPool.h"

class MwTcpIpServer;
class MWDLLCLASS MwTcpIpServerConnection
{
public:
	MwTcpIpServer *server;
	MwTcpIpConnection *connection;

	MwTcpIpServerConnection(MwTcpIpServer *server, MwTcpIpConnection *connection);
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwTcpIpConnection*>;

// TODO: Add functionality to ThreadPool (or create separate class) where the number of threads can grow dynamically. This is required to make more, unfixed number of maximum simultaneous connections to the server

class MWDLLCLASS MwTcpIpServer
{
private:
	MwThreadsPool *threadsPool;
	MwMutex *synchronization;

	bool opened;

	static int Listen(void *tcpIpServer);
	static int ConnectionReceive(void *tcpIpConnection);

public:
	MwTcpIpListener *listener;
	MwList<MwTcpIpConnection*> connections;

	bool synchronized;

	MwTcpIpServer(void);
	virtual ~MwTcpIpServer(void);

	// TODO: Make these asynchronous, as well as Client's
	bool Open(int port = 80);
	void Close();

	virtual bool OnAcceptConnection(MwTcpIpConnection *connection);

	virtual void OnConnectionReceive(MwTcpIpConnection *connection, void *data, int dataSize);
	virtual void OnConnectionClose(MwTcpIpConnection *connection);
	virtual void OnConnectionError(MwTcpIpConnection *connection);
};

