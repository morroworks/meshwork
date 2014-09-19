#pragma once

#include "..\..\MeshworkEngine.h"

class MwOpenALDispatcher :
	public MwDispatcher
{
public:
	MwOpenALDispatcher(void);
	~MwOpenALDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

