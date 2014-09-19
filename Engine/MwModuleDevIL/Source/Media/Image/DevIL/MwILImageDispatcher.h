#pragma once

#include "..\..\..\MeshworkEngine.h"

class MwILImageDispatcher
	: public MwDispatcher
{
public:
	MwILImageDispatcher(void);
	~MwILImageDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

