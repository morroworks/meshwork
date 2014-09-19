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

#include "MwFileObjTextureMap.h"


MwFileObjTextureMap::MwFileObjTextureMap(void)
{
	this->offset.x = 0.0f;
	this->offset.y = 0.0f;
	this->offset.z = 0.0f;

	this->scale.x = 1.0f;
	this->scale.y = 1.0f;
	this->scale.z = 1.0f;
	
	this->turbulence.x = 0.0f;
	this->turbulence.y = 0.0f;
	this->turbulence.z = 0.0f;

	this->brightness = 0.0f;
	this->contrastFactor = 1.0;
	this->bumpFactor = 1.0f;
	this->mipMapSharpness = 0.0f;

	this->resolution = -1;
	
	this->clamp = false;
	this->blendU = true;
	this->blendV = true;

	this->mapType = MwFileObjTextureMapType_Default;
	this->mapChannel = MwFileObjTextureMapChannel_Default;
}


MwFileObjTextureMap::~MwFileObjTextureMap(void)
{
}
