#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsPrimitiveTypes.h"

#include "..\..\..\..\Tools\MwString.h"

class MWDLLCLASS MwFile3dsMaterial
{
public:
	MwString name;
	MwFile3dsColorByte ambient, diffuse, specular;
	float specularLevel, glossiness;
	bool hasAmbient, hasDiffuse, hasSpecular;
	MwString colorMap, specularMap, bumpMap, reflectionMap;

	MwFile3dsMaterial(void);
	~MwFile3dsMaterial(void);
};

