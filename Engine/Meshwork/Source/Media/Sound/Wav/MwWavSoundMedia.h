#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\MwSoundMedia.h"

#include "WavFile\MwWavFile.h"

class MWDLLCLASS MwWavSoundMedia :
	public MwSoundMedia
{
private:
	MwWavFile wavFile;
	unsigned int position;

public:
	MwWavSoundMedia(void);
	~MwWavSoundMedia(void);

	virtual bool Load(MwBaseStream &source);
	virtual bool Save(MwBaseStream &destination, const char *format);

	virtual bool SetPosition(unsigned int position);
	virtual unsigned int ReadData(unsigned int bytesToRead);
};

