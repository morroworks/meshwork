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

#include "MwImage.h"

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwMem.h"
#include "..\..\Tools\MwMath.h"


MwImage::MwImage(void)
{
	this->Init();
}

MwImage::MwImage(MwImage &source)
{
	this->Init();
	this->Copy(source);
}

MwImage::MwImage(MwImage &source, MwPixelFormat &pixelFormat)
{
	this->Init();
	this->Copy(source);
	this->SetPixelFormat(pixelFormat);
}

MwImage::~MwImage(void)
{
	this->SetSize(0, 0, 0);
}

void MwImage::Init()
{
	this->width = 0;
	this->height = 0;
	this->depth = 0;

	this->pixelData = 0;
	this->pixelFormat = MwPixelFormat(4, 4, 8, 8, 8, 8, MwPixelFormat::ChannelIdRed, MwPixelFormat::ChannelIdGreen, MwPixelFormat::ChannelIdBlue, MwPixelFormat::ChannelIdAlpha);
}

void MwImage::SetPixelFormat(MwPixelFormat &pixelFormat, bool dither)
{
	if (this->pixelFormat.Equals(pixelFormat))
		return;


	// perform dithering on matching channels, if required
	if (dither)
	{
		int lineSize = this->width * this->pixelFormat.sizeInBytes;
		int bitOffset = 0;
		for (int channelIndex = 0; channelIndex < this->pixelFormat.numChannels; channelIndex++)
		{
			int newChannelIndex = pixelFormat.FindChannelIdIndex(this->pixelFormat.channelId[channelIndex]);
			if (newChannelIndex != -1)
			{
				int channelBitDifference = this->pixelFormat.channelBitCount[channelIndex] - pixelFormat.channelBitCount[newChannelIndex];
				if (channelBitDifference > 0)
				{
					int channelMax = ((1 << this->pixelFormat.channelBitCount[channelIndex]) - 1);
					unsigned int mask = channelMax << bitOffset;
					unsigned char *pixel = this->pixelData;

					for (int z = 0; z < this->depth; z++)
					{
						for (int y = 0; y < this->height - 1; y++)
						{
							pixel += this->pixelFormat.sizeInBytes;
							for (int x = 1; x < this->width - 1; x++)
							{
								unsigned int channelOldValue = (*(unsigned int*)pixel & mask) >> bitOffset;
								unsigned int channelNewValue = (channelOldValue >> channelBitDifference) << channelBitDifference;
								unsigned int error = channelOldValue - channelNewValue;

								*(unsigned int*)pixel = ((*(unsigned int*)pixel) & (~mask)) | (channelNewValue << bitOffset);

								unsigned int *neighbour = (unsigned int*)(pixel + this->pixelFormat.sizeInBytes);
								*neighbour = ((*neighbour) & (~mask)) | (MwMath::Min(((*neighbour & mask) >> bitOffset) + 7 * error / 16, channelMax) << bitOffset);
								neighbour = (unsigned int*)(pixel + lineSize - this->pixelFormat.sizeInBytes);
								*neighbour = ((*neighbour) & (~mask)) | (MwMath::Min(((*neighbour & mask) >> bitOffset) + 3 * error / 16, channelMax) << bitOffset);
								neighbour = (unsigned int*)(pixel + lineSize);
								*neighbour = ((*neighbour) & (~mask)) | (MwMath::Min(((*neighbour & mask) >> bitOffset) + 5 * error / 16, channelMax) << bitOffset);
								neighbour = (unsigned int*)(pixel + lineSize + this->pixelFormat.sizeInBytes);
								*neighbour = ((*neighbour) & (~mask)) | (MwMath::Min(((*neighbour & mask) >> bitOffset) + error / 16, channelMax) << bitOffset);

								pixel += this->pixelFormat.sizeInBytes;
							}
							pixel += this->pixelFormat.sizeInBytes;
						}
						pixel += lineSize;
					}
				}
			}

			bitOffset += this->pixelFormat.channelBitCount[channelIndex];
		}
	}


	// create and fill the new channels
	unsigned char *newData = 0;
	int newDataSize = this->width * this->height * this->depth * pixelFormat.sizeInBytes;
	if (newDataSize != 0)
	{
		newData = new unsigned char[newDataSize];

		int bitOffset = 0;
		for (int channelIndex = 0; channelIndex < pixelFormat.numChannels; channelIndex++)
		{
			int channelBitDifference = 0;

			//int oldChannelIndex = pixelFormat.FindChannelIdIndex(this->pixelFormat.channelId[channelIndex]);
			int oldChannelIndex = this->pixelFormat.FindChannelIdIndex(pixelFormat.channelId[channelIndex]);
			int oldChannelBitOffset;
			unsigned int channelOldValue = 0;
			unsigned int oldChannelMax;
			unsigned int oldChannelMask;
			unsigned char *oldChannelPixel = this->pixelData;
			if (oldChannelIndex != -1)
			{
				channelBitDifference = this->pixelFormat.channelBitCount[oldChannelIndex] - pixelFormat.channelBitCount[channelIndex];
				oldChannelBitOffset = this->pixelFormat.FindChannelIdBitOffset(this->pixelFormat.channelId[oldChannelIndex]);
				oldChannelMax = (1 << this->pixelFormat.channelBitCount[oldChannelIndex]) - 1;
				oldChannelMask = oldChannelMax << oldChannelBitOffset;
			}

			
			unsigned int channelNewValue = 0;
			unsigned int newChannelMax = (1 << pixelFormat.channelBitCount[channelIndex]) - 1;
			unsigned int mask = newChannelMax << bitOffset;
			unsigned char *pixel = newData;

			for (int z = 0; z < this->depth; z++)
			{
				for (int y = 0; y < this->height; y++)
				{
					for (int x = 0; x < this->width; x++)
					{
						if ((oldChannelIndex != -1) && (oldChannelMax > 0))
						{
							channelOldValue = (*(unsigned int*)oldChannelPixel & oldChannelMask) >> oldChannelBitOffset;
							channelNewValue = channelBitDifference >= 0 ? channelOldValue >> channelBitDifference : (channelOldValue  * newChannelMax) / oldChannelMax;
						}

						*(unsigned int*)pixel = ((*(unsigned int*)pixel) & (~mask)) | (channelNewValue << bitOffset);

						pixel += pixelFormat.sizeInBytes;
						oldChannelPixel += this->pixelFormat.sizeInBytes;
					}
				}
			}

			bitOffset += pixelFormat.channelBitCount[channelIndex];
		}
	}

	if (this->pixelData != 0)
		delete[] this->pixelData;

	this->pixelData = newData;

	this->pixelFormat = pixelFormat;
}

