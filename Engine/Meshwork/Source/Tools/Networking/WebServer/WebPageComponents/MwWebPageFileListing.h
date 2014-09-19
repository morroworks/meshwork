#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwWebPageComponent.h"

class MWDLLCLASS MwWebPageFileListing
	: public MwWebPageComponent
{
public:
	MwWebPageFileListing(void);
	~MwWebPageFileListing(void);

	MwString Output(MwWebRequest *request);
};

