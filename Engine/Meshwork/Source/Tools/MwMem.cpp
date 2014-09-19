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

#include "MwMem.h"

#include <string>  

#include "MwMath.h"

MwMem::MwMem(void)
{
}

MwMem::~MwMem(void)
{
}

void* MwMem::Get(unsigned int size)
{
	return malloc(size);
}

void MwMem::FreeAndNull(void **data)
{
	if (*data == 0)
		return;

	free(*data);
	*data = 0;
}

void MwMem::Zero(void* data, int size)
{
	memset(data, 0, size);
}

void MwMem::Fill(void* data, int dataSize, const void *value, int valueSize)
{
	int chunks = dataSize / valueSize;
	int remains = dataSize % valueSize;

	for (int i = chunks; i != 0; i--)
	{
		memcpy(data, value, valueSize);
		data = (void*)((int)data + valueSize);
	}
}

void MwMem::Copy(void* destination, const void* source, int size)
{
	memcpy(destination, source, size);
}

int MwMem::Compare(const void* block1, const void* block2, int size)
{
	return memcmp(block1, block2, size);
}

void MwMem::CopyBits(const void *src, int srcBitOffset, void *dest, int destBitOffset, int bitCount)
{
	// TODO: Can be optimized to process larger (16, 32 bit) chunks while bitCount is large enough
	while (bitCount > 0)
	{
		if (srcBitOffset >= 8)
		{
			src = (void*)((unsigned int)src + (srcBitOffset >> 3));
			srcBitOffset &= 7;
		}

		if (destBitOffset >= 8)
		{
			dest = (void*)((unsigned int)dest + (destBitOffset >> 3));
			destBitOffset &= 7;
		}

		int bitsWritten = MwMath::Min(8 - MwMath::Max(srcBitOffset, destBitOffset), bitCount);

		unsigned char srcChunk = *(unsigned char*)src;
		srcChunk <<= srcBitOffset;
		srcChunk >>= destBitOffset;
		unsigned char mask = (~0);
		mask <<= 8 - bitsWritten;
		mask >>= destBitOffset;
		*(unsigned char*)dest &= (~mask);
		*(unsigned char*)dest |= (srcChunk & mask);


		srcBitOffset += bitsWritten;
		destBitOffset += bitsWritten;

		bitCount -= bitsWritten;
	}
}