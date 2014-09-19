//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwOGGVorbisSoundMedia.h"


size_t MwOGGVorbisSoundMedia::ReadCallback(void *ptr, size_t size, size_t nmemb, void *datasource)
{
	MwOGGVorbisSoundMedia *media = (MwOGGVorbisSoundMedia*)datasource;

	return (size_t)media->sourceStream->ReadData(ptr, size * nmemb);
}

int MwOGGVorbisSoundMedia::SeekCallback(void *datasource, ogg_int64_t offset, int whence)
{
	MwOGGVorbisSoundMedia *media = (MwOGGVorbisSoundMedia*)datasource;

	if (media->sourceStream->Seek(offset, whence == SEEK_SET ? StreamSeekMode_FromBeginning : whence == SEEK_CUR ? StreamSeekMode_Relative : StreamSeekMode_FromEnd))
		return 0;
	else
		return -1;
}

int MwOGGVorbisSoundMedia::CloseCallback(void *datasource)
{
	return 0;
}

long MwOGGVorbisSoundMedia::TellCallback(void *datasource)
{
	MwOGGVorbisSoundMedia *media = (MwOGGVorbisSoundMedia*)datasource;
	return (long)(media->sourceStream->position - media->streamStartOffset);
}

MwOGGVorbisSoundMedia::MwOGGVorbisSoundMedia(void)
{
	this->opened = false;
}


MwOGGVorbisSoundMedia::~MwOGGVorbisSoundMedia(void)
{
	this->Clear();
}

bool MwOGGVorbisSoundMedia::Load(MwBaseStream &source)
{
	if (!MwSoundMedia::Load(source))
		return false;

	this->Clear();
	
	this->streamStartOffset = source.position;
	
	ov_callbacks callbacks;
	callbacks.read_func = MwOGGVorbisSoundMedia::ReadCallback;
	callbacks.seek_func = MwOGGVorbisSoundMedia::SeekCallback;
	callbacks.close_func = MwOGGVorbisSoundMedia::CloseCallback;
	callbacks.tell_func = MwOGGVorbisSoundMedia::TellCallback;

	if (ov_open_callbacks(this, &this->oggVorbisFile, 0, 0, callbacks) < 0)
		return false;
	
	// OGG samples are always 2-byte sized (16bit)
	vorbis_info *vorbisInfo = ov_info(&this->oggVorbisFile, -1);
	this->pcmFormat = MwPCMFormat(2, vorbisInfo->rate, vorbisInfo->channels);

	this->totalMediaSamplesCount = (unsigned int)ov_pcm_total(&this->oggVorbisFile, -1);

	this->position = 0;

	this->opened = true;

	return true;
}

void MwOGGVorbisSoundMedia::Clear()
{
	if (this->opened)
	{
		ov_clear(&this->oggVorbisFile);
		
		this->opened = false;
	}
}

bool MwOGGVorbisSoundMedia::Save(MwBaseStream &destination, const char *format)
{
	return false;
}

bool MwOGGVorbisSoundMedia::SetPosition(unsigned int position)
{
	if (!this->opened)
		return false;

	long long channelsSampleSize = (this->pcmFormat.sampleSizeInBytes * this->pcmFormat.channelsCount);
	long long currentSampleIndex = this->position / channelsSampleSize;
	long long seekSampleIndex = position / channelsSampleSize;

	if (currentSampleIndex != seekSampleIndex)
	{
		if (ov_pcm_seek(&this->oggVorbisFile, seekSampleIndex) == 0)
		{
			this->position = seekSampleIndex * channelsSampleSize;
		}
		else
			return false;
	}

	return true;
}

unsigned int MwOGGVorbisSoundMedia::ReadData(unsigned int bytesToRead)
{
	if (!this->opened)
		return 0;

	if (bytesToRead > this->dataSize)
		bytesToRead = this->dataSize;

	int bitStream;
	long bytesRead;
	this->dataBytesRead = 0;
	char *destination = (char*)this->data;
	do
	{
		bytesRead = ov_read(&this->oggVorbisFile, destination, bytesToRead, 0, this->pcmFormat.sampleSizeInBytes, 1, &bitStream);

		destination += bytesRead;
		bytesToRead -= bytesRead;
		this->dataBytesRead += bytesRead;
	}
	while ((bytesRead > 0) && (bytesToRead > 0));

	this->position += this->dataBytesRead;

	return this->dataBytesRead;
}

