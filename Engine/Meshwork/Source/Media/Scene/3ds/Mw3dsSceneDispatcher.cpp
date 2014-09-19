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

#include "Mw3dsSceneDispatcher.h"

#include "Mw3dsScene.h"

Mw3dsSceneDispatcher::Mw3dsSceneDispatcher(void)
{
}


Mw3dsSceneDispatcher::~Mw3dsSceneDispatcher(void)
{
}

bool Mw3dsSceneDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_Scene);
			return true;

		case MwDispatcher::infoId_Name:
			info = "3D Studio Max";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Meshwork built in reader of the 3D Studio Max format";
			return true;

		case MwDispatcher::infoId_MediaDeserializationFormatExtension:
			if (infoTag == 0)
			{
				info = "3ds";
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaDeserializationFormatDescription:
			if (infoTag == 0)
			{
				info = "3D Studio Max";
				return true;
			}
			break;
	}

	return false;
}

void *Mw3dsSceneDispatcher::CreateObject()
{
	return new Mw3dsScene();
}
