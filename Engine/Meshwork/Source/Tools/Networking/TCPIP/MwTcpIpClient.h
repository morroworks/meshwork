#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwTcpIpConnection.h"

#include "..\..\Threading\MwThread.h"
#include "..\..\Threading\MwMutex.h"

class MWDLLCLASS MwTcpIpClient
{
private:
	static int ConnectionReceive(void *tcpIpClient);

	MwThread *thread;
	MwMutex *synchronization;

public:
	bool connected;
	MwTcpIpConnection *connection;

	MwTcpIpClient(void);
	~MwTcpIpClient(void);

	// TODO: Make these asynchronous, as well as Server's
	// Connects to a server. Returns true if succeeds or false otherwise
	bool Connect(MwString address, int port = 80);
	// Disconnects from a server
	void Disconnect();

	// Occurs when the client has successfully connected to a server
	virtual void OnConnected();

	// Occurs when the client has received data from the server
	virtual void OnReceive(void *data, int dataSize);
	// Occurs when the client has disconnected from the server
	virtual void OnDisconnected();
	// Occurs when there was an error with the connection
	virtual void OnError();
};

