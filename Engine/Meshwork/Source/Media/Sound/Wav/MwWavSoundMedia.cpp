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

#include "MwWavSoundMedia.h"


MwWavSoundMedia::MwWavSoundMedia(void)
{
}


MwWavSoundMedia::~MwWavSoundMedia(void)
{
}

bool MwWavSoundMedia::Load(MwBaseStream &source)
{
	if (!MwSoundMedia::Load(source))
		return false;

	if (this->wavFile.Initialize(this->sourceStream))
	{
		this->pcmFormat = MwPCMFormat(this->wavFile.bitsPerSample / 8, this->wavFile.sampleRate, this->wavFile.numChannels);
		this->totalMediaSamplesCount = (unsigned int)(this->wavFile.dataLength / (this->pcmFormat.sampleSizeInBytes * this->pcmFormat.channelsCount));

		this->position = 0;

		return true;
	}

	return false;
}

bool MwWavSoundMedia::Save(MwBaseStream &destination, const char *format) 
{ 
	return false;
}

bool MwWavSoundMedia::SetPosition(unsigned int position)
{
	if ((position >= 0) && (position < this->wavFile.dataLength))
	{
		this->position = position;
		return true;
	}

	return false;
}

unsigned int MwWavSoundMedia::ReadData(unsigned int bytesToRead)
{
	if (bytesToRead > this->dataSize)
		bytesToRead = this->dataSize;

	int readBytes = this->wavFile.ReadData(this->data, this->position, bytesToRead);
	this->position += readBytes;

	return readBytes;
}
