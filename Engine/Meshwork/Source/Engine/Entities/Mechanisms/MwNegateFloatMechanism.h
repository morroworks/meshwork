#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

class MWDLLCLASS MwNegateFloatMechanism
	: public MwBaseMechanism
{
public:
	static const int classId = MwBaseMechanism::classId | 2;

	MwNegateFloatMechanism(float value);
	~MwNegateFloatMechanism(void);

	bool Process(float deltaTime);
};

