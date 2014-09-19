#pragma once

#include "..\..\..\MwGlobals.h"

#include "Primitive\SrLight.h"
#include "Primitive\SrMatrix.h"
#include "Primitive\SrMaterial.h"
#include "Primitive\SrShadingParameters.h"
#include "Primitive\SrVector3.h"
#include "Primitive\SrCullModes.h"
#include "Primitive\SrTextureSamplers.h"
#include "Primitive\SrShaderOperations.h"

#include "SrMesh.h"
#include "SrTexture.h"
#include "SrRenderThread.h"

#include "..\..\..\Tools\Threading\MwThreadsPool.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<SrRenderThread*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<SrShaderOperation>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<SrTexture*>;

class MWDLLCLASS Soras
{
private:
    MwList<SrRenderThread*> renderThreads;

	MwThreadsPool *threadsPool;

	bool NormalizationNecessary();

public:
    SrLight *lights;
    int numLights, maxLights;
    bool normalizeNormals, wireFrame;
    int numVisiblePrimitives;
    int cull_PrimitiveIndex;

    float *zBuffer, *zBufferStencil;
	unsigned int zBufferSize;
	SrARGB clearColor;
    SrMatrix worldMatrix, worldMatrixNormals, viewProjectionMatrix;
    SrMaterial material;
    SrARGBInt materialAmbient;
    SrShadingParameters shadingParameters;
    SrVector3 camPos;

	SrMatrix *bones;
	int maxBones;
	bool skeletalAnimationOn;

	SrMesh *mesh;

	SrTexture *renderSurface;

    SrCullMode cullMode;
	SrTextureSampler textureSampler;
    MwList<SrShaderOperation> vertexOps, pixelOps;
    MwList<SrTexture*> shaderTextures;
    SrShaderOperation blending;

	Soras(void);
	~Soras(void);

	void Clear(SrARGB color);
	void ClearZ();

	void SetThreadCount(int threadCount);

	void SetRenderSurface(SrTexture *renderSurface);

	void SetMesh(SrMesh *mesh);

	void ClearShaderOperations();
	void AddVertexShader(SrShaderOperation shaderOperation, SrShaderOperation colorOperation);
	void AddPixelShader(SrShaderOperation shaderOperation, SrShaderOperation colorOperation, SrTexture* texture);

	void SetLighsCount(int numLights);

	void RenderMesh();
};

