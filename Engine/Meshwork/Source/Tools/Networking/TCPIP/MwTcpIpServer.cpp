//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwTcpIpServer.h"

MwTcpIpServerConnection::MwTcpIpServerConnection(MwTcpIpServer *server, MwTcpIpConnection *connection)
{
	this->server = server;
	this->connection = connection;
}

int MwTcpIpServer::Listen(void *tcpIpServer)
{
	MwTcpIpServer *server = (MwTcpIpServer*)tcpIpServer;

	while (server->opened)
	{
		MwTcpIpConnection *connection = server->listener->AcceptConnection();

		if (connection == 0)
			return 0;

		bool synchronized = server->synchronized;
		if (synchronized)
			server->synchronization->Lock();

		if (server->OnAcceptConnection(connection))
		{
			server->connections.Add(connection);
			server->threadsPool->QueueTask(MwTcpIpServer::ConnectionReceive, new MwTcpIpServerConnection(server, connection));
		}
		else
		{
			delete connection;
		}

		if (synchronized)
			server->synchronization->Unlock();
	}


	return 0;
}

int MwTcpIpServer::ConnectionReceive(void *tcpIpServerConnection)
{
	MwTcpIpServerConnection *serverConnection = (MwTcpIpServerConnection*)tcpIpServerConnection;

	const int bufferSize = 4096;
	char buffer[bufferSize];
	bool active = serverConnection->connection->opened;
	while (active)
	{
		int bytesReceived = serverConnection->connection->Receive(buffer, bufferSize);

		bool synchronized = serverConnection->server->synchronized;
		if (synchronized)
			serverConnection->server->synchronization->Lock();

		if (bytesReceived > 0)
		{
			serverConnection->server->OnConnectionReceive(serverConnection->connection, buffer, bytesReceived);
		}

		else if (bytesReceived == 0)
		{
			// Connection is closing. OnConnectionClose will be called after this loop
			active = false;
		}

		else
		{
			serverConnection->server->OnConnectionError(serverConnection->connection);
			active = false;
		}

		if (synchronized)
			serverConnection->server->synchronization->Unlock();
	}

	bool synchronized = serverConnection->server->synchronized;
	if (synchronized)
		serverConnection->server->synchronization->Lock();

	serverConnection->server->OnConnectionClose(serverConnection->connection);

	serverConnection->server->connections.Remove(serverConnection->connection);
	serverConnection->connection->Close();
	delete serverConnection->connection;

	if (synchronized)
		serverConnection->server->synchronization->Unlock();

	delete serverConnection;


	return 0;
}

MwTcpIpServer::MwTcpIpServer(void)
{
	this->synchronized = false;

	this->synchronization = 0;
	this->threadsPool = 0;
	
	this->listener = 0;

	this->opened = false;
}

MwTcpIpServer::~MwTcpIpServer(void)
{
	this->Close();
}

bool MwTcpIpServer::Open(int port)
{
	this->synchronization = new MwMutex();
	this->threadsPool = new MwThreadsPool(4);
	
	this->listener = new MwTcpIpListener();
	this->opened = this->listener->Open(port);

	this->threadsPool->QueueTask(MwTcpIpServer::Listen, this);

	return this->opened;
}

void MwTcpIpServer::Close()
{
	if (this->opened)
	{
		// Close all active connections
		for (int i = 0; i < this->connections.count; i++)
			this->connections[i]->Close();

		// Close listener
		this->listener->Close();

		// Wait for all to finalize
		this->threadsPool->WaitAll();
		
		delete this->listener;
		delete this->threadsPool;
		delete this->synchronization;

		this->opened = false;
	}
}

bool MwTcpIpServer::OnAcceptConnection(MwTcpIpConnection *connection)
{
	return true;
}

void MwTcpIpServer::OnConnectionReceive(MwTcpIpConnection *connection, void *data, int dataSize)
{
}

void MwTcpIpServer::OnConnectionClose(MwTcpIpConnection *connection)
{
}

void MwTcpIpServer::OnConnectionError(MwTcpIpConnection *connection)
{
}
