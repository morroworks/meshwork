#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

#include "..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwBoxGeometry
{
private:
	void CreateGeometry(MwDeviceMesh &result, int xSegments, int ySegments, int zSegments, MwVector3 &xAxis, MwVector3 &yAxis, MwVector3 &zAxis);

public:
	MwBoxGeometry(MwDeviceMesh &result, int xSegments, int ySegments, int zSegments, MwVector3 &xAxis, MwVector3 &yAxis, MwVector3 &zAxis);
	MwBoxGeometry(MwDeviceMesh &result, int xSegments, int ySegments, int zSegments);
	~MwBoxGeometry(void);
};

