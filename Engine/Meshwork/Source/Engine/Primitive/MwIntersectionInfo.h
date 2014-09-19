#pragma once

#include "..\..\MwGlobals.h"

#include "MwVertex.h"

class MWDLLCLASS MwIntersectionInfo
{
public:
	MwVertex point;
    float distance;
    int primitiveIndex;
    bool intersection;

	MwIntersectionInfo(void);
	~MwIntersectionInfo(void);
};

