#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwTransformOperation.h"

class MWDLLCLASS MwTransformSlot
{
public:
	MwTransformOperation operation;
    int propertyFirst, propertyCount;

	MwTransformSlot(void);
	MwTransformSlot(MwTransformOperation operation, int propertyFirst, int propertyCount);
	~MwTransformSlot(void);
};

