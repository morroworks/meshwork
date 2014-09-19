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

#include "MwOpenGL1_1Texture2D.h"

#include <windows.h>
#include <gl\GL.h>

MwOpenGL1_1Texture2D::MwOpenGL1_1Texture2D()
	: MwDeviceTexture2D()
{
	glGenTextures(1, &this->textureId);

	glBindTexture(GL_TEXTURE_2D, this->textureId);				
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


MwOpenGL1_1Texture2D::~MwOpenGL1_1Texture2D(void)
{
	glDeleteTextures(1, &this->textureId);
}

void MwOpenGL1_1Texture2D::Update(void *data, int width, int height)
{
	if (data != 0)
	{
		glBindTexture(GL_TEXTURE_2D, this->textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}

void MwOpenGL1_1Texture2D::GetData(void *data)
{
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
