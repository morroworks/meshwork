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

#include "MwWavSoundMediaDispatcher.h"

#include "MwWavSoundMedia.h"

MwWavSoundMediaDispatcher::MwWavSoundMediaDispatcher(void)
{
}


MwWavSoundMediaDispatcher::~MwWavSoundMediaDispatcher(void)
{
}

bool MwWavSoundMediaDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_Sound);
			return true;

		case MwDispatcher::infoId_Name:
			info = "Wave";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Meshwork built in reader of the Waveform Audio File Format";
			return true;

		case MwDispatcher::infoId_MediaDeserializationFormatExtension:
			if (infoTag == 0)
			{
				info = "wav";
				return true;
			}
			break;

		case MwDispatcher::infoId_MediaDeserializationFormatDescription:
			if (infoTag == 0)
			{
				info = "Wave";
				return true;
			}
			break;
	}

	return false;
}

void *MwWavSoundMediaDispatcher::CreateObject()
{
	return new MwWavSoundMedia();
}
