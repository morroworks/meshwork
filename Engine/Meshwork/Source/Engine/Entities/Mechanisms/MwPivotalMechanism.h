#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Primitive\MwVector3.h"

#include "MwBaseMechanism.h"

class MWDLLCLASS MwPivotalMechanism
	: public MwBaseMechanism
{
private:
	    MwVector3 gravityVector, targetPos, targetMoveVector;

public:
	static const int classId = MwBaseMechanism::classId | 8;

	MwPivotalMechanism(void);
	~MwPivotalMechanism(void);

	bool Process(float deltaTime);
};

