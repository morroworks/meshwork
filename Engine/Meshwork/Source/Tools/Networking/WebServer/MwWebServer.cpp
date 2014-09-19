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

#include "MwWebServer.h"

#include "..\..\MwMath.h"
#include "..\..\OS\MwOSUtils.h"
#include "..\..\Streams\MwFileStream.h"
#include "..\..\Streams\MwMemoryStream.h"


MwWebServer::MwWebServer(void)
{
	this->rootPath = MwOSUtils::GetApplicationPath();
	this->synchronized = true;

	this->fileSystem = new MwPhysicalFileSystem();
	this->defaultFileSystem = true;

	this->sessionDurationSeconds = 20 * 60;
}


MwWebServer::~MwWebServer(void)
{
	for (int componentIndex = 0; componentIndex < this->components.count; componentIndex++)
		delete this->components[componentIndex];

	if (this->defaultFileSystem)
		delete this->fileSystem;

	for (void *entry = this->sessions.GetNodeNext(0); entry != 0; entry = this->sessions.GetNodeNext(entry))
	{
		this->OnEndSession(this->sessions.GetNodeValue(entry).value->data);
		delete this->sessions.GetNodeValue(entry).value;
	}
}

void MwWebServer::OnConnectionReceive(MwTcpIpConnection *connection, void *data, int dataSize)
{
	MwWebRequest *request = new MwWebRequest(this, connection, MwString((char*)data, dataSize));
	MwWebResponse *response = new MwWebResponse(request);

	if (request->supported)
	{
		this->GetSession(response);
		
		request->path = this->RerouteRequest(request->originalPath);

		if (!this->InterceptRequest(response))
		{
			if (this->fileSystem->FileExists(this->rootPath + "\\" + request->path))
			{
				if (this->GetContentType(request->path, response->dataType))
				{
					bool resourceAcquired;
					if (response->dataType == "text/html")
					{
						resourceAcquired = this->GenerateHtmlContents(request->path, request, response->data);
					}
					else
					{
						resourceAcquired = this->GetFileContents(request, response->data);
					}

					if (resourceAcquired)
					{
						this->OnResourceResponse(response);
					}
					else
					{
						this->OnInternalError(response);
					}
				}
				else
				{
					this->OnContentTypeNotSupported(response);
				}
			}
			else
			{
				this->OnResourceNotFound(response);
			}
		}
	}
	else
	{
		this->OnHttpMethodNotImplemented(response);
	}

	this->SendResponse(response);

	delete response;
	delete request;
		

	connection->Close();
}

void MwWebServer::Redirect(MwWebResponse *response, MwString url)
{
	this->GenerateHtmlResponse(response, "303 See Other", MwString("Location: ") + url + "\r\n", 
		"Not Imlemented.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>501 - HTTP Method Not Implemented</div></body></html>");
}

void MwWebServer::RequestAuthorization(MwWebResponse *response, MwString message)
{
	this->GenerateHtmlResponse(response, "401 Unauthorized", MwString("WWW-Authenticate: basic realm=\"") + message + "\"\r\n", 
		"Unauthorized.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>401 - Unauthorized</div></body></html>");
}

void MwWebServer::Reject(MwWebResponse *response)
{
	this->GenerateHtmlResponse(response, "403 Forbidden", "", 
		"Rejected.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>403 - Rejected</div></body></html>");
}


void MwWebServer::SetFileSystem(MwFileSystem *fileSystem)
{
	if (this->defaultFileSystem)
	{
		delete this->fileSystem;
		this->defaultFileSystem = false;
	}

	this->fileSystem = fileSystem;
}

void MwWebServer::SetRootPath(MwString rootPath)
{
	if (MwFileSystem::IsAbsolutePath(rootPath))
		this->rootPath = rootPath;
	else
		this->rootPath = MwFileSystem::MergePaths(MwOSUtils::GetApplicationPath(), rootPath);
}

void MwWebServer::RegisterComponent(MwWebPageComponent *component, MwString componentName)
{
	this->components.Add(component);
	component->webServer = this;
	component->name = componentName;
}

