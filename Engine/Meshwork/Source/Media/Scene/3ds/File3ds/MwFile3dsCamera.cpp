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

#include "MwFile3dsCamera.h"


MwFile3dsCamera::MwFile3dsCamera(void)
{
	this->objectType = MwFile3dsObjectType_Camera;

	this->position.x = 0.0f;
	this->position.y = 0.0f;
	this->position.z = 0.0f;
	
	this->target.x = 0.0f;
	this->target.y = 0.0f;
	this->target.z = 0.0f;

	this->bank = 0.0f;
	this->lens = 0.0f;
}


MwFile3dsCamera::~MwFile3dsCamera(void)
{
}
