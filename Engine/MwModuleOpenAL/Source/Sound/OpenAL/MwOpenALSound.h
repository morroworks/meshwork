#pragma once

#include "..\..\MeshworkEngine.h"

#include <OpenAL\al.h>

class MwOpenALSound :
	public MwAudioDeviceSound
{
private:
	// The maximum duration in seconds, of a buffer which is not streaming, but residently loaded in memory. Sounds with longer duration will use streaming buffers.
	static const float ResidentBufferMaxDuration;
	// The duration in seconds, of a buffer used in a queue for streaming audio.
	static const float StreamingBufferDuration;

	void Clear();

public:
	int buffersCount;
	ALuint *bufferIds;

	ALenum alFormat;

	bool isStreaming;
	MwSoundMedia *mediaSource;

	MwOpenALSound(void);
	~MwOpenALSound(void);

	virtual bool IsStreaming();
	virtual void SetMediaSource(MwSoundMedia *mediaSource);
};

