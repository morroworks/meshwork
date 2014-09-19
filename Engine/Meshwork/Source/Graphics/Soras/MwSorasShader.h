#pragma once

#include "..\DeviceIndependent\MwDeviceIndependentShader.h"

#include "Engine\Soras.h"

#include "..\..\Engine\Primitive\MwVector4.h"
#include "..\..\Engine\Primitive\MwMatrix.h"

class MwSorasGraphicsDevice;

class MwSorasShader :
	public MwDeviceIndependentShader
{
private:
	// Indices to pixelOpsTextures, -1 if not used.
	int colorMapIndex, envMapIndex, normalMapIndex, refractionMapIndex;

	void MwToSrARGBInt(SrARGBInt &result, MwVector4 &source);

public:
	MwSorasGraphicsDevice *context;

	bool isAnimated;
	MwMatrix viewMatrix, projectionMatrix;

	MwList<SrShaderOperation> vertexShaderOps, vertexColorOps, pixelShaderOps, pixelColorOps;
	MwList<SrTexture*> pixelOpsTextures;

	MwSorasShader(void);
	virtual ~MwSorasShader(void);

	virtual int GetParameterAddress(MwString parameterName);
	virtual void SetParameter(int address, int index, void *value);

	virtual bool Update(MwString &compilationMessage);
};

