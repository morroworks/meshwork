#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

class MWDLLCLASS MwPlanarTexCoords
{
public:
	MwPlanarTexCoords(MwDeviceMesh &result, MwVector3 &planeX, MwVector3 &planeY);
	~MwPlanarTexCoords(void);
};

