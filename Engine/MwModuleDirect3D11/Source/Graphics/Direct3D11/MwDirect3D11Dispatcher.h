#pragma once

#include "..\..\MeshworkEngine.h"

class MwDirect3D11Dispatcher :
	public MwDispatcher
{
public:
	MwDirect3D11Dispatcher(void);
	~MwDirect3D11Dispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};