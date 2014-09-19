#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\Streams\MwBaseStream.h"

class MWDLLCLASS MwWavFile
{
private:
	static const unsigned int	chunk_RIFF = 0x46464952;
	static const unsigned int		chunk_fmt = 0x20746d66;
	static const unsigned int		chunk_data = 0x61746164;

	static const unsigned int riffType_WAVE = 0x45564157;

	MwBaseStream *source;

	long long mainChunkEnd;

	bool Read();

public:
	unsigned short audioFormat;		// PCM
	unsigned short numChannels;		// mono, stereo
	unsigned int sampleRate;		// 22050, 44100, etc.
	unsigned int byteRate;			// == SampleRate * NumChannels * BitsPerSample / 8
	unsigned short blockAlign;		// == NumChannels * BitsPerSample / 8. The number of bytes for one sample
	unsigned short bitsPerSample;	// 8, 16, etc.

	long long dataStart, dataLength;
	
	MwWavFile(void);
	~MwWavFile(void);

	bool Initialize(MwBaseStream *source);
	int ReadData(void *destination, unsigned int position, unsigned int length);
};

