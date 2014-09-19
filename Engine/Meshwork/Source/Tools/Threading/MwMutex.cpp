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

#include "MwMutex.h"

#include <windows.h>

MwMutex::MwMutex(void)
{
	this->handle = new HANDLE;

	*(HANDLE*)this->handle = CreateMutex( 
		NULL,		// default security attributes
		FALSE,		// initially not owned
		NULL);		// unnamed mutex
}


MwMutex::~MwMutex(void)
{
	CloseHandle(*(HANDLE*)this->handle);

	delete this->handle;
}

bool MwMutex::Lock()
{
	return WaitForSingleObject(*(HANDLE*)this->handle, INFINITE) == WAIT_OBJECT_0;
}

void MwMutex::Unlock()
{
	ReleaseMutex(*(HANDLE*)this->handle);
}