MwPixelFormat MwImage::GetPixelFormat()
{
	return this->pixelFormat;
}

void MwImage::SetSize(int width, int height, int depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;

	if (this->pixelData != 0)
	{
		delete[] this->pixelData;
		this->pixelData = 0;
	}

	int dataSize = this->width * this->height * this->depth * this->pixelFormat.sizeInBytes;
	if (dataSize != 0)
		this->pixelData = new unsigned char[dataSize];
}

void MwImage::CopyPixels(MwImage &source, int srcX, int srcY, int srcZ, int destX, int destY, int destZ, int width, int height, int depth)
{
	if ((source.height == height) && (this->height == height) && (source.width == width) && (this->width == width))
	{
		if ((source.depth == depth) && (this->depth == depth))
		{
			MwMem::Copy(this->pixelData, source.pixelData, width * height * depth * source.pixelFormat.sizeInBytes);
		}
		else
		{
			int planeSize = width * height * 4;
			int dest = *(int*)this->pixelData + destZ * planeSize;
			int src = *(int*)source.pixelData + srcZ * planeSize;
			for (int z = 0; z < depth; z++)
			{
				MwMem::Copy((void*)dest, (void*)src, planeSize); 
				dest += planeSize;
				src += planeSize;
			}
		}
	}
	else
	{
		int lineSize = width * 4;
		int destLineSize = this->width * 4;
		int destPlaneSize = destLineSize * this->height;
		int srcLineSize = source.width * 4;
		int srcPlaneSize = srcLineSize * source.height;
		int dest = *(int*)this->pixelData + destZ * destPlaneSize + destY * destLineSize + destX * 4;
		int src = *(int*)source.pixelData + srcZ * srcPlaneSize + srcY * srcLineSize + srcX * 4;
		for (int z = 0; z < depth; z++)
		{
			int d = dest;
			int s = src;
			for (int y = 0; y < height; y++)
			{
				MwMem::Copy((void*)d, (void*)s, lineSize); 
				d += destLineSize;
				s += srcLineSize;
			}

			dest += destPlaneSize;
			src += srcPlaneSize;
		}
	}
}

