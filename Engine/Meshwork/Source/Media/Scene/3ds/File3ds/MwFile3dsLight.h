#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsPrimitiveTypes.h"

#include "MwFile3dsBaseObject.h"

class MWDLLCLASS MwFile3dsLight :
	public MwFile3dsBaseObject
{
public:
	bool active;
	MwFile3dsVector position;
	MwFile3dsColorFloat color;
	bool spotLight;
	MwFile3dsVector spotlight_Target;
	float spotlight_Hotspot, spotlight_Falloff;

	MwFile3dsLight(void);
	~MwFile3dsLight(void);
};

