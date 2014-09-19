#pragma once

#include "..\..\..\MeshworkEngine.h"

#include <Vorbis\vorbis\vorbisfile.h>

class MwOGGVorbisSoundMedia :
	public MwSoundMedia
{
private:
	bool opened;

	OggVorbis_File oggVorbisFile;
	
	long long streamStartOffset, position;

	static size_t MwOGGVorbisSoundMedia::ReadCallback(void *ptr, size_t size, size_t nmemb, void *datasource);
	static int MwOGGVorbisSoundMedia::SeekCallback(void *datasource, ogg_int64_t offset, int whence);
	static int MwOGGVorbisSoundMedia::CloseCallback(void *datasource);
	static long MwOGGVorbisSoundMedia::TellCallback(void *datasource);

	void Clear();

public:
	MwOGGVorbisSoundMedia(void);
	~MwOGGVorbisSoundMedia(void);

	virtual bool Load(MwBaseStream &source);
	virtual bool Save(MwBaseStream &destination, const char *format);

	virtual bool SetPosition(unsigned int position);
	virtual unsigned int ReadData(unsigned int bytesToRead);
};

