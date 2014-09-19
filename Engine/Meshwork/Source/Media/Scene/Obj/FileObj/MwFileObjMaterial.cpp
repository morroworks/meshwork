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

#include "MwFileObjMaterial.h"


MwFileObjMaterial::MwFileObjMaterial(void)
{
	this->ambientMap = 0;
	this->diffuseMap = 0;
	this->specularColorMap = 0;
	this->specularHighlightMap = 0;
	this->alphaMap = 0;
	this->bumpMap = 0;
	this->displacementMap = 0;
	this->stencilMap = 0;
	this->reflectionMap = 0;
	
	this->ambientColor.x = 0.0f;
	this->ambientColor.y = 0.0f;
	this->ambientColor.z = 0.0f;

	this->diffuseColor.x = 0.0f;
	this->diffuseColor.y = 0.0f;
	this->diffuseColor.z = 0.0f;

	this->specularColor.x = 0.0f;
	this->specularColor.y = 0.0f;
	this->specularColor.z = 0.0f;
	
	this->specularFactor = 0.0f;
	this->transparency = 0.0f;
}


MwFileObjMaterial::~MwFileObjMaterial(void)
{
	if (this->ambientMap != 0)
		delete this->ambientMap;
	if (this->diffuseMap != 0)
		delete this->diffuseMap;
	if (this->specularColorMap != 0)
		delete this->specularColorMap;
	if (this->specularHighlightMap != 0)
		delete this->specularHighlightMap;
	if (this->alphaMap != 0)
		delete this->alphaMap;
	if (this->bumpMap != 0)
		delete this->bumpMap;
	if (this->displacementMap != 0)
		delete this->displacementMap;
	if (this->stencilMap != 0)
		delete this->stencilMap;
	if (this->reflectionMap != 0)
		delete this->reflectionMap;
}
