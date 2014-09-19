#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Engine\Base\MwDispatcher.h"

class MWDLLCLASS Mw3dsSceneDispatcher :
	public MwDispatcher
{
public:
	Mw3dsSceneDispatcher(void);
	~Mw3dsSceneDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

