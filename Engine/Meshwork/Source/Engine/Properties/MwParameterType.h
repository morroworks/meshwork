#pragma once

#include "..\..\MwGlobals.h"

enum MwParameterType
{
    MwParameterType_None = 0,
    MwParameterType_Int = 1,
    MwParameterType_Float = 2,
    MwParameterType_Bool = 3,
    MwParameterType_Color = 4,
    MwParameterType_ReferenceVector3 = 5,
    MwParameterType_ReferenceTexture = 6,
    MwParameterType_ReferenceCamera = 7,
    MwParameterType_ReferenceMechanism = 8,
    MwParameterType_ReferenceTransform = 9,
	MwParameterType_ReferenceSound = 10
};