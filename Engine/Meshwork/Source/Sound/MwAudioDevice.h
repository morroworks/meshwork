#pragma once

#include "..\MwGlobals.h"

#include "MwAudioDeviceSound.h"
#include "MwAudioDeviceSoundEmitter.h"
#include "MwAudioDeviceSoundReceptor.h"

class MWDLLCLASS MwAudioDevice
{
public:
	MwAudioDevice(void);
	virtual ~MwAudioDevice(void);

	virtual MwAudioDeviceSound *CreateSound() = 0;
	virtual MwAudioDeviceSoundEmitter *CreateSoundEmitter() = 0;
	virtual MwAudioDeviceSoundReceptor *CreateSoundReceptor() = 0;
};

