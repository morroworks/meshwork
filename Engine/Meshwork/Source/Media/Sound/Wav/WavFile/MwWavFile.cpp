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

#include "MwWavFile.h"

#include "..\..\..\..\Tools\MwMath.h"

MwWavFile::MwWavFile(void)
{
	this->mainChunkEnd = -1;
	this->dataStart = -1;

	this->source = 0;
}


MwWavFile::~MwWavFile(void)
{
}

bool MwWavFile::Read()
{
	unsigned int chunkId = this->source->ReadUInt32();
	unsigned int chunkSize = this->source->ReadUInt32();

	switch (chunkId)
	{
		case MwWavFile::chunk_RIFF:
		{
			this->mainChunkEnd = this->source->position + chunkSize;
			
			unsigned int riffType = this->source->ReadUInt32();
			if (riffType != MwWavFile::riffType_WAVE)
				return false;

			break;
		}

		case MwWavFile::chunk_fmt:
		{
			this->audioFormat = this->source->ReadUInt16();
			this->numChannels = this->source->ReadUInt16();
			this->sampleRate = this->source->ReadUInt32();
			this->byteRate = this->source->ReadUInt32();
			this->blockAlign = this->source->ReadUInt16();
			this->bitsPerSample = this->source->ReadUInt16();

			break;
		}

		case MwWavFile::chunk_data:
		{
			this->dataStart = this->source->position;
			this->dataLength = chunkSize;

			return true;
		}

		default:
		{
			if ((chunkSize < 0) || (this->source->position + chunkSize > this->mainChunkEnd))
				return false;

			this->source->Seek(chunkSize, StreamSeekMode_Relative);

			break;
		}
	}

	if (this->mainChunkEnd < 0)
		return false;

	if (this->source->position + 8 < this->mainChunkEnd)
        return this->Read();

	return true;
}

bool MwWavFile::Initialize(MwBaseStream *source)
{
	this->source = source;

	return this->Read();
}

int MwWavFile::ReadData(void *destination, unsigned int position, unsigned int length)
{
	if (this->source == 0)
		return -1;

	if (this->dataStart == -1)
		return -1;

	long long pos = this->dataStart + position;
	if (pos >= this->source->length)
		return 0;

	long long readLength = MwMath::Min(length, this->dataLength - position);

	this->source->Seek(pos);
	readLength = this->source->ReadData(destination, readLength);

	return readLength;
}
