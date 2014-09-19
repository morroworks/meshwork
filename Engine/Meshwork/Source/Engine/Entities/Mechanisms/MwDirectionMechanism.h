#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

#include "..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwDirectionMechanism
	: public MwBaseMechanism
{
private:
    MwVector3 lastSpherical;

public:
	static const int classId = MwBaseMechanism::classId | 5;

	MwDirectionMechanism(void);
	~MwDirectionMechanism(void);

	bool Process(float deltaTime);
};

