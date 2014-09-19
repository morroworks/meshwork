#pragma once

#include "..\..\..\MeshworkEngine.h"

class MwOGGVorbisSoundMediaDispatcher :
	public MwDispatcher
{
public:
	MwOGGVorbisSoundMediaDispatcher(void);
	~MwOGGVorbisSoundMediaDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

