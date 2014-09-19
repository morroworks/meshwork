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

#include "MwPixelFormat.h"

#include "..\..\Tools\MwMem.h"

MwPixelFormat::MwPixelFormat(void)
{
}

MwPixelFormat::MwPixelFormat(int numChannels, int sizeInBytes, unsigned char channel0BitCount, unsigned char channel1BitCount, unsigned char channel2BitCount, unsigned char channel3BitCount, unsigned char channel0Id, unsigned char channel1Id, unsigned char channel2Id, unsigned char channel3Id)
{
	this->numChannels = numChannels;
	this->sizeInBytes = sizeInBytes;
	this->channelBitCount[0] = channel0BitCount;
	this->channelBitCount[1] = channel1BitCount;
	this->channelBitCount[2] = channel2BitCount;
	this->channelBitCount[3] = channel3BitCount;
	this->channelId[0] = channel0Id;
	this->channelId[1] = channel1Id;
	this->channelId[2] = channel2Id;
	this->channelId[3] = channel3Id;
}

MwPixelFormat::~MwPixelFormat(void)
{
}

bool MwPixelFormat::Equals(MwPixelFormat &pixelFormat)
{
	return MwMem::Compare(this, &pixelFormat, sizeof(MwPixelFormat)) == 0;
}

int MwPixelFormat::FindChannelIdIndex(unsigned char channelId)
{
	for (int channelIndex = 0; channelIndex < this->numChannels; channelIndex++)
		if (this->channelId[channelIndex] == channelId)
			return channelIndex;

	return -1;
}

int MwPixelFormat::FindChannelIdBitOffset(unsigned char channelId)
{
	int offset = 0;
	for (int channelIndex = 0; channelIndex < this->numChannels; channelIndex++)
	{
		if (this->channelId[channelIndex] == channelId)
			return offset;

		offset += this->channelBitCount[channelIndex];
	}

	return -1;
}

void MwPixelFormat::GetChannelsValues(unsigned int pixelValue, float *channelsValues)
{
	for (int channelIndex = 0; channelIndex < this->numChannels; channelIndex++)
	{

	}
}
