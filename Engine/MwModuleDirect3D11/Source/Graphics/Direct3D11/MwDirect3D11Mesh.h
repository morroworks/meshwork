#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwDirect3D11GraphicsDevice.h"

class MwDirect3D11Mesh :
	public MwDeviceMesh
{
private:
	void *vertexData;
	int *indexData;

public:
	ID3D11InputLayout*      vertexLayout;
	ID3D11Buffer*           vertexBuffer;
	
	ID3D11Buffer*           indexBuffer;

	int positionOffset, normalOffset, texCoordsOffset, bonesOffset;
	int vertexSize;

	int vertexCount;
	int indexCount;

	MwDirect3D11GraphicsDevice *context;

	MwDirect3D11Mesh(void);
	~MwDirect3D11Mesh(void);

	virtual bool CreateVertexBuffer(int numVertices);
	virtual bool CreateIndexBuffer(int numIndices);

	virtual bool DeleteVertexBuffer();
	virtual bool DeleteIndexBuffer();

	virtual bool UpdateVertices(int offset, int count);
	virtual bool UpdateIndices(int offset, int count);

	virtual int GetVertexCount();
	virtual int GetIndexCount();
	virtual int GetPrimitiveCount();

	virtual void GetVertexPosition(int index, MwVector3 &result);
	virtual void SetVertexPosition(int index, MwVector3 &value);

	virtual void GetVertexNormal(int index, MwVector3 &result);
	virtual void SetVertexNormal(int index, MwVector3 &value);

	virtual void GetVertexTexCoords(int index, MwVector2 &result);
	virtual void SetVertexTexCoords(int index, MwVector2 &value);

	virtual void GetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights);
	virtual void SetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights);

	virtual int GetIndex(int index);
	virtual void SetIndex(int index, int value);
};

