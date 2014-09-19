#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Engine\Base\MwDispatcher.h"

class MWDLLCLASS MwNativeSceneDispatcher :
	public MwDispatcher
{
public:
	MwNativeSceneDispatcher(void);
	~MwNativeSceneDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

