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

#include "MwSubMesh.h"


MwSubMesh::MwSubMesh(int originalVertexCount)
{
	this->originalVertexCount = originalVertexCount;
	this->originalVertexReferences = new int[this->originalVertexCount];
	for (int i = 0; i < this->originalVertexCount; i++)
	{
		this->originalVertexReferences[i] = -1;
	}
}


MwSubMesh::~MwSubMesh(void)
{
	delete[] this->originalVertexReferences;

	for (int i = 0; i < this->faces.count; i++)
	{
		delete this->faces[i];
	}
}

int MwSubMesh::AddFace()
{
	this->faces.Add(new MwSubMeshFace());
	
	return this->faces.count - 1;
}

int MwSubMesh::AddFaceVertex(int faceIndex, int originalVertexIndex)
{
	int vertexIndex = this->originalVertexReferences[originalVertexIndex];
	if (vertexIndex == -1)
	{
		vertexIndex = this->vertexIndices.count;
		this->vertexIndices.Add(originalVertexIndex);
		this->originalVertexReferences[originalVertexIndex] = vertexIndex;
	}

	this->faces[faceIndex]->indices.Add(vertexIndex);

	return vertexIndex;
}


void MwSubMesh::Reset()
{
	for (int i = 0; i < this->originalVertexCount; i++)
	{
		this->originalVertexReferences[i] = -1;
	}

	for (int i = 0; i < this->faces.count; i++)
	{
		delete this->faces[i];
	}
	this->faces.SetSize(0);
}