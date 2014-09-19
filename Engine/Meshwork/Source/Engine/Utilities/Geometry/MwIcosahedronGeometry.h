#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

class MWDLLCLASS MwIcosahedronGeometry
{
public:
	MwIcosahedronGeometry(MwDeviceMesh &result, float radius = 1.0f);
	~MwIcosahedronGeometry(void);
};