void MwImage::CopyPixels(MwImage &source, int srcX, int srcY, int srcZ, int width, int height, int depth)
{
	this->CopyPixels(source, srcX, srcY, srcZ, 0, 0, 0, width, height, depth);
}

void MwImage::CopyPixels(MwImage &source)
{
	this->CopyPixels(source, 0, 0, 0, 0, 0, 0, MwMath::Min(source.width, this->width), MwMath::Min(source.height, this->height), MwMath::Min(source.depth, this->depth));
}

void MwImage::Copy(MwImage &source)
{
	this->pixelFormat = source.pixelFormat;
	this->SetSize(source.width, source.height, source.depth);
	this->CopyPixels(source);
}

void MwImage::SetPixel(int x, int y, int z, unsigned int value)
{
	MwMem::Copy(&this->pixelData[(z * this->width * this->height + y * this->width + x) * this->pixelFormat.sizeInBytes], &value, this->pixelFormat.sizeInBytes);
}

unsigned int MwImage::GetPixel(int x, int y, int z)
{
	unsigned int result = 0;
	MwMem::Copy(&result, &this->pixelData[z * this->width * this->height + y * this->width + x], this->pixelFormat.sizeInBytes);
	return result;
}

unsigned int MwImage::GetSample(float u, float v, int z)
{
	float x = u * this->width;
	float y = v * this->height;

	int x1 = (int)x;
	int y1 = (int)y;

	x -= x1;
	y -= y1;

	x1 %= this->width;
	y1 %= this->height;

	int x2 = (x1 + 1) % this->width;
	int y2 = (y1 + 1) % this->height;

	int planeOffset = z * this->width * this->height;

	unsigned int p11 = *(unsigned int*)&this->pixelData[(planeOffset + y1 * this->width + x1) * this->pixelFormat.sizeInBytes];
	unsigned int p12 = *(unsigned int*)&this->pixelData[(planeOffset + y1 * this->width + x2) * this->pixelFormat.sizeInBytes];
	unsigned int p21 = *(unsigned int*)&this->pixelData[(planeOffset + y2 * this->width + x1) * this->pixelFormat.sizeInBytes];
	unsigned int p22 = *(unsigned int*)&this->pixelData[(planeOffset + y2 * this->width + x2) * this->pixelFormat.sizeInBytes];

	unsigned int result;

	for (int channelIndex = 0; channelIndex < this->pixelFormat.numChannels; channelIndex++)
	{
		int channelBitCount = this->pixelFormat.channelBitCount[channelIndex];
		int channelLimit = 1 << channelBitCount;
		int channelMax = channelLimit - 1;
		int fx = (int)(x * channelLimit);
		int fy = (int)(y * channelLimit);

		int c11 = p11 & channelMax;
		int c12 = p12 & channelMax;
		int c21 = p21 & channelMax;
		int c22 = p22 & channelMax;

		int c1 = c11 + (((c12 - c11) * fx) >> channelBitCount);
		int c2 = c21 + (((c22 - c21) * fx) >> channelBitCount);
		int c = c1 + (((c2 - c1) * fy) >> channelBitCount);

		result = (result << channelBitCount) | c;

		p11 = p11 >> channelBitCount;
		p12 = p12 >> channelBitCount;
		p21 = p21 >> channelBitCount;
		p22 = p22 >> channelBitCount;
	}

	return result;
}

