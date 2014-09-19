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

#include "MwDirect3D11Mesh.h"


MwDirect3D11Mesh::MwDirect3D11Mesh(void)
{
	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->positionOffset = 0;
	this->normalOffset = this->positionOffset + 3 * 4;
	this->texCoordsOffset = this->normalOffset + 3 * 4;
	this->bonesOffset = this->texCoordsOffset + 2 * 4;

	this->vertexSize = (3 + 3 + 2 + 4 + 4) * 4;

	this->vertexData = 0;
	this->vertexCount = 0;

	this->indexData = 0;
	this->indexCount = 0;
}

MwDirect3D11Mesh::~MwDirect3D11Mesh(void)
{
	this->DeleteVertexBuffer();
	this->DeleteIndexBuffer();
}

bool MwDirect3D11Mesh::CreateVertexBuffer(int numVertices)
{
	this->DeleteVertexBuffer();

	this->vertexCount = numVertices;
	this->vertexData = new char[this->vertexSize * this->vertexCount];

	return true;
}

bool MwDirect3D11Mesh::CreateIndexBuffer(int numIndices)
{
	this->DeleteIndexBuffer();

	this->indexCount = numIndices;
	this->indexData = new int[this->indexCount];

	return true;
}

bool MwDirect3D11Mesh::DeleteVertexBuffer()
{
	if (this->vertexData != 0)
	{
		delete[] this->vertexData;
		this->vertexData = 0;
	}
	
	this->vertexCount = 0;

	if (this->vertexBuffer != 0)
	{
		this->vertexBuffer->Release();
		this->vertexBuffer = 0;
	}

	return true;
}

bool MwDirect3D11Mesh::DeleteIndexBuffer()
{
	if (this->indexData != 0)
	{
		delete[] this->indexData;
		this->indexData = 0;
	}
	
	this->indexCount = 0;

	if (this->indexBuffer != 0)
	{
		this->indexBuffer->Release();
		this->indexBuffer = 0;
	}

	return true;
}

bool MwDirect3D11Mesh::UpdateVertices(int offset, int count)
{
	if (this->vertexBuffer == 0)
	{
		D3D11_BUFFER_DESC bufferDescription;
		MwMem::Zero(&bufferDescription, sizeof(bufferDescription));
		bufferDescription.ByteWidth = this->vertexCount * this->vertexSize;
		bufferDescription.Usage = D3D11_USAGE_DEFAULT;
		bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDescription.CPUAccessFlags = 0;
		bufferDescription.MiscFlags = 0;
		bufferDescription.StructureByteStride = this->vertexSize;

		D3D11_SUBRESOURCE_DATA initData;
		MwMem::Zero(&initData, sizeof(initData));
		initData.pSysMem = this->vertexData;
		
		if (FAILED(this->context->device->CreateBuffer(&bufferDescription, &initData, &this->vertexBuffer)))
			return false;
	}

	return true;
}

bool MwDirect3D11Mesh::UpdateIndices(int offset, int count)
{
	if (this->indexBuffer == 0)
	{
		D3D11_BUFFER_DESC bufferDescription;
		MwMem::Zero(&bufferDescription, sizeof(bufferDescription));
		bufferDescription.ByteWidth = this->indexCount * 4;
		bufferDescription.Usage = D3D11_USAGE_DEFAULT;
		bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDescription.CPUAccessFlags = 0;
		bufferDescription.MiscFlags = 0;
		bufferDescription.StructureByteStride = 4;

		D3D11_SUBRESOURCE_DATA initData;
		MwMem::Zero(&initData, sizeof(initData));
		initData.pSysMem = this->indexData;
		
		if (FAILED(this->context->device->CreateBuffer(&bufferDescription, &initData, &this->indexBuffer)))
			return false;
	}

	return true;
}

int MwDirect3D11Mesh::GetVertexCount()
{
	return this->vertexCount;
}

int MwDirect3D11Mesh::GetIndexCount()
{
	return this->indexCount;
}

int MwDirect3D11Mesh::GetPrimitiveCount()
{
	return this->indexCount / 3;
}

void MwDirect3D11Mesh::GetVertexPosition(int index, MwVector3 &result)
{
	float *pos = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->positionOffset);
	result.x = *pos++;
	result.y = *pos++;
	result.z = *pos;
}

void MwDirect3D11Mesh::SetVertexPosition(int index, MwVector3 &value)
{
	float *pos = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->positionOffset);
	*pos++ = value.x;
	*pos++ = value.y;
	*pos = value.z;
}

void MwDirect3D11Mesh::GetVertexNormal(int index, MwVector3 &result)
{
	float *normal = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->normalOffset);
	result.x = *normal++;
	result.y = *normal++;
	result.z = *normal;
}

void MwDirect3D11Mesh::SetVertexNormal(int index, MwVector3 &value)
{
	float *normal = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->normalOffset);
	*normal++ = value.x;
	*normal++ = value.y;
	*normal = value.z;
}

void MwDirect3D11Mesh::GetVertexTexCoords(int index, MwVector2 &result)
{
	float *texCoords = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->texCoordsOffset);
	result.x = *texCoords++;
	result.y = *texCoords++;
}

void MwDirect3D11Mesh::SetVertexTexCoords(int index, MwVector2 &value)
{
	float *texCoords = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->texCoordsOffset);
	*texCoords++ = value.x;
	*texCoords++ = value.y;
}

void MwDirect3D11Mesh::GetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights)
{
	float *bone = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->bonesOffset);
	boneIndices.x = *bone++;
	boneIndices.y = *bone++;
	boneIndices.z = *bone++;
	boneIndices.w = *bone++;
	
	boneWeights.x = *bone++;
	boneWeights.y = *bone++;
	boneWeights.z = *bone++;
	boneWeights.w = *bone;
}

void MwDirect3D11Mesh::SetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights)
{
	float *bone = (float*)((unsigned int)this->vertexData + index * this->vertexSize + this->bonesOffset);
	*bone++ = boneIndices.x;
	*bone++ = boneIndices.y;
	*bone++ = boneIndices.z;
	*bone++ = boneIndices.w;

	*bone++ = boneWeights.x;
	*bone++ = boneWeights.y;
	*bone++ = boneWeights.z;
	*bone = boneWeights.w;
}

int MwDirect3D11Mesh::GetIndex(int index)
{
	return this->indexData[index];
}

void MwDirect3D11Mesh::SetIndex(int index, int value)
{
	this->indexData[index] = value;
}
