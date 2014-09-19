#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\..\Sound\MwAudioDeviceSound.h"

#include "..\..\..\Media\Sound\MwSoundMedia.h"
#include "..\..\..\Tools\MwString.h"

class Meshwork;

class MWDLLCLASS MwSound :
	public MwBaseResource
{
public:
	static const int classId = (MwResourceType_Sound << 16) | 0;

	static const unsigned int SerializationId_FileName	= 0x2111100a;

	Meshwork *context;

	MwBaseStream *mediaSourceStream;
	MwSoundMedia *mediaSource;

	MwAudioDeviceSound *deviceSound;

	MwString fileName;

	MwSound(Meshwork *context);
	~MwSound(void);

	//// Loads the whole data into memory. The resulting sound is not streaming
	//void Load(void *data, int dataSize, const MwPCMFormat &format);
	// Loads the sound from a media and if the resulting sound is streaming, keeps the source media or if the resulting sound is not streaming, releases the source media. If the sound is streaming, the media is kept and the stream which it reads from must also be kept until the sound is destroyed.
	void Load(MwSoundMedia *sourceMedia);
	// Loads the sound from a stream and if the resulting sound is streaming, keeps the source stream or if the resulting sound is not streaming, releases the source stream.
	bool Load(MwBaseStream *source);
	// Loads the sound from a file and if the resulting sound is streaming, keeps the file open or if the resulting sound is not streaming, closes the file.
	bool Load(MwString &fileName);

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

