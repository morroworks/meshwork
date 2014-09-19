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

#include "MwWebRequest.h"

#include "MwWebServer.h"
#include "..\TCPIP\MwTcpIpConnection.h"
#include "..\..\MwStrings.h"

MwWebRequest::MwWebRequest(MwWebServer *server, MwTcpIpConnection *connection, MwString requestString)
{
	// TODO: Parsing of request

	this->server = server;
	this->connection = connection;

	this->fullRequest = requestString;

	MwStrings requestLines;
	requestLines.SplitString(requestString, "\r\n");

	MwList<MwStrings*> tokens;
	MwStrings linesHeaders;
	for (int lineIndex = 0; lineIndex < requestLines.count; lineIndex++)
	{
		MwStrings *lineTokens = new MwStrings();
		lineTokens->SplitString(requestLines[lineIndex], " ");
		linesHeaders.Add((*lineTokens)[0].ToLower());
		tokens.Add(lineTokens);
	}

	
	this->methodName = (*tokens[0])[0];

	if (this->methodName.Equals("GET") || this->methodName.Equals("POST"))
	{
		this->supported = true;

		this->originalPath = (*tokens[0])[1].Trim('/', false, true).Replace("/", "\\").Replace("%20", " ").Remove("\\..");

		int hostNameIndex = linesHeaders.IndexOf(MwString("host:"), StringComparison_CaseInsensitive);
		if (hostNameIndex != -1)
			this->hostName = (*tokens[hostNameIndex])[1];

		int authorizationTypeIndex = linesHeaders.IndexOf(MwString("authorization:"), StringComparison_CaseInsensitive);
		if (authorizationTypeIndex != -1)
		{
			this->authenticationTypeName = (*tokens[authorizationTypeIndex])[1];
			MwStrings userAndPass;
			userAndPass.SplitString((*tokens[authorizationTypeIndex])[2].FromBase64(), MwString(":"));
			this->authenticationUserName = userAndPass[0];
			this->authenticationUserPassword = userAndPass[1];
		}

		this->sessionId = -1;
		this->receivedSessionId = false;
		int cookiesLineIndex = linesHeaders.IndexOf(MwString("cookie:"), StringComparison_CaseInsensitive);
		if (cookiesLineIndex != -1)
		{
			for (int cookieIndex = 1; cookieIndex < (*tokens[cookiesLineIndex]).count; cookieIndex++)
			{
				MwStrings cookie;
				cookie.SplitString((*tokens[cookiesLineIndex])[cookieIndex].Trim(';'), '=');
				if (cookie.count == 2)
				{
					if (cookie[0].Trim(' ').Equals("mwsession"))
					{
						 cookie[1].Trim(' ').ToUInt(this->sessionId);
						 this->receivedSessionId = true;
					}
				}
			}
		}
	}
	else
		this->supported = false;

	for (int lineIndex = 0; lineIndex < tokens.count; lineIndex++)
		delete tokens[lineIndex];
}


MwWebRequest::~MwWebRequest(void)
{
}
