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

#include "MwFileStream.h"

#include "..\MwMem.h"

#include <fstream>

MwFileStream::MwFileStream(const MwString &fileName, FileStreamAccessMode accessMode)
	: MwBaseStream()
{

	std::ios_base::openmode fileMode = accessMode == FileStreamAccessMode_Read ? std::ios::in : accessMode == FileStreamAccessMode_Write ? std::ios::out : accessMode == FileStreamAccessMode_ReadWrite ? std::ios::in | std::ios::out : 0;

	this->fileStream_fstream = new std::fstream;
	((std::fstream*)this->fileStream_fstream)->open(fileName.contents, fileMode | std::ios::binary | std::ios::ate);

	this->length = ((std::fstream*)this->fileStream_fstream)->tellg();
	
	this->Seek(0, StreamSeekMode_FromBeginning);
}


MwFileStream::~MwFileStream(void)
{
	((std::fstream*)this->fileStream_fstream)->close();
	delete ((std::fstream*)this->fileStream_fstream);
}

long long MwFileStream::ReadData(void *data, long long size)
{
	((std::fstream*)this->fileStream_fstream)->read((char*)data, size);

	long long bytesRead = ((std::fstream*)this->fileStream_fstream)->gcount();

	this->position += bytesRead;

	return bytesRead;
}

long long MwFileStream::WriteData(const void *data, long long size)
{
	((std::fstream*)this->fileStream_fstream)->write((char*)data, size);

	long long bytesWritten = size;

	this->position += bytesWritten;
	
	if (this->position > this->length)
		this->length = this->position;

	return bytesWritten;
}

bool MwFileStream::Seek(long long offset, StreamSeekMode seekType)
{
	if (MwBaseStream::Seek(offset, seekType))
	{
		((std::fstream*)this->fileStream_fstream)->seekg(this->position);
		((std::fstream*)this->fileStream_fstream)->seekp(this->position);
	}

	return false;
}
