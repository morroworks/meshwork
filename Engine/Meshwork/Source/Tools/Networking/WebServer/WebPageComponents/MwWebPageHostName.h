#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwWebPageComponent.h"

class MWDLLCLASS MwWebPageHostName
	: public MwWebPageComponent
{
public:
	MwWebPageHostName(void);
	~MwWebPageHostName(void);

	MwString Output(MwWebRequest *request);
};

