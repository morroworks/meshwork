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

#include "MwSorasTexture2D.h"

#include "..\..\Tools\MwMem.h"

MwSorasTexture2D::MwSorasTexture2D(void)
{
	this->sorasTexture = new SrTexture();
}


MwSorasTexture2D::~MwSorasTexture2D(void)
{
	delete this->sorasTexture;
}

void MwSorasTexture2D::Update(void *data, int width, int height)
{
	this->sorasTexture->SetSize(width, height);

	if (data != 0)
		MwMem::Copy(this->sorasTexture->data, data, this->sorasTexture->dataSize);
}

void MwSorasTexture2D::GetData(void *data)
{
	MwMem::Copy(data, this->sorasTexture->data, this->sorasTexture->dataSize);
}
