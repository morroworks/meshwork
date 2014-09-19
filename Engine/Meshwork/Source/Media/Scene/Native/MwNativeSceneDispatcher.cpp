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

#include "MwNativeSceneDispatcher.h"

#include "MwNativeScene.h"

MwNativeSceneDispatcher::MwNativeSceneDispatcher(void)
{
}


MwNativeSceneDispatcher::~MwNativeSceneDispatcher(void)
{
}

bool MwNativeSceneDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_Scene);
			return true;

		case MwDispatcher::infoId_Name:
			info = "Meshwork";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Meshwork native scene format. Serializes and deserialized scene in meshwork's native format";
			return true;

		case MwDispatcher::infoId_MediaSerializationFormatExtension:
			if (infoTag == 0)
			{
				info = "mw";
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaSerializationFormatDescription:
			if (infoTag == 0)
			{
				info = "Meshwork";
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaDeserializationFormatExtension:
			if (infoTag == 0)
			{
				info = "mw";
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaDeserializationFormatDescription:
			if (infoTag == 0)
			{
				info = "Meshwork";
				return true;
			}
			break;
	}

	return false;
}

void *MwNativeSceneDispatcher::CreateObject()
{
	return new MwNativeScene();
}
