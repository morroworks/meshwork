#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwGraphicsDevice.h"

#include "Engine\Soras.h"

#include "..\..\Tools\OS\MwDrawSurface.h"

class MWDLLCLASS MwSorasGraphicsDevice :
	public MwGraphicsDevice
{
private:
	MwMatrix viewProjection;

	void *windowHandle_HWND;
	void *deviceContext_HDC;

	MwPixelFormat pixelFormat;

public:
	Soras *soras;
	MwDrawSurface *drawSurface;

	MwSorasGraphicsDevice();
	~MwSorasGraphicsDevice(void);

	virtual MwDeviceMesh *CreateMesh();
	virtual MwDeviceTexture2D *CreateTexture();
	virtual MwDeviceShader *CreateShader();

	virtual bool SetRenderTargetWindow(void *windowHandle);
	virtual bool SetRenderTargetTexture(MwDeviceTexture2D *texture);

	virtual MwPixelFormat GetPixelFormat();

	virtual void Clear(MwVector4 &color);

	virtual void BeginScene();
	virtual void EndScene();
	
	virtual void SetViewport(int x, int y, int width, int height);
	
	virtual void SetMesh(MwDeviceMesh &mesh);

	virtual void SetShader(MwDeviceShader &shader);

	virtual void SetRenderState(MwRenderState renderState);

	virtual void RenderMesh();

	virtual bool Present();
};