unsigned int MwImage::GetSample(float u, float v, float w)
{
	float x = u * this->width;
	float y = v * this->height;
	float z = w * this->depth;

	int x1 = (int)x;
	int y1 = (int)y;
	int z1 = (int)z;

	x -= x1;
	y -= y1;
	z -= z1;

	x1 %= this->width;
	y1 %= this->height;
	z1 %= this->depth;

	int x2 = (x1 + 1) % this->width;
	int y2 = (y1 + 1) % this->height;
	int z2 = (z1 + 1) % this->depth;

	int planeSize = this->width * this->height;
	int plane1Offset = z1 * planeSize;
	int plane2Offset = z2 * planeSize;

	unsigned int p111 = *(unsigned int*)&this->pixelData[(plane1Offset + y1 * this->width + x1) * this->pixelFormat.sizeInBytes];
	unsigned int p112 = *(unsigned int*)&this->pixelData[(plane1Offset + y1 * this->width + x2) * this->pixelFormat.sizeInBytes];
	unsigned int p121 = *(unsigned int*)&this->pixelData[(plane1Offset + y2 * this->width + x1) * this->pixelFormat.sizeInBytes];
	unsigned int p122 = *(unsigned int*)&this->pixelData[(plane1Offset + y2 * this->width + x2) * this->pixelFormat.sizeInBytes];
	unsigned int p211 = *(unsigned int*)&this->pixelData[(plane2Offset + y1 * this->width + x1) * this->pixelFormat.sizeInBytes];
	unsigned int p212 = *(unsigned int*)&this->pixelData[(plane2Offset + y1 * this->width + x2) * this->pixelFormat.sizeInBytes];
	unsigned int p221 = *(unsigned int*)&this->pixelData[(plane2Offset + y2 * this->width + x1) * this->pixelFormat.sizeInBytes];
	unsigned int p222 = *(unsigned int*)&this->pixelData[(plane2Offset + y2 * this->width + x2) * this->pixelFormat.sizeInBytes];

	unsigned int result;

	for (int channelIndex = 0; channelIndex < this->pixelFormat.numChannels; channelIndex++)
	{
		int channelBitCount = this->pixelFormat.channelBitCount[channelIndex];
		int channelLimit = 1 << channelBitCount;
		int channelMax = channelLimit - 1;
		int fx = (int)(x * channelLimit);
		int fy = (int)(y * channelLimit);
		int fz = (int)(z * channelLimit);

		int c11 = p111 & channelMax;
		int c12 = p112 & channelMax;
		int c21 = p121 & channelMax;
		int c22 = p122 & channelMax;

		int c1 = c11 + (((c12 - c11) * fx) >> channelBitCount);
		int c2 = c21 + (((c22 - c21) * fx) >> channelBitCount);
		int p1c = c1 + (((c2 - c1) * fy) >> channelBitCount);

		c11 = p211 & channelMax;
		c12 = p212 & channelMax;
		c21 = p221 & channelMax;
		c22 = p222 & channelMax;

		c1 = c11 + (((c12 - c11) * fx) >> channelBitCount);
		c2 = c21 + (((c22 - c21) * fx) >> channelBitCount);
		int p2c = c1 + (((c2 - c1) * fy) >> channelBitCount);

		int pc = p1c + (((p2c - p1c) * fy) >> 8);

		result = (result << channelBitCount) | pc;

		p111 = p111 >> channelBitCount;
		p112 = p112 >> channelBitCount;
		p121 = p121 >> channelBitCount;
		p122 = p122 >> channelBitCount;

		p211 = p211 >> channelBitCount;
		p212 = p212 >> channelBitCount;
		p221 = p221 >> channelBitCount;
		p222 = p222 >> channelBitCount;
	}

	return result;
}

bool MwImage::Load(MwBaseStream &source) { return false; };
bool MwImage::Save(MwBaseStream &destination, const char *encoding) { return false; };
