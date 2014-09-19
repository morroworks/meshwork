#pragma once

#include "..\..\..\MwGlobals.h"

#include "Primitive\SrVertex.h"

class MWDLLCLASS SrMesh
{
public:
    int *indices;
	int numIndices;

	SrVertex *vertices, *transformedVertices;
    int numVertices;

    int *visiblePrimitives;
    int numVisiblePrimitives;

	SrMesh(void);
	SrMesh(SrMesh &original);
	~SrMesh(void);

	void SetIndexCount(int numIndices);
	void SetVertexCount(int numVertices);
};

