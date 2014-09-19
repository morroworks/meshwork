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

#include "MwTcpIpListener.h"

#include "..\..\MwMem.h"
#include "..\..\MwString.h"

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")


MwTcpIpListener::MwTcpIpListener(void)
{
	this->Initialize();
}

MwTcpIpListener::MwTcpIpListener(int port)
{
	this->Initialize();

	this->Open(port);
}

MwTcpIpListener::~MwTcpIpListener(void)
{
	this->Close();

	delete this->listeningSocket;

	if (this->wsaStarted)
		WSACleanup();
}

void MwTcpIpListener::Initialize()
{
	this->wsaStarted = false;
	this->opened = false;

	this->listeningSocket = new SOCKET;
	*(SOCKET*)this->listeningSocket = INVALID_SOCKET;

    // Initialize Winsock
    WSADATA wsaData;
	int error = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (error != 0) 
	{
		this->wsaStarted = false;
		int errorCode = error;
		this->Close();
    }
	else
		this->wsaStarted = true;
}

bool MwTcpIpListener::Open(int port)
{
	if (!this->wsaStarted)
		return false;

	int error;
	int errorCode; // putting the actual error code here, in case it's eventually needed for some further implementation

    // Resolve the server address and port
	addrinfo *result = NULL;

	addrinfo hints;
	MwMem::Zero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

	error = getaddrinfo(NULL, MwString(port).GetCharContents(), &hints, &result);
    if (error != 0) 
	{
		errorCode = error;
		this->Close();
		return false;
    }

    // Create a SOCKET for connecting to server
    *(SOCKET*)this->listeningSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (*(SOCKET*)this->listeningSocket == INVALID_SOCKET) 
	{
        freeaddrinfo(result);

		errorCode = WSAGetLastError();
		this->Close();
		return false;
    }

    // Setup the TCP listening socket
    error = bind(*(SOCKET*)this->listeningSocket, result->ai_addr, (int)result->ai_addrlen);
    if (error == SOCKET_ERROR) 
	{
		freeaddrinfo(result);

		errorCode = WSAGetLastError();
		this->Close();
		return false;
    }

    freeaddrinfo(result);

    error = listen(*(SOCKET*)this->listeningSocket, SOMAXCONN);
    if (error == SOCKET_ERROR) 
	{
		errorCode = WSAGetLastError();
		this->Close();
		return false;
    }

	// Get the socket's addres, that is the local address
	SOCKADDR_IN addressInfo;
	int addressInfoSize = sizeof(addressInfo);
	if (getsockname(*(SOCKET*)this->listeningSocket, (sockaddr*)&addressInfo, &addressInfoSize) != 0)
	{
		int errorCode = WSAGetLastError();
		return false;
	}
	this->address = inet_ntoa(addressInfo.sin_addr);
	this->port = addressInfo.sin_port;

	this->opened = true;
	
	return true;
}

void MwTcpIpListener::Close()
{
	if (!this->wsaStarted)
		return;
    
	if (*(SOCKET*)this->listeningSocket != INVALID_SOCKET)
	{
		closesocket(*(SOCKET*)this->listeningSocket);
		*(SOCKET*)this->listeningSocket = INVALID_SOCKET;
	}

	WSACleanup();

	this->opened = false;
	this->wsaStarted = false;
}

MwTcpIpConnection *MwTcpIpListener::AcceptConnection()
{
	if (!this->wsaStarted)
		return 0;
    
	SOCKET clientSocket = accept(*(SOCKET*)this->listeningSocket, 0, 0);

	if (clientSocket == INVALID_SOCKET) 
	{
		int errorCode = WSAGetLastError();
		return 0;
    }

	return new MwTcpIpConnection(&clientSocket);
}