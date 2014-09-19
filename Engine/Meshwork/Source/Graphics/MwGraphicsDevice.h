#pragma once

#include "..\MwGlobals.h"

#include "..\Engine\Primitive\MwShaderOperation.h"
#include "..\Engine\Primitive\MwColorOperation.h"
#include "..\Engine\Primitive\MwRenderState.h"
#include "..\Engine\Primitive\MwVector4.h"
#include "..\Engine\Primitive\MwMatrix.h"
#include "..\Engine\Primitive\MwPixelFormat.h"

#include "MwDeviceMesh.h"
#include "MwDeviceTexture2D.h"
#include "MwDeviceShader.h"


class MWDLLCLASS MwGraphicsDevice
{
public:
	MwGraphicsDevice(void);
	virtual ~MwGraphicsDevice(void);

	virtual MwDeviceMesh *CreateMesh() = 0;
	virtual MwDeviceTexture2D *CreateTexture() = 0;
	virtual MwDeviceShader *CreateShader() = 0;

	virtual bool SetRenderTargetWindow(void *windowHandle) = 0;
	virtual bool SetRenderTargetTexture(MwDeviceTexture2D *texture) = 0;

	virtual MwPixelFormat GetPixelFormat() = 0;

	virtual void Clear(MwVector4 &color) = 0;

	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	
	virtual void SetViewport(int x, int y, int width, int height) = 0;
	
	virtual void SetMesh(MwDeviceMesh &mesh) = 0;

	// TODO: these should all be set through SetShaderParameter
	//virtual void SetModelAnimation(bool enabled) = 0;
	//virtual void SetModelBone(int boneIndex, MwMatrix &bone) = 0;

	//virtual void SetModelTransform(MwMatrix &transform) = 0;
	//virtual void SetViewTransform(MwMatrix &transform) = 0;
	//virtual void SetProjectionTransform(MwMatrix &transform) = 0;

	
	virtual void SetShader(MwDeviceShader &shader) = 0;

	//virtual int CreateShader();
	//virtual int CreateShader(void *shader);
	//virtual void AddShaderLayer(int shaderId, layerEffect);
	//virtual void FinalizeShader(int shaderId);
	//virtual void SetShader(int shaderId);
	//virtual void SetShaderParameter(int shaderId, int parameterIndex, void *parameterValue);

	//virtual void SetShader(void *shader) = 0;
	//virtual void SetShaderParameter(int parameter, void *value) = 0;

	virtual void SetRenderState(MwRenderState renderState) = 0;

	virtual void RenderMesh() = 0;

	virtual bool Present() = 0;
};

