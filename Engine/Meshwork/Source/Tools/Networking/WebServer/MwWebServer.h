#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwWebRequest.h"
#include "MwWebResponse.h"

#include "WebPageComponents\MwWebPageComponent.h"

#include "..\..\MwDictionary.h"
#include "..\TCPIP\MwTcpIpServer.h"

#include "..\..\..\FileSystem\PhysicalFileSystem\MwPhysicalFileSystem.h"


struct WebServerSession
{
	void *data;
	long long time;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwDictionary<unsigned int, WebServerSession*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwWebPageComponent*>;

class MWDLLCLASS MwWebServer :
	public MwTcpIpServer
{
private:
	bool defaultFileSystem;
	MwDictionary<unsigned int, WebServerSession*> sessions;

	void GetSession(MwWebResponse *response);

	void SendResponse(MwWebResponse *response);
	bool GetFileContents(MwWebRequest *request, MwBaseStream *responseContents);
	bool GenerateHtmlContents(MwString requestFile, MwWebRequest *request, MwBaseStream *responseContents);
	
	void GenerateHtmlResponse(MwWebResponse *response, MwString headerCode, MwString headerAppendix, MwString fileName, MwString backupHtmlCode);

public:
	MwFileSystem *fileSystem;
	float sessionDurationSeconds;

	MwString rootPath;

	MwList<MwWebPageComponent*> components;

	MwWebServer(void);
	~MwWebServer(void);

	void OnConnectionReceive(MwTcpIpConnection *connection, void *data, int dataSize);

	// Creates a response with http code 303, which makes the client redirect to the given url
	void Redirect(MwWebResponse *response, MwString url);
	// Creates a response with http code 401, which makes the client ask the user for a user name and a password. The following requests should contain the username and password entered.
	void RequestAuthorization(MwWebResponse *response, MwString message);
	// Creates a response with http code 403, which denotes that the client has been rejected access to the requested resource.
	void Reject(MwWebResponse *response);

	// Sets the file system, which the server is to acquire the requested resources
	void SetFileSystem(MwFileSystem *fileSystem);
	// Sets the root path where the html files are located
	void SetRootPath(MwString rootPath);

	// Registers a component with dynamic page content
	void RegisterComponent(MwWebPageComponent *component, MwString componentName);

	// Ends a session. Next time the user with that session makes a request, a new session will me made. Returns true if a session with the given session id existed, false otherwise
	bool EndSession(unsigned int sessionId);	

	// Provides the ability to reroute the url, which was originally requested by the client.
	// The return value of this method is stored in the MwWebRequest.path, while the originally requested url is stored in MwWebRequest.originalPath
	virtual MwString RerouteRequest(MwString originalUrl);
	// Provides the ability to intercept and "steal" a web request. If this method returns true, then the request will not be futherly processed by the standard pipeline of the web server.
	// It is a convenient place to ask the client for authorization, to redirect, reject or do anything before the standard processing happens
	virtual bool InterceptRequest(MwWebResponse *response);
	// Gets the type of the requested resource outputs it in "responseType". Requested resource is the name of the resource and may include full path. Returns true if the type is found and supported, false otherwise.
	// If this method returns false, normally the web server will return an error that the requested resource is not of supported type.
	virtual bool GetContentType(MwString requestedResource, MwString &responseType);

	// Occurs when a new session is created. The method can be overridden to create an object to hold data for the session and return it as a result.
	virtual void *OnCreateSession(MwWebRequest *request);
	// Occurs when a session is ending. If an object has been created in OnCreateSession, it should be freed here.
	virtual void OnEndSession(void *session);
	
	// Http code 200. Occurs just before the server is to respond to a request. Method parameters hold the data, which is to be used in the response.
	virtual void OnResourceResponse(MwWebResponse *response);
	// Http code 500. Occurs just before the server is to respond that some general error prevents it from performing normally. For example, an error while parsing html code file, or not succeeding to return a resource without any definite cause.
	virtual void OnInternalError(MwWebResponse *response);
	// Http code 404. Occurs just before the server is to responded that a requested resource was not found. Method parameters hold the data, which is to be used in the response.
	virtual void OnResourceNotFound(MwWebResponse *response);
	// Http code 415. Occurs just before the server is to responded that a requested resource is not of a supported type. 
	// This occurs when the requested resource type is not in the server's supportedTypes list or when the GetContentType method returns false for the requested resource. Method parameters hold the data, which is to be used in the response.
	virtual void OnContentTypeNotSupported(MwWebResponse *response);
	// Http code 501. Occurs just before the server is to responded that an HTTP method is not supported by the server. Method parameters hold the data, which is to be used in the response.
	virtual void OnHttpMethodNotImplemented(MwWebResponse *response);
};

