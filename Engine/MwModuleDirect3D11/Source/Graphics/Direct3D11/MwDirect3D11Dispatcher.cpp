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

#include "MwDirect3D11Dispatcher.h"

#include "MwDirect3D11GraphicsDevice.h"

MwDirect3D11Dispatcher::MwDirect3D11Dispatcher(void)
{
}


MwDirect3D11Dispatcher::~MwDirect3D11Dispatcher(void)
{
}

bool MwDirect3D11Dispatcher::GetInfo(unsigned int infoId, int infoTag, MwString &info)
{
	switch (infoId)
	{
		case MwDispatcher::infoId_TypeId:
			info = MwString(MwDispatcher::typeId_GraphicsDevice);
			return true;

		case MwDispatcher::infoId_Name:
			info = "Direct3D 11";
			return true;

		case MwDispatcher::infoId_Description:
			info = "Direct3D 11 rendering device with dynamic shader building. Provides a full-feature support for the Meshwork engine.";
			return true;
	}

	return false;
}

void *MwDirect3D11Dispatcher::CreateObject()
{
	return new MwDirect3D11GraphicsDevice();
}
