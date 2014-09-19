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

#include "MwSoundMedia.h"


MwSoundMedia::MwSoundMedia(void)
{
	this->data = 0;
	this->dataSize = 0;

	this->sourceStream = 0;
}


MwSoundMedia::~MwSoundMedia(void)
{
	this->SetSize(0);
}

bool MwSoundMedia::Load(MwBaseStream &source)
{
	this->sourceStream = &source;

	return true;
}

void MwSoundMedia::SetSize(unsigned int dataSize)
{
	if (this->data != 0)
	{
		delete[] this->data;
		this->data = 0;
		this->dataSize = 0;
	}

	if (dataSize > 0)
	{
		this->dataSize = dataSize;
		this->data = new char[this->dataSize];
	}
}

float MwSoundMedia::GetTotalDuration()
{
	return (float)this->totalMediaSamplesCount / (float)this->pcmFormat.frequency;
}

unsigned int MwSoundMedia::ReadDataLooping(unsigned int bytesToRead)
{
	unsigned int bytesRead = this->ReadData(bytesToRead);

	unsigned int remainingBytes = bytesToRead - bytesRead;
	if (remainingBytes != 0)
	{
		unsigned int totalDataSize = this->pcmFormat.sampleSizeInBytes * this->pcmFormat.channelsCount * this->totalMediaSamplesCount;
		unsigned int lastPos = totalDataSize - bytesRead;
		if (remainingBytes > lastPos)
			remainingBytes = lastPos;
		
		this->SetPosition(0);

		void* d = this->data;
		this->data = (void*)((unsigned int)this->data + bytesRead);
		bytesRead += this->ReadData(remainingBytes);
		this->data = d;
	}

	return bytesRead;
}