void MwWebServer::GetSession(MwWebResponse *response)
{
	// TODO: Tidy up this ugly method. Refine cookie management (as well as the session cookie)

	long long time = MwOSUtils::GetPerformanceCounter();
	long long freq = MwOSUtils::GetPerformanceCounterFrequency();

	// Find if there is such session already and whether it has not timed out
	WebServerSession *session;
	if (response->request->receivedSessionId && this->sessions.GetValue(response->request->sessionId, session))
	{
		if (((float)(time - session->time) / (float)freq) < this->sessionDurationSeconds)
		{
			session->time = time;
			response->request->session = session->data;
			response->newSession = false;
			return;
		}
	}

	// Remove any timed-out sessions. TODO: ?This can also be done in a background thread
	void *entry = this->sessions.GetNodeNext(0);
	while (entry != 0)
	{
		void *current = entry;
		entry = this->sessions.GetNodeNext(entry);
		WebServerSession *session = this->sessions.GetNodeValue(current).value;
		if (((float)(time - session->time) / (float)freq) >= this->sessionDurationSeconds)
		{
			this->OnEndSession(session->data);
			delete session;
			this->sessions.RemoveNode(current);
		}
	}

	// Add a new session
	do
	{
		response->request->sessionId = MwMath::Random(MwMath::IntMax) ^ (unsigned int)(MwOSUtils::GetPerformanceCounter());
	}
	while (this->sessions.KeyExists(response->request->sessionId));

	response->request->session = this->OnCreateSession(response->request);

	WebServerSession *newSession = new WebServerSession();
	newSession->data = response->request->session;
	newSession->time = time;
	
	this->sessions.Add(response->request->sessionId, newSession);

	response->newSession = true;
}

MwString MwWebServer::RerouteRequest(MwString originalUrl)
{
	originalUrl = originalUrl.Trim('\\', false, true);

	if ((originalUrl.length == 0) || this->fileSystem->DirectoryExists(this->rootPath + "\\" + originalUrl))
	{
		if (this->fileSystem->FileExists(this->rootPath + "\\index.html"))
			return MwString("index.html");

		if (this->fileSystem->FileExists(this->rootPath + "\\index.htm"))
			return MwString("index.htm");
	}

	return MwString(originalUrl);
}

bool MwWebServer::EndSession(unsigned int sessionId)
{
	WebServerSession *session;
	if (!this->sessions.GetValue(sessionId, session))
		return false;

	this->OnEndSession(session->data);

	delete session;

	this->sessions.Remove(sessionId);

	return true;
}

bool MwWebServer::InterceptRequest(MwWebResponse *response)
{
	return false;
}

bool MwWebServer::GetContentType(MwString requestedResource, MwString &responseType)
{
	int extensionTextStart = requestedResource.LastIndexOf(".") + 1;
	MwString requestedResourceExtension = requestedResource.SubString(extensionTextStart, requestedResource.length - extensionTextStart).ToLower();

	const int numSupportedExtensions = 11;
	const char *extensions[numSupportedExtensions][2] =
	{ 
		{ "htm", "text/html" },
		{ "html", "text/html" },
		{ "css", "text/css" },
		{ "xml", "application/xml" },
		{ "txt", "text/plain" },
		{ "jpg", "image/jpeg" },
		{ "jpeg", "image/jpeg" },
		{ "png", "image/png" },
		{ "gif", "image/gif" },
		{ "ico", "image/x-icon" },
		{ "zip", "application/zip"}
	};

	for (int i = 0; i < numSupportedExtensions; i++)
	{
		if (requestedResourceExtension.Equals(extensions[i][0]))
		{
			responseType = extensions[i][1];
			return true;
		}
	}

	//responseType = "application/octet-stream";
	//return true;

	return false;
}


void *MwWebServer::OnCreateSession(MwWebRequest *request)
{
	return new MwString();
}

void MwWebServer::OnEndSession(void *session)
{
	MwString *s = (MwString*)session;
	delete s;
}

void MwWebServer::OnResourceResponse(MwWebResponse *response)
{
	MwString responseType;
	if (this->GetContentType(response->request->path, responseType))
		if (responseType.Equals("text/html"))
		{
			MwString *s = (MwString*)(response->request->session);
			if (MwMath::Random(5) == 0)
				response->request->server->EndSession(response->request->sessionId);
			else
				s->Insert(response->request->path);
		}


	
	response->headerCode = "200 OK";
}

void MwWebServer::OnInternalError(MwWebResponse *response)
{
	this->GenerateHtmlResponse(response, "500 Internal Server Error", "", 
		"Internal Error.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>500 - Internal Server Error</div></body></html>");
}

void MwWebServer::OnResourceNotFound(MwWebResponse *response)
{
	this->GenerateHtmlResponse(response, "404 Not Found", "", 
		"Not Found.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>404 - Not Found</div></body></html>");
}

