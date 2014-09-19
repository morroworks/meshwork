#pragma once

#include "..\MwGlobals.h"

#include "..\Engine\Primitive\MwVector2.h"
#include "..\Engine\Primitive\MwVector3.h"
#include "..\Engine\Primitive\MwVector4.h"

class MWDLLCLASS MwDeviceMesh
{
public:
	MwDeviceMesh(void);
	virtual ~MwDeviceMesh(void);

	virtual void CopyFrom(MwDeviceMesh *source);

	virtual bool CreateVertexBuffer(int numVertices) = 0;
	virtual bool CreateIndexBuffer(int numIndices) = 0;

	virtual bool DeleteVertexBuffer() = 0;
	virtual bool DeleteIndexBuffer() = 0;

	virtual bool UpdateVertices(int offset, int count) = 0;
	virtual bool UpdateIndices(int offset, int count) = 0;

	virtual int GetVertexCount() = 0;
	virtual int GetIndexCount() = 0;
	virtual int GetPrimitiveCount() = 0;

	virtual void GetVertexPosition(int index, MwVector3 &result) = 0;
	virtual void SetVertexPosition(int index, MwVector3 &value) = 0;

	virtual void GetVertexNormal(int index, MwVector3 &result) = 0;
	virtual void SetVertexNormal(int index, MwVector3 &value) = 0;

	virtual void GetVertexTexCoords(int index, MwVector2 &result) = 0;
	virtual void SetVertexTexCoords(int index, MwVector2 &value) = 0;

	virtual void GetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights) = 0;
	virtual void SetVertexBones(int index, MwVector4 &boneIndices, MwVector4 &boneWeights) = 0;

	virtual int GetIndex(int index) = 0;
	virtual void SetIndex(int index, int value) = 0;
};

