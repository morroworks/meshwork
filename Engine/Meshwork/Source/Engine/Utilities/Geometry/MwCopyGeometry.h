#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

class MWDLLCLASS MwCopyGeometry
{
public:
	MwCopyGeometry(MwDeviceMesh &result, MwDeviceMesh &source);
	~MwCopyGeometry(void);
};

