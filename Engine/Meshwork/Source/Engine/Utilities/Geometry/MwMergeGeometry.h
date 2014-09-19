#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Graphics\MwDeviceMesh.h"

#include "..\..\Primitive\MwMatrix.h"

class MWDLLCLASS MwMergeGeometry
{
public:
	MwMergeGeometry(MwDeviceMesh &result, MwDeviceMesh &geometry1, MwMatrix &transform1, MwDeviceMesh &geometry2, MwMatrix &transform2);
	MwMergeGeometry(MwDeviceMesh &result, MwDeviceMesh &geometry1, MwDeviceMesh &geometry2);
	~MwMergeGeometry(void);

	void CreateGeometry(MwDeviceMesh &result, MwDeviceMesh &geometry1, MwMatrix &transform1, MwDeviceMesh &geometry2, MwMatrix &transform2);
};

