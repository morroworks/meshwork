#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwWebRequest.h"

#include "..\..\MwString.h"
#include "..\..\Streams\MwMemoryStream.h"

class MWDLLCLASS MwWebResponse
{
public:
	MwWebRequest *request;
	
	MwString headerCode, headerAppendix, dataType;
	MwMemoryStream *data;
	bool newSession;	

	MwWebResponse(MwWebRequest *request);
	~MwWebResponse(void);
};

