#pragma once

#include "..\..\Engine\Base\MwDispatcher.h"

class MwSorasGraphicsDeviceDispatcher :
	public MwDispatcher
{
public:
	MwSorasGraphicsDeviceDispatcher(void);
	~MwSorasGraphicsDeviceDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

