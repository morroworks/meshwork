#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

#include "..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwPlaneGeometry
{
private:
	void CreateGeometry(MwDeviceMesh &result, int xSegments, int ySegments, MwVector3 &xAxis, MwVector3 &yAxis);

public:
	MwPlaneGeometry(MwDeviceMesh &result, int xSegments, int ySegments, MwVector3 &xAxis, MwVector3 &yAxis);
	MwPlaneGeometry(MwDeviceMesh &result, int xSegments, int ySegments);
	~MwPlaneGeometry(void);
};

