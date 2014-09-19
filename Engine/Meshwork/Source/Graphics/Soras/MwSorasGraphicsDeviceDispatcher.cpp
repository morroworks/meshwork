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

#include "MwSorasGraphicsDeviceDispatcher.h"

#include "MwSorasGraphicsDevice.h"

MwSorasGraphicsDeviceDispatcher::MwSorasGraphicsDeviceDispatcher(void)
{
}


MwSorasGraphicsDeviceDispatcher::~MwSorasGraphicsDeviceDispatcher(void)
{
}


bool MwSorasGraphicsDeviceDispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_GraphicsDevice);
			return true;

		case MwDispatcher::infoId_Name:
			info = "Meshwork Soras";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Meshwork Soras is a software rasterization device with some customizable shading capabilities. Supports a few of Meshwork's less complex features to some extent.";
			return true;
	}

	return false;
}

void *MwSorasGraphicsDeviceDispatcher::CreateObject()
{
	return new MwSorasGraphicsDevice();
}
