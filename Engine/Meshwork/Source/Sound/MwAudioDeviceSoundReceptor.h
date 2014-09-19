#pragma once

#include "..\MwGlobals.h"

#include "..\Tools\MwString.h"

class MWDLLCLASS MwAudioDeviceSoundReceptor
{
public:
	MwAudioDeviceSoundReceptor(void);
	~MwAudioDeviceSoundReceptor(void);

	virtual int GetParameterAddress(MwString parameterName) = 0;
	virtual void SetParameter(int address, int index, void *value) = 0;
};

