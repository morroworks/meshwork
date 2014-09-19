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

#include "MwDeviceMesh.h"


MwDeviceMesh::MwDeviceMesh(void)
{
}


MwDeviceMesh::~MwDeviceMesh(void)
{
}

void MwDeviceMesh::CopyFrom(MwDeviceMesh *source)
{
	if (source == this)
		return;
	
	int numIndices = source->GetIndexCount();
	this->CreateIndexBuffer(numIndices);
	for (int i = 0; i < numIndices; i++)
	{
		this->SetIndex(i, source->GetIndex(i));
	}
	this->UpdateIndices(0, numIndices);

	int numVertices = source->GetVertexCount();
	this->CreateVertexBuffer(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		MwVector3 v3;
		MwVector2 v2;

		source->GetVertexPosition(i, v3);
		this->GetVertexPosition(i, v3);

		source->GetVertexNormal(i, v3);
		this->GetVertexNormal(i, v3);

		source->GetVertexTexCoords(i, v2);
		this->GetVertexTexCoords(i, v2);
	}
	this->UpdateVertices(0, numVertices);
}