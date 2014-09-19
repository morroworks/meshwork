#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

class MWDLLCLASS MwFloatMechanism
	: public MwBaseMechanism
{
public:
	static const int classId = MwBaseMechanism::classId | 1;

	MwFloatMechanism(float value);
	~MwFloatMechanism(void);

	bool Process(float deltaTime);
};

