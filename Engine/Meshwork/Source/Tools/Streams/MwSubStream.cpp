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

#include "MwSubStream.h"

#include "..\MwMath.h"

MwSubStream::MwSubStream(MwBaseStream &mainStream, long long length, long long offset, bool writeBeyondLength)
{
	this->mainStream = &mainStream;
	this->offset = offset == -1 ? mainStream.position : offset;
	this->length = length == -1 ? mainStream.length - offset : length;
	this->writeBeyondLength = writeBeyondLength;
}


MwSubStream::~MwSubStream(void)
{
}

long long MwSubStream::ReadData(void *data, long long size)
{
	long long originalPosition = this->mainStream->position;

	size = MwMath::Min(size, this->position + this->length);

	this->mainStream->Seek(this->offset + this->position, StreamSeekMode_FromBeginning);
	long long result = this->mainStream->ReadData(data, size);
	this->mainStream->Seek(originalPosition, StreamSeekMode_FromBeginning);

	this->position += result;

	return result;
}

long long MwSubStream::WriteData(const void *data, long long size)
{
	long long originalPosition = this->mainStream->position;

	if (!this->writeBeyondLength)
		size = MwMath::Min(size, this->position + this->length);

	this->mainStream->Seek(this->offset + this->position, StreamSeekMode_FromBeginning);
	long long result = this->mainStream->WriteData(data, size);
	this->mainStream->Seek(originalPosition, StreamSeekMode_FromBeginning);

	this->position += result;
	if (this->position > this->length)
		this->length = this->position;

	return result;
}
