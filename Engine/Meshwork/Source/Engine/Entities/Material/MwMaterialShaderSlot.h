#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Primitive\MwShaderOperation.h"
#include "..\..\Primitive\MwColorOperation.h"

class MWDLLCLASS MwMaterialShaderSlot
{
public:
	MwMaterialShaderSlot(void);
	MwMaterialShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp, int propertyFirst, int propertyCount);
	~MwMaterialShaderSlot(void);

	MwShaderOperation shaderOp;
    MwColorOperation colorOp;
    int propertyFirst, propertyCount;
};

