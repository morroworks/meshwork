#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

class MWDLLCLASS MwLight :
	public MwBaseResource
{
public:
	static const int classId = (MwResourceType_Light << 16) | 0;

	static const int propertyIndex_Active = 0;
	static const int propertyIndex_Color = 1;
	static const int propertyIndex_Intensity = 2;

public:
	MwLight(void);
	~MwLight(void);
};

