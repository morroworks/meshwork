#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwOpenALSoundEmitter.h"

#include <OpenAL\al.h>
#include <OpenAL\alc.h>

class MwOpenALAudioDevice :
	public MwAudioDevice
{
private:
	static int MwOpenALAudioDevice::StreamingThreadFunction(void *parameter);

	ALCdevice *device;
	ALCcontext *context;

	MwList<MwAudioDeviceSoundEmitter*> streamingSounds;
	MwMutex *streamingThreadMutex;
	MwThread *streamingThread;
	bool processStreaming;

public:
	MwOpenALAudioDevice(void);
	~MwOpenALAudioDevice(void);

	void AddStreamingSoundEmitter(MwAudioDeviceSoundEmitter *soundEmitter);
	void RemoveStreamingSoundEmitter(MwAudioDeviceSoundEmitter *soundEmitter);

	virtual MwAudioDeviceSound *CreateSound();
	virtual MwAudioDeviceSoundEmitter *CreateSoundEmitter();
	virtual MwAudioDeviceSoundReceptor *CreateSoundReceptor();
};

