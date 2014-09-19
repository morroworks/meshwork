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

#include "MwILImage.h"

#include <DevIL\il.h>

MwILImage::Initialization MwILImage::initialization;

MwILImage::Initialization::Initialization(void)
{
	ilInit();

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
}

MwILImage::MwILImage(void)
	: MwImage()
{
	this->SetPixelFormat(MwPixelFormat(4, 4, 8, 8, 8, 8, MwPixelFormat::ChannelIdRed, MwPixelFormat::ChannelIdGreen, MwPixelFormat::ChannelIdBlue, MwPixelFormat::ChannelIdAlpha));

	this->imageId_ILuint = new ILuint();
}

MwILImage::~MwILImage(void)
{
	delete (ILuint*)this->imageId_ILuint;
}

bool MwILImage::Load(MwBaseStream &source)
{
	ilGenImages(1, (ILuint*)this->imageId_ILuint);
	ilBindImage(*((ILuint*)this->imageId_ILuint));
	
	void *bytes = MwMem::Get((int)source.length);
	source.ReadData(bytes, source.length);
	bool result = ilLoadL(IL_TYPE_UNKNOWN, bytes, (unsigned int) source.length) == IL_TRUE;
	MwMem::FreeAndNull(&bytes);

	if (result)
	{
		this->SetSize(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_DEPTH));
	
		ilCopyPixels(0, 0, 0, this->width, this->height, this->depth, IL_RGBA, IL_UNSIGNED_BYTE, this->pixelData);
	}

	ilDeleteImages(1, (ILuint*)this->imageId_ILuint);

	return result;
}

bool MwILImage::Save(MwBaseStream &destination, const char *format)
{
	ILuint ilEncoding;

	if (format != 0)
	{
		MwString encodingCode = MwString(format).Trim('.');
		
		if (encodingCode.length == 0)
			ilEncoding = IL_PNG;

		if (encodingCode.Equals("png"))
			ilEncoding = IL_PNG;
		else if (encodingCode.Equals("jpg"))
			ilEncoding = IL_JPG;
		else if (encodingCode.Equals("bmp"))
			ilEncoding = IL_BMP;

		else
			return false;
	}
	else
		ilEncoding = IL_PNG;

	ILuint numChannels = this->pixelFormat.numChannels == 4 ? 4 : 3;
	ILuint ilFormat = numChannels == 4 ? IL_RGBA : IL_RGB;
	MwPixelFormat requiredFormat(numChannels, numChannels, 8, 8, 8, 8, MwPixelFormat::ChannelIdRed, MwPixelFormat::ChannelIdGreen, MwPixelFormat::ChannelIdBlue, MwPixelFormat::ChannelIdAlpha);
	MwImage *image = this->pixelFormat.Equals(requiredFormat) ? this : new MwImage(*this, requiredFormat);

	ILuint imageId;
	ilGenImages(1, &imageId);
	ilBindImage(imageId);
	ilTexImage(image->width, image->height, image->depth, numChannels, ilFormat, IL_UNSIGNED_BYTE, image->pixelData);
	unsigned int dataSize = ilSaveL(ilEncoding, 0, 0);
	char *data = new char[dataSize];
	dataSize = ilSaveL(ilEncoding, data, dataSize);
	ilDeleteImages(1, &imageId);
	destination.WriteData(data, dataSize);
	delete[] data;

	if (image != this)
		delete image;

	return dataSize != 0;
}
