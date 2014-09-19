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

#include "MwSorasMesh.h"

#include "Engine\Primitive\SrUnit.h"

MwSorasMesh::MwSorasMesh(void)
{
	this->sorasMesh = new SrMesh();
}

MwSorasMesh::~MwSorasMesh(void)
{
	delete this->sorasMesh;
}

bool MwSorasMesh::CreateVertexBuffer(int numVertices)
{
	this->sorasMesh->SetVertexCount(numVertices);

	return true;
}

bool MwSorasMesh::CreateIndexBuffer(int numIndices)
{
	this->sorasMesh->SetIndexCount(numIndices);

	return true;
}

bool MwSorasMesh::DeleteVertexBuffer()
{
	this->sorasMesh->SetVertexCount(0);

	return true;
}

bool MwSorasMesh::DeleteIndexBuffer()
{
	this->sorasMesh->SetIndexCount(0);

	return true;
}

bool MwSorasMesh::UpdateVertices(int offset, int count)
{
	// no need to update

	return true;
}

bool MwSorasMesh::UpdateIndices(int offset, int count)
{
	// no need to update

	return true;
}

int MwSorasMesh::GetVertexCount()
{
	return this->sorasMesh->numVertices;
}

int MwSorasMesh::GetIndexCount()
{
	return this->sorasMesh->numIndices;
}

int MwSorasMesh::GetPrimitiveCount()
{
	return this->sorasMesh->numIndices / 3;
}

void MwSorasMesh::GetVertexPosition(int index, MwVector3 &result)
{
	result = *(MwVector3*)(&this->sorasMesh->vertices[index].position);
}

void MwSorasMesh::SetVertexPosition(int index, MwVector3 &value)
{
	this->sorasMesh->vertices[index].position = *(SrVector3*)(&value);
}

void MwSorasMesh::GetVertexNormal(int index, MwVector3 &result)
{
	result = *(MwVector3*)(&this->sorasMesh->vertices[index].normal);
}

void MwSorasMesh::SetVertexNormal(int index, MwVector3 &value)
{
	this->sorasMesh->vertices[index].normal = *(SrVector3*)(&value);
}

void MwSorasMesh::GetVertexTexCoords(int index, MwVector2 &result)
{
	result.x = SrUnit::ToFloat(this->sorasMesh->vertices[index].texCoords.x);
	result.y = SrUnit::ToFloat(this->sorasMesh->vertices[index].texCoords.y);
}

void MwSorasMesh::SetVertexTexCoords(int index, MwVector2 &value)
{
	this->sorasMesh->vertices[index].texCoords.x = SrUnit::FromFloat(value.x);
	this->sorasMesh->vertices[index].texCoords.y = SrUnit::FromFloat(value.y);
}

void MwSorasMesh::GetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights)
{
	boneIndices.x = (float)this->sorasMesh->vertices[index].boneIndices.x;
	boneIndices.y = (float)this->sorasMesh->vertices[index].boneIndices.y;
	boneIndices.z = (float)this->sorasMesh->vertices[index].boneIndices.z;
	boneIndices.w = (float)this->sorasMesh->vertices[index].boneIndices.w;

	boneWeights.x = this->sorasMesh->vertices[index].boneWeights.x;
	boneWeights.y = this->sorasMesh->vertices[index].boneWeights.y;
	boneWeights.z = this->sorasMesh->vertices[index].boneWeights.z;
	boneWeights.w = this->sorasMesh->vertices[index].boneWeights.w;
}

void MwSorasMesh::SetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights)
{
	this->sorasMesh->vertices[index].boneIndices.x = (int)MwMath::Round(boneIndices.x);
	this->sorasMesh->vertices[index].boneIndices.y = (int)MwMath::Round(boneIndices.y);
	this->sorasMesh->vertices[index].boneIndices.z = (int)MwMath::Round(boneIndices.z);
	this->sorasMesh->vertices[index].boneIndices.w = (int)MwMath::Round(boneIndices.w);

	this->sorasMesh->vertices[index].boneWeights.x = boneWeights.x;
	this->sorasMesh->vertices[index].boneWeights.y = boneWeights.y;
	this->sorasMesh->vertices[index].boneWeights.z = boneWeights.z;
	this->sorasMesh->vertices[index].boneWeights.w = boneWeights.w;
}

int MwSorasMesh::GetIndex(int index)
{
	return this->sorasMesh->indices[index];
}

void MwSorasMesh::SetIndex(int index, int value)
{
	this->sorasMesh->indices[index] = value;
}

