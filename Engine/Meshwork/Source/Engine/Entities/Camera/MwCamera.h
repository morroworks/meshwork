#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwMath.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\Primitive\MwMatrix.h"
#include "..\..\Primitive\MwVector3.h"

class Meshwork;

class MWDLLCLASS MwCamera
	: public MwBaseResource
{
public:
	static const int classId = (MwResourceType_Camera << 16) | 0;

	static const int propertyIndex_Aspect = 0;
	static const int propertyIndex_FOV = 1;
	static const int propertyIndex_OrthoZoom = 2;
	static const int propertyIndex_Orthographic = 3;

	Meshwork *context;

	MwMatrix view, projection, viewProjection;
    MwVector3 position, lookAt, xAxis, yAxis, zAxis;

	MwCamera(Meshwork *context);
	~MwCamera(void);

    void BuildMatrix(MwMatrix &transform);
};

