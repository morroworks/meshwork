#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\MwList.h"

struct MwFileObjVector3
{
	float x, y, z;
};

struct MwFileObjVector4
{
	float x, y, z, w;
};

struct MwFileObjFaceVertex
{
	int vertexIndex;
	int normalIndex;
	int texCoordIndex;
};

struct MwFileObjFace
{
	MwList<MwFileObjFaceVertex> vertices;
	unsigned int smoothingGroups;
};

struct MwFileObjBufferedFace
{
	MwList<int> bufferedVertexIndices;
	unsigned int smoothingGroups;
};


enum MwFileObjTextureMapType
{
	MwFileObjTextureMapType_Default,
	MwFileObjTextureMapType_Sphere,
	MwFileObjTextureMapType_CubeTop,
	MwFileObjTextureMapType_CubeBottom,
	MwFileObjTextureMapType_CubeFront,
	MwFileObjTextureMapType_CubeBack,
	MwFileObjTextureMapType_CubeLeft,
	MwFileObjTextureMapType_CubeRight
};

enum MwFileObjTextureMapChannel
{
	MwFileObjTextureMapChannel_Default,
	MwFileObjTextureMapChannel_R,
	MwFileObjTextureMapChannel_G,
	MwFileObjTextureMapChannel_B,
	MwFileObjTextureMapChannel_Matte,
	MwFileObjTextureMapChannel_Luminance,
	MwFileObjTextureMapChannel_Depth
};