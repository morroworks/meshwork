#pragma once

#include "..\..\..\MwGlobals.h"

#include "Primitive\SrARGBInt.h"
#include "Primitive\SrVertex.h"

#include "SrTexture.h"

#include "..\..\..\Tools\MwList.h"

class Soras;

class MWDLLCLASS SrRenderThread
{
public:
    SrARGBInt shaderReg_ColorArg;
    SrVertex *shaderReg_Point;
    SrTexture *shaderReg_Texture;
    int shaderTextureIndex;

	int vertexStart, vertexEnd,
		primitiveStart, primitiveEnd;
        
    Soras *soras;

	SrRenderThread(Soras *soras);
	~SrRenderThread(void);

	void RenderPrimitive(SrVertex *V1, SrVertex *V2, SrVertex *V3);
	void RenderScanLine(SrVertex *p1, SrVertex *p2);

	static int ComputeVertices(void *renderThread);
	static int RenderPrimitives(void *renderThread);
};

