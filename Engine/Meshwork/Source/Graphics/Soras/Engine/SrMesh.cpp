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

#include "SrMesh.h"

#include "..\..\..\Tools\MwMem.h"

SrMesh::SrMesh(void)
{
	this->indices = 0;
	this->vertices = 0;
	this->transformedVertices = 0;
	this->visiblePrimitives = 0;

	this->numIndices = 0;
	this->numVertices = 0;
}


SrMesh::SrMesh(SrMesh &original)
{
	this->SetIndexCount(original.numIndices);
	this->SetVertexCount(original.numVertices);

	MwMem::Copy(this->indices, original.indices, original.numIndices * sizeof(int));
	MwMem::Copy(this->vertices, original.vertices, original.numVertices * sizeof(SrVertex));
}

SrMesh::~SrMesh(void)
{
	this->SetIndexCount(0);
	this->SetVertexCount(0);
}

// TODO: consider only a SetCount method for MwDeviceMesh and all mesh-related objects. The creation and destruction of the buffers will happen simply at create/destroy of on object

void SrMesh::SetIndexCount(int numIndices)
{
	if (numIndices == this->numIndices)
		return;
	
	
	if (this->indices != 0)
		delete[] this->indices;

	if (this->visiblePrimitives != 0)
		delete[] this->visiblePrimitives;


	if (numIndices != 0)
	{
		this->indices = new int[numIndices];
		this->visiblePrimitives = new int[numIndices / 3];
	}
	else
	{
		this->indices = 0;
		this->visiblePrimitives = 0;
	}


	this->numIndices = numIndices;
}

void SrMesh::SetVertexCount(int numVertices)
{
	if (numVertices == this->numVertices)
		return;

	
	if (this->vertices != 0)
		delete[] this->vertices;

	if (this->transformedVertices != 0)
		delete[] this->transformedVertices;


	if (numVertices != 0)
	{
		this->vertices = new SrVertex[numVertices];
		this->transformedVertices = new SrVertex[numVertices];
	}
	else
	{
		this->vertices = 0;
		this->transformedVertices = 0;
	}


	this->numVertices = numVertices;
}
