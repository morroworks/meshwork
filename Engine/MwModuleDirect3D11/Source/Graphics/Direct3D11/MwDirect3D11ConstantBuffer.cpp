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

#include "MwDirect3D11ConstantBuffer.h"

MwDirect3D11ConstantBuffer::MwDirect3D11ConstantBuffer(void)
{
	this->data = 0;
	this->dataSize = 0;
}


MwDirect3D11ConstantBuffer::~MwDirect3D11ConstantBuffer(void)
{
	this->SetDataSize(0);
}

void MwDirect3D11ConstantBuffer::SetDataSize(int dataSizeInBytes)
{
	if (this->data != 0)
	{
		delete this->data;
		this->data = 0;
		this->dataSize = 0;
	}

	if (dataSizeInBytes > 0)
	{
		this->dataSize = dataSizeInBytes;
		this->data = new char[this->dataSize];
		MwMem::Zero(this->data, this->dataSize);
	}
}