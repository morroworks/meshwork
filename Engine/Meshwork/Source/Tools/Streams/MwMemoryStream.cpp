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

#include "MwMemoryStream.h"

#include "..\MwMem.h"
#include "..\MwMath.h"

MwMemoryStream::MwMemoryStream(int initialCapacity)
	: MwBaseStream()
{
	this->SetWriteMode(StreamWriteMode_Overwrite);
	
	this->capacity = 0;
	this->data = 0;

	this->Resize(initialCapacity);
}

MwMemoryStream::MwMemoryStream(void *data, int size)
	: MwBaseStream()
{
	this->length = size;

	this->SetWriteMode(StreamWriteMode_Overwrite);
	
	this->capacity = size;
	this->data = data;
}


MwMemoryStream::~MwMemoryStream(void)
{
	MwMem::FreeAndNull(&this->data);
}

long long MwMemoryStream::ReadData(void *data, long long size)
{
	long long bytesToCopy = MwMath::Min(this->length - this->position, size);
	MwMem::Copy(data, (void*)((unsigned int)this->data + (unsigned int)this->position), (unsigned int)bytesToCopy);

	this->position += bytesToCopy;

	return bytesToCopy;
}

long long MwMemoryStream::WriteData(const void *data, long long size)
{
	long long requiredCapacity = this->writeMode == StreamWriteMode_Overwrite ? this->position + size : this->length + size;
	long long newCapacity = this->capacity;
	while (requiredCapacity > newCapacity)
	{
		newCapacity *= 2;
	}
	if (newCapacity != this->capacity)
		this->Resize(newCapacity);

	if (this->writeMode == StreamWriteMode_Insert)
	{
		long long tailBytes = this->length - this->position;
		if (size > tailBytes)
		{
			MwMem::Copy(this->GetDataPointer((unsigned int)this->position + size), this->GetDataPointer(this->position), (unsigned int)tailBytes);
		}
		else
		{
			void *tailData = MwMem::Get((unsigned int)tailBytes);
			MwMem::Copy(tailData, this->GetDataPointer(this->position), tailBytes);
			MwMem::Copy(this->GetDataPointer(this->position + size), tailData, tailBytes);
			MwMem::FreeAndNull(&tailData);
		}

		this->length += size;
	}

	MwMem::Copy(this->GetDataPointer(this->position), data, size);

	this->position += size;

	this->length = MwMath::Max(this->length, this->position);

	return size;
}

void MwMemoryStream::SetWriteMode(StreamWriteMode writeMode)
{
	this->writeMode = writeMode;
}

void MwMemoryStream::Resize(long long newCapacity)
{
	void *newData = MwMem::Get((int)newCapacity);
	
	if (this->length > 0)
		MwMem::Copy(newData, this->data, MwMath::Min(this->length, newCapacity));
	if (this->data != 0)
		MwMem::FreeAndNull(&this->data);

	this->data = newData;
	this->capacity = newCapacity;

};

void *MwMemoryStream::GetDataPointer(long long offset)
{
	return (void*)((int)this->data + offset);
}
