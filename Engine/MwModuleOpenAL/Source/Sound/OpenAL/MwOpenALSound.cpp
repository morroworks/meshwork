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

#include "MwOpenALSound.h"

const float MwOpenALSound::ResidentBufferMaxDuration = 5.0f;
const float MwOpenALSound::StreamingBufferDuration = 1.0f;


MwOpenALSound::MwOpenALSound(void)
{
	this->bufferIds = 0;
	this->buffersCount = 0;

	this->mediaSource = 0;
}


MwOpenALSound::~MwOpenALSound(void)
{
	this->Clear();
}

void MwOpenALSound::Clear()
{
	if (this->bufferIds != 0)
	{
		alDeleteBuffers(this->buffersCount, this->bufferIds);

		delete[] this->bufferIds;
		this->bufferIds = 0;
	}

	this->mediaSource = 0;
}

bool MwOpenALSound::IsStreaming()
{
	return this->isStreaming;
}

void MwOpenALSound::SetMediaSource(MwSoundMedia *mediaSource)
{
	this->Clear();

	this->isStreaming = mediaSource->GetTotalDuration() > MwOpenALSound::ResidentBufferMaxDuration;

	this->buffersCount = this->isStreaming ? 2 : 1;
	this->bufferIds = new ALuint[this->buffersCount];

	unsigned int buffersLength = this->isStreaming ? (unsigned int)(MwOpenALSound::StreamingBufferDuration * (float)(mediaSource->pcmFormat.frequency * mediaSource->pcmFormat.sampleSizeInBytes * mediaSource->pcmFormat.channelsCount)) : mediaSource->totalMediaSamplesCount * mediaSource->pcmFormat.sampleSizeInBytes * mediaSource->pcmFormat.channelsCount;

	this->alFormat = mediaSource->pcmFormat.channelsCount == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

	alGenBuffers(this->buffersCount, this->bufferIds);
	
	mediaSource->SetSize(buffersLength);

	for (int i = 0; i < this->buffersCount; i++)
	{
		unsigned int readBytes = mediaSource->ReadData(mediaSource->dataSize);
		
		alBufferData(this->bufferIds[i], this->alFormat, mediaSource->data, readBytes, mediaSource->pcmFormat.frequency);
	}

	this->mediaSource = this->isStreaming ? mediaSource : 0;
}
