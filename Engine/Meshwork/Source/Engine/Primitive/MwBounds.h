#pragma once

#include "..\..\MwGlobals.h"

#include "MwVector3.h"

class MwMatrix;

class MWDLLCLASS MwBounds
{
public:
	MwVector3 center, box;
    float sphere;

	MwBounds(void);
	~MwBounds(void);

	bool InsideViewFrustum(MwMatrix &transform);
};

