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

#include "MwFile3dsLight.h"


MwFile3dsLight::MwFile3dsLight(void)
{
	this->objectType = MwFile3dsObjectType_Light;

	this->active = true;

	this->color.r = 1.0f;
	this->color.g = 1.0f;
	this->color.b = 1.0f;
	
	this->position.x = 0.0f;
	this->position.y = 0.0f;
	this->position.z = 0.0f;

	this->spotLight = false;
	this->spotlight_Target.x = 0.0f;
	this->spotlight_Target.y = 0.0f;
	this->spotlight_Target.z = 0.0f;

	this->spotlight_Hotspot = 0.0f;
	this->spotlight_Falloff = 0.0f;
}


MwFile3dsLight::~MwFile3dsLight(void)
{
}
