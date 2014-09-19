#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Engine\Base\MwDispatcher.h"

class MWDLLCLASS MwObjSceneDispatcher :
	public MwDispatcher
{
public:
	MwObjSceneDispatcher(void);
	~MwObjSceneDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};