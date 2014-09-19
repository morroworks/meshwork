#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\MwString.h"

#include "MwFileObjPrimitiveTypes.h"
#include "MwFileObjTextureMap.h"

class MWDLLCLASS MwFileObjMaterial
{
public:
	MwString name;

	MwFileObjTextureMap *ambientMap, *diffuseMap, *specularColorMap, *specularHighlightMap, *alphaMap, *bumpMap, *displacementMap, *stencilMap, *reflectionMap;
	
	MwFileObjVector3 ambientColor, diffuseColor, specularColor;
	float specularFactor;
	float transparency;

	MwFileObjMaterial(void);
	~MwFileObjMaterial(void);
};

