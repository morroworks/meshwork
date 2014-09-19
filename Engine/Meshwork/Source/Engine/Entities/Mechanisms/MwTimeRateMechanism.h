#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

class Meshwork;

class MWDLLCLASS MwTimeRateMechanism :
	public MwBaseMechanism
{
private:
	Meshwork *context;

public:
	static const int classId = MwBaseMechanism::classId | 11;

	MwTimeRateMechanism(Meshwork *context);
	~MwTimeRateMechanism(void);

	bool Process(float deltaTime);
};

