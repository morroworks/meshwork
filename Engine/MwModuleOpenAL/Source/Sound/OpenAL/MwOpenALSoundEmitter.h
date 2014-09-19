#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwOpenALSound.h"

#include <OpenAL\al.h>

class MwOpenALAudioDevice;

class MwOpenALSoundEmitter :
	public MwAudioDeviceSoundEmitter
{
private:
	ALuint handle;

	MwOpenALSound *soundBuffer;

	bool isLooping, isAmbient, isPlaying;

public:
	MwOpenALAudioDevice *context;

	MwOpenALSoundEmitter(void);
	~MwOpenALSoundEmitter(void);

	virtual void Play();
	virtual void Stop();

	virtual bool RefillStreamingBuffers();

	virtual int GetParameterAddress(MwString parameterName);
	virtual void SetParameter(int address, int index, void *value);
};

