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

#include "MwILImageDispatcher.h"

#include "MwILImage.h"

MwILImageDispatcher::MwILImageDispatcher(void)
{
}


MwILImageDispatcher::~MwILImageDispatcher(void)
{
}

bool MwILImageDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	const int numDeserializationFormats = 7;
	const char *deserializationFormats[numDeserializationFormats] = { "bmp", "dds", "jpg", "jpeg", "jp2", "png", "tga" };
	const char *deserializationFormatsDescription[numDeserializationFormats] = { "Windows Bitmap", "DirectDraw Surface", "Jpeg", "Jpeg", "Jpeg 2000", "Portable Network Graphics", "Truevision Targa" };
	
	const int numSerializationFormats = 5;
	const char *serializationFormats[numSerializationFormats] = { "bmp", "dds", "jpg", "png", "tga" };
	const char *serializationFormatsDescription[numSerializationFormats] = { "Windows Bitmap", "DirectDraw Surface", "Jpeg", "Portable Network Graphics", "Truevision Targa" };
	
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_Image);
			return true;

		case MwDispatcher::infoId_Name:
			info = "DevIL";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Serializes and deserializes images using DevIL - the open Developers Image Library (a.k.a. OpenIL)";
			return true;

		case MwDispatcher::infoId_MediaDeserializationFormatExtension:
			if ((infoTag >= 0) && (infoTag < numDeserializationFormats))
			{
				info = deserializationFormats[infoTag];
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaDeserializationFormatDescription:
			if ((infoTag >= 0) && (infoTag < numDeserializationFormats))
			{
				info = deserializationFormatsDescription[infoTag];
				return true;
			}
			break;
		
		case MwDispatcher::infoId_MediaSerializationFormatExtension:
			if ((infoTag >= 0) && (infoTag < numSerializationFormats))
			{
				info = serializationFormats[infoTag];
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaSerializationFormatDescription:
			if ((infoTag >= 0) && (infoTag < numSerializationFormats))
			{
				info = serializationFormatsDescription[infoTag];
				return true;
			}
			break;	
	}

	return false;
}

void *MwILImageDispatcher::CreateObject()
{
	return new MwILImage();
}
