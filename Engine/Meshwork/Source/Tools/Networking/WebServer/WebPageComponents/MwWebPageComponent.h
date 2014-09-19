#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\MwString.h"
#include "..\MwWebRequest.h"

class MwWebServer;

class MWDLLCLASS MwWebPageComponent
{
public:
	MwWebServer *webServer;
	MwString name;

	MwWebPageComponent(void);
	virtual ~MwWebPageComponent(void);

	virtual MwString Output(MwWebRequest *request) = 0;
};

