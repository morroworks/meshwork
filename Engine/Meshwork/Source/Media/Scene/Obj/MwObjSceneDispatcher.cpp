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

#include "MwObjSceneDispatcher.h"

#include "MwObjScene.h"

MwObjSceneDispatcher::MwObjSceneDispatcher(void)
{
}


MwObjSceneDispatcher::~MwObjSceneDispatcher(void)
{
}

bool MwObjSceneDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	const int numDeserializationFormats = 2;
	const char *deserializationFormats[numDeserializationFormats] = { "obj", "mtl" };
	const char *deserializationFormatsDescription[numDeserializationFormats] = { "Wavefront mesh", "Wavefront material" };
	
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_Scene);
			return true;

		case MwDispatcher::infoId_Name:
			info = "Wavefront OBJ and MTL";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Meshwork built in reader of Wavefront's OBJ and MTL formats";
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
	}

	return false;
}

void *MwObjSceneDispatcher::CreateObject()
{
	return new MwObjScene();
}
