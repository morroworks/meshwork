#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwOpenALSound.h"

class MwOpenALSoundReceptor :
	public MwAudioDeviceSoundReceptor
{
public:
	MwOpenALSoundReceptor(void);
	~MwOpenALSoundReceptor(void);

	virtual int GetParameterAddress(MwString parameterName);
	virtual void SetParameter(int address, int index, void *value);
};

