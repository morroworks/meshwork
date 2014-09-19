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

#include "MwDeviceIndependentMesh.h"


MwDeviceIndependentMesh::MwDeviceIndependentMesh(void)
	: MwDeviceMesh()
{
	this->positions = 0;
	this->normals = 0;
	this->texCoords = 0;
	this->boneIndices = 0;
	this->boneWeights = 0;


	this->indices = 0;


	this->numVertices = 0;
	this->numIndices = 0;
}


MwDeviceIndependentMesh::~MwDeviceIndependentMesh(void)
{
	this->DeleteVertexBuffer();
	this->DeleteIndexBuffer();
}

bool MwDeviceIndependentMesh::CreateVertexBuffer(int numVertices)
{
	this->DeleteVertexBuffer();
	
	this->positions = new float[numVertices * 3];
	this->normals = new float[numVertices * 3];
	this->texCoords = new float[numVertices * 2];
	this->boneIndices = new float[numVertices * 4];
	this->boneWeights = new float[numVertices * 4];

	this->numVertices = numVertices;

	return true;
}

bool MwDeviceIndependentMesh::CreateIndexBuffer(int numIndices)
{
	this->DeleteIndexBuffer();

	this->indices = new unsigned short[numIndices];

	this->numIndices = numIndices;
	
	return true;
}

bool MwDeviceIndependentMesh::DeleteVertexBuffer()
{
	if (this->positions != 0)
		delete[] this->positions;
	if (this->normals != 0)
		delete[] this->normals;
	if (this->texCoords != 0)
		delete[] this->texCoords;
	if (this->boneIndices != 0)
		delete[] this->boneIndices;
	if (this->boneWeights != 0)
		delete[] this->boneWeights;

	this->positions = 0;
	this->normals = 0;
	this->texCoords = 0;
	this->boneIndices = 0;
	this->boneWeights = 0;

	this->numVertices = 0;

	return true;
}

bool MwDeviceIndependentMesh::DeleteIndexBuffer()
{
	if (this->indices != 0)
		delete[] this->indices;

	this->indices = 0;

	this->numIndices = 0;

	return true;
}

bool MwDeviceIndependentMesh::UpdateVertices(int offset, int count)
{
	return true;
}

bool MwDeviceIndependentMesh::UpdateIndices(int offset, int count)
{
	return true;
}

int MwDeviceIndependentMesh::GetVertexCount()
{
	return this->numVertices;
}

int MwDeviceIndependentMesh::GetIndexCount()
{
	return this->numIndices;
}

int MwDeviceIndependentMesh::GetPrimitiveCount()
{
	return this->numIndices / 3;
}

void MwDeviceIndependentMesh::GetVertexPosition(int index, MwVector3 &result)
{
	index *= 3;
	result.x = this->positions[index++];
	result.y = this->positions[index++];
	result.z = this->positions[index];
}

void MwDeviceIndependentMesh::SetVertexPosition(int index, MwVector3 &value)
{
	index *= 3;
	this->positions[index++] = value.x;
	this->positions[index++] = value.y;
	this->positions[index] = value.z;
}

void MwDeviceIndependentMesh::GetVertexNormal(int index, MwVector3 &result)
{
	index *= 3;
	result.x = this->normals[index++];
	result.y = this->normals[index++];
	result.z = this->normals[index];
}

void MwDeviceIndependentMesh::SetVertexNormal(int index, MwVector3 &value)
{
	index *= 3;
	this->normals[index++] = value.x;
	this->normals[index++] = value.y;
	this->normals[index] = value.z;
}

void MwDeviceIndependentMesh::GetVertexTexCoords(int index, MwVector2 &result)
{
	index *= 2;
	result.x = this->texCoords[index++];
	result.y = this->texCoords[index];
}

void MwDeviceIndependentMesh::SetVertexTexCoords(int index, MwVector2 &value)
{
	index *= 2;
	this->texCoords[index++] = value.x;
	this->texCoords[index] = value.y;
}

void MwDeviceIndependentMesh::GetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights)
{
	index *= 4;
	boneIndices.x = this->boneIndices[index];
	boneWeights.x = this->boneWeights[index++];

	boneIndices.y = this->boneIndices[index];
	boneWeights.y = this->boneWeights[index++];

	boneIndices.z = this->boneIndices[index];
	boneWeights.z = this->boneWeights[index++];

	boneIndices.w = this->boneIndices[index];
	boneWeights.w = this->boneWeights[index++];
}

void MwDeviceIndependentMesh::SetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights)
{
	index *= 4;
	this->boneIndices[index] = boneIndices.x;
	this->boneWeights[index++] = boneWeights.x;

	this->boneIndices[index] = boneIndices.y;
	this->boneWeights[index++] = boneWeights.y;

	this->boneIndices[index] = boneIndices.z;
	this->boneWeights[index++] = boneWeights.z;

	this->boneIndices[index] = boneIndices.w;
	this->boneWeights[index] = boneWeights.w;
}

int MwDeviceIndependentMesh::GetIndex(int index)
{
	return this->indices[index];
}

void MwDeviceIndependentMesh::SetIndex(int index, int value)
{
	this->indices[index] = value;
}
