#pragma once

#include "..\..\MeshworkEngine.h"

class MwOpenGL1_1Dispatcher :
	public MwDispatcher
{
public:
	MwOpenGL1_1Dispatcher(void);
	~MwOpenGL1_1Dispatcher(void);
	
	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

