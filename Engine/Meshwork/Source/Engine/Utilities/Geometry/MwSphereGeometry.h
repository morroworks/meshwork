#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

#include "..\..\..\Tools\MwList.h"

struct MWDLLCLASS MwEdge
{
	int index1, index2;
	int subIndex;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwEdge>;

class MWDLLCLASS MwSphereGeometry
{
	MwList<MwEdge> edges;
	MwDeviceMesh *result;
	int currentIndex, currentVertexIndex;
	float radius;

	void SubDivideTriangle(int triangleIndex, int subLevel);
	int GetEdgeSubIndex(int edgeIndex1, int edgeIndex2);

public:
	MwSphereGeometry(MwDeviceMesh &result, float radius, int subDivisions);
	~MwSphereGeometry(void);

};

