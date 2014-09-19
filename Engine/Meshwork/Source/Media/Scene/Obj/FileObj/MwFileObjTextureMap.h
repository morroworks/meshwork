#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\MwString.h"

#include "MwFileObjPrimitiveTypes.h"

class MwFileObjTextureMap
{
public:
	MwString fileName;
	MwFileObjVector3 offset, scale, turbulence;

	float brightness, contrastFactor, bumpFactor, mipMapSharpness;

	int resolution;

	bool clamp, blendU, blendV;

	MwFileObjTextureMapType mapType;
	MwFileObjTextureMapChannel mapChannel;

	MwFileObjTextureMap(void);
	~MwFileObjTextureMap(void);
};

