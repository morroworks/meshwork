#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwDeviceMesh.h"

class MWDLLCLASS MwDeviceIndependentMesh
	: public MwDeviceMesh
{
public:
	float *positions, *normals, *texCoords, *boneIndices, *boneWeights;
	unsigned short *indices;
	int numIndices, numVertices;

	MwDeviceIndependentMesh(void);
	virtual ~MwDeviceIndependentMesh(void);

	bool CreateVertexBuffer(int numVertices);
	bool CreateIndexBuffer(int numIndices);
	
	bool DeleteVertexBuffer();
	bool DeleteIndexBuffer();

	bool UpdateVertices(int offset, int count);
	bool UpdateIndices(int offset, int count);

	int GetVertexCount();
	int GetIndexCount();
	int GetPrimitiveCount();

	void GetVertexPosition(int index, MwVector3 &result);
	void SetVertexPosition(int index, MwVector3 &value);

	void GetVertexNormal(int index, MwVector3 &result);
	void SetVertexNormal(int index, MwVector3 &value);

	void GetVertexTexCoords(int index, MwVector2 &result);
	void SetVertexTexCoords(int index, MwVector2 &value);

	void GetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights);
	void SetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights);

	int GetIndex(int index);
	void SetIndex(int index, int value);
};

