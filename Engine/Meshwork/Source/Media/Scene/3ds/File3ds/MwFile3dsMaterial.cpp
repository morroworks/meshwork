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

#include "MwFile3dsMaterial.h"


MwFile3dsMaterial::MwFile3dsMaterial(void)
{
	this->ambient.r = 0x00;
	this->ambient.g = 0x00;
	this->ambient.b = 0x00;

	this->diffuse.r = 0x00;
	this->diffuse.g = 0x00;
	this->diffuse.b = 0x00;

	this->specular.r = 0x00;
	this->specular.g = 0x00;
	this->specular.b = 0x00;
	
	this->specularLevel = 0.0f;
	this->glossiness = 0.0f;
	
	this->hasAmbient = false;
	this->hasDiffuse = false;
	this->hasSpecular = false;
}


MwFile3dsMaterial::~MwFile3dsMaterial(void)
{
}
