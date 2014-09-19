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

#include "MwTcpIpClient.h"

int MwTcpIpClient::ConnectionReceive(void *tcpIpClient)
{
	MwTcpIpClient *client = (MwTcpIpClient*)tcpIpClient;

	const int bufferSize = 4096;
	char buffer[bufferSize];
	bool active = client->connection->opened;
	while (active)
	{
		int bytesReceived = client->connection->Receive(buffer, bufferSize);

		client->synchronization->Lock();

		if (bytesReceived > 0)
		{
			client->OnReceive(buffer, bytesReceived);
		}

		else if (bytesReceived == 0)
		{
			// Connection is closing. OnConnectionClose will be called after this loop
			active = false;
		}

		else
		{
			client->OnError();
			active = false;
		}

		client->synchronization->Unlock();
	}

	client->synchronization->Lock();

	client->OnDisconnected();

	client->synchronization->Unlock();

	return 0;
}

MwTcpIpClient::MwTcpIpClient(void)
{
	this->connected = false;
}


MwTcpIpClient::~MwTcpIpClient(void)
{
	this->Disconnect();
}

bool MwTcpIpClient::Connect(MwString address, int port)
{
	this->connection = new MwTcpIpConnection();
	this->connected = this->connection->Open(address, port);

	this->synchronization = new MwMutex();
	this->thread = new MwThread(MwTcpIpClient::ConnectionReceive, this);

	return this->connected;
}

void MwTcpIpClient::Disconnect()
{
	if (this->connected)
	{
		this->connection->Close();

		this->thread->Wait();

		delete this->thread;
		delete this->synchronization;

		delete this->connection;

		this->connected = false;
	}
}

void MwTcpIpClient::OnConnected()
{
}

void MwTcpIpClient::OnReceive(void *data, int dataSize)
{
}

void MwTcpIpClient::OnDisconnected()
{
}

void MwTcpIpClient::OnError()
{
}
