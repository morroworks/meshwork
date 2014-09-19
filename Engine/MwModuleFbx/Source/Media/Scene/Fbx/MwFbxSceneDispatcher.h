#pragma once

#include "..\..\..\MeshworkEngine.h"

class MwFbxSceneDispatcher :
	public MwDispatcher
{
public:
	MwFbxSceneDispatcher(void);
	~MwFbxSceneDispatcher(void);
	
	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};
