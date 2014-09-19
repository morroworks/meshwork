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

#include "MwFbxSceneDispatcher.h"

#include "MwFbxScene.h"

MwFbxSceneDispatcher::MwFbxSceneDispatcher(void)
{
}


MwFbxSceneDispatcher::~MwFbxSceneDispatcher(void)
{
}

bool MwFbxSceneDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	const int numDeserializationFormats = 4;
	const char *deserializationFormats[numDeserializationFormats] = { "fbx", "dae", "3ds", "obj" };
	const char *deserializationFormatsDescription[numDeserializationFormats] = { "Autodesk FBX", "Collada DAE", "3D Studio", "Wavefront OBJ" };
	
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_Scene);
			return true;

		case MwDispatcher::infoId_Name:
			info = "Autodesk FBX formats";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Deserializes 3d file formats using the Autodesk FBX SDK. Supports FBX, DAE, 3DS and OBJ. Can only load data from files from the physical file system.";
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

void *MwFbxSceneDispatcher::CreateObject()
{
	return new MwFbxScene();
}
