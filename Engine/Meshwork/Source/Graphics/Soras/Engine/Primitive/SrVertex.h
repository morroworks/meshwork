#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "SrVector3.h"
#include "SrVector3Int.h"
#include "SrVector2Int.h"
#include "SrVector4.h"
#include "SrVector4Int.h"
#include "SrARGBInt.h"

struct SrVertex
{
    SrVector3 position, normal;
    SrVector3Int positionIntScreen;
    SrVector2Int texCoords;
	SrVector4Int boneIndices;
	SrVector4 boneWeights;
    SrARGBInt color;
};