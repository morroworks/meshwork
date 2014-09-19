#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

class MWDLLCLASS MwSineMechanism
	: public MwBaseMechanism
{
private:
    float u;

public:
	static const int classId = MwBaseMechanism::classId | 4;

	MwSineMechanism(float min, float max, float time, bool loop);
	~MwSineMechanism(void);

	bool Process(float deltaTime);
};

