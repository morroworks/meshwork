#pragma once

#include "..\..\MwGlobals.h"

class MWDLLCLASS MwPixelFormat
{
public:
	static const unsigned char ChannelsMax = 4;

	static const unsigned char ChannelIdRed = 0;
	static const unsigned char ChannelIdGreen = 1;
	static const unsigned char ChannelIdBlue = 2;
	static const unsigned char ChannelIdAlpha = 3;

	int numChannels, sizeInBytes;
	unsigned char channelBitCount[4], channelId[4];

	MwPixelFormat(void);
	MwPixelFormat(int numChannels, int sizeInBytes, unsigned char channel0BitCount, unsigned char channel1BitCount, unsigned char channel2BitCount, unsigned char channel3BitCount, unsigned char channel0Id, unsigned char channel1Id, unsigned char channel2Id, unsigned char channel3Id);
	~MwPixelFormat(void);

	bool Equals(MwPixelFormat &pixelFormat);
	int FindChannelIdIndex(unsigned char channelId);
	int FindChannelIdBitOffset(unsigned char channelId);
	
	void GetChannelsValues(unsigned int pixelValue, float *channelsValues);
};