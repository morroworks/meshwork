#pragma once

#include "..\..\MwGlobals.h"

#include "MwVector3.h"
#include "MwVector2.h"

class MWDLLCLASS MwVertex
{
public:
	MwVector3 position, normal;
    MwVector2 texCoords;

	MwVertex(void);
	~MwVertex(void);
};