void MwWebServer::OnContentTypeNotSupported(MwWebResponse *response)
{
	this->GenerateHtmlResponse(response, "415 Unsupported Media Type", "", 
		"Not Supported.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>415 - Unsupported Media Type</div></body></html>");
}

void MwWebServer::OnHttpMethodNotImplemented(MwWebResponse *response)
{
	this->GenerateHtmlResponse(response, "501 Not Implemented", "", 
		"Not Imlemented.html",
		"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Meshwork Web Server</h2><div>501 - HTTP Method Not Implemented</div></body></html>");
}


void MwWebServer::SendResponse(MwWebResponse *response)
{
	MwString header = MwString("HTTP/1.1 ") + response->headerCode + "\r\nServer: Meshwork Web Server\r\nContent-Type: " + response->dataType + "\r\nContent-Length: " + MwString(response->data->length) + "\r\n" + response->headerAppendix;
	if (response->newSession)
		header += MwString("Set-Cookie: ") + "mwsession=" + MwString(response->request->sessionId) + "; HttpOnly\r\n";
	header += "Connection: close\r\n\r\n";
	response->request->connection->Send(header.GetCharContents(), header.length);
	if (response->data->length > 0)
	{
		char *data = new char[(int)response->data->length];
		response->data->Seek(0);
		response->data->ReadData(data, response->data->length);
		response->request->connection->Send(data, (int)response->data->length);
		delete[] data;
	}
}

void MwWebServer::GenerateHtmlResponse(MwWebResponse *response, MwString headerCode, MwString headerAppendix, MwString fileName, MwString backupHtmlCode)
{
	response->headerCode = headerCode;
	response->dataType = "text/html";
	response->headerAppendix = headerAppendix;
	if (!this->GenerateHtmlContents(fileName, response->request, response->data))
	{
		response->data->WriteData(backupHtmlCode.GetCharContents(), backupHtmlCode.length);
	}
}

bool MwWebServer::GetFileContents(MwWebRequest *request, MwBaseStream *responseContents)
{
	MwString fileName = this->rootPath + "\\" + request->path;

	if (!this->fileSystem->FileExists(fileName))
		return false;

	MwFileStream fileData(fileName.contents, FileStreamAccessMode_Read);
	responseContents->WriteStreamData(fileData);

	return true;
}

bool MwWebServer::GenerateHtmlContents(MwString requestFile, MwWebRequest *request, MwBaseStream *responseContents)
{
	MwString fileName = this->rootPath + "\\" + requestFile;

	if (!this->fileSystem->FileExists(fileName))
		return false;

	MwFileStream codeStream(fileName.contents, FileStreamAccessMode_Read);

	char *sourceData = new char[(unsigned int)codeStream.length + 1];
	codeStream.ReadData(sourceData, codeStream.length);
	sourceData[codeStream.length] = 0;
	MwString source(sourceData);
	delete[] sourceData;

	MwString output;

	// TODO: Real parsing of html

	int parsedIndex = 0;
	while (parsedIndex < source.length)
	{
		int mwwTagStart = source.IndexOf("<mww", parsedIndex);
		int mwwTagEnd = -1;
		if (mwwTagStart != -1)
		{
			int classNameStart = source.IndexOf("component=\"", mwwTagStart + 5);
			if (classNameStart != -1)
			{
				classNameStart += 11;
				int classNameEnd = source.IndexOf("\"", classNameStart);
				if (classNameEnd != -1)
				{
					mwwTagEnd = source.IndexOf("/>", mwwTagStart);
					if (mwwTagEnd != -1)
						mwwTagEnd += 2;
					else
					{
						mwwTagEnd = source.IndexOf("</mww>", mwwTagStart);
						if (mwwTagEnd != -1)
							mwwTagEnd += 6;
					}

					if (mwwTagEnd != -1)
					{
						output += source.SubString(parsedIndex, mwwTagStart - parsedIndex);
						parsedIndex = mwwTagEnd;

						MwString className = source.SubString(classNameStart, classNameEnd - classNameStart);
						
						int componentIndex = this->components.count - 1;
						for (; componentIndex >= 0; componentIndex--)
							if (this->components[componentIndex]->name.Equals(className))
								break;

						if (componentIndex != -1)
						{
							MwString s = this->components[componentIndex]->Output(request);
							output += s;
						}
					}
				}
			}
		}

		if (mwwTagEnd == -1)
		{
			output += source.SubString(parsedIndex, source.length - parsedIndex);
			parsedIndex = source.length;
		}
	}
	
	responseContents->WriteData((void*)output.GetCharContents(), output.length);

	return true;
}
