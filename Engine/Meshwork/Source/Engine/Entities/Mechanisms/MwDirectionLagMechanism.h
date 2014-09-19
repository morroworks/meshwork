#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

#include "..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwDirectionLagMechanism
	: public MwBaseMechanism
{
private:
    MwVector3 lastSpherical;

public:
	static const int classId = MwBaseMechanism::classId | 6;

	MwDirectionLagMechanism(void);
	~MwDirectionLagMechanism(void);

	bool Process(float deltaTime);
};

