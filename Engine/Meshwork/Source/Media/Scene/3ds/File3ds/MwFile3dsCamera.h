#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsPrimitiveTypes.h"

#include "MwFile3dsBaseObject.h"

class MWDLLCLASS MwFile3dsCamera :
	public MwFile3dsBaseObject
{
public:
	MwFile3dsVector position, target;
	float bank, lens;

	MwFile3dsCamera(void);
	~MwFile3dsCamera(void);
};

