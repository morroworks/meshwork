#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwList.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<int>;

class MWDLLCLASS MwConvexHullGeometry
{
private:
	MwDeviceMesh *result;
	MwList<int> indices, modifyIndices;

	bool IsOutside(int vertexIndex, int triangleIndex);

public:
	MwConvexHullGeometry(MwDeviceMesh &result);
	~MwConvexHullGeometry(void);
};

