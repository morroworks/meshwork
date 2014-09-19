#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

class MWDLLCLASS MwLinearInterpolationMechanism :
	public MwBaseMechanism
{
public:
	static const int classId = MwBaseMechanism::classId | 10;

	static const int propertyIndex_Min = 0;
	static const int propertyIndex_Max = 1;
	static const int propertyIndex_Argument = 2;

	MwLinearInterpolationMechanism(float min, float max, float argument);
	~MwLinearInterpolationMechanism(void);

	bool Process(float deltaTime);
};

