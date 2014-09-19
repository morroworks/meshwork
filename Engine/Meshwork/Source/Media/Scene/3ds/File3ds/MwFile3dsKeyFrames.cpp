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

#include "MwFile3dsKeyFrames.h"

MwFile3dsKeyFrameBase::MwFile3dsKeyFrameBase(void)
{
}

MwFile3dsKeyFrameBase::~MwFile3dsKeyFrameBase(void)
{
}


MwFile3dsKeyFramesTrack::MwFile3dsKeyFramesTrack(void)
{
}

MwFile3dsKeyFramesTrack::~MwFile3dsKeyFramesTrack(void)
{
	for (int i = 0; i < this->data.count; i++)
		delete this->data[i];
}


MwFile3dsKeyFrameObject::MwFile3dsKeyFrameObject(void)
{
	this->position = 0;
	this->rotation = 0;
	this->scaling = 0;

	this->pivot.x = 0.0f;
	this->pivot.y = 0.0f;
	this->pivot.z = 0.0f;
}

MwFile3dsKeyFrameObject::~MwFile3dsKeyFrameObject(void)
{
	if (this->position != 0)
		delete this->position;

	if (this->rotation != 0)
		delete this->rotation;

	if (this->scaling != 0)
		delete this->scaling;
}


MwFile3dsKeyFrames::MwFile3dsKeyFrames(void)
{
}

MwFile3dsKeyFrames::~MwFile3dsKeyFrames(void)
{
	for (int i = 0; i < this->objects.count; i++)
		delete this->objects[i];
}