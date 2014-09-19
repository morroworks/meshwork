#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

class MWDLLCLASS MwLinearMechanism
	: public MwBaseMechanism
{
public:
	static const int classId = MwBaseMechanism::classId | 3;

	static const int propertyIndex_Min = 0;
	static const int propertyIndex_Max = 1;
	static const int propertyIndex_Speed = 2;
	static const int propertyIndex_Loop = 3;
	//static const int propertyIndex_Oscilate = 4; // requries an additional back/forth variable OR make it analogous to sine

	MwLinearMechanism(float min, float max, float speed, bool loop);
	~MwLinearMechanism(void);

	bool Process(float deltaTime);
};

