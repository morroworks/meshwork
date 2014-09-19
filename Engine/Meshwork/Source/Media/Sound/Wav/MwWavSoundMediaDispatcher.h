#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Engine\Base\MwDispatcher.h"

class MWDLLCLASS MwWavSoundMediaDispatcher :
	public MwDispatcher
{
public:
	MwWavSoundMediaDispatcher(void);
	~MwWavSoundMediaDispatcher(void);

	virtual bool GetInfo(unsigned int infoId, int infoTag, MwString &info);
	virtual void *CreateObject();
};

