#pragma once

#include "..\..\MeshworkEngine.h"

#include <windows.h>

#include <Direct3D11\D3D11.h>

class MwDirect3D11Mesh;
class MwDirect3D11Shader;
class MwDirect3D11Texture2D;

class MwDirect3D11GraphicsDevice :
	public MwGraphicsDevice
{
private:
	int width, height;

	MwDirect3D11Mesh *currentMesh;
	MwDirect3D11Shader *currentShader;
	//MwDirect3D11Texture2D *currentRenderTarget;
	ID3D11RenderTargetView *currentRenderTargetView;
	ID3D11DepthStencilView *currentRenderTargetDepthStencilView;

	MwMatrix viewProjection;

public:
	D3D_DRIVER_TYPE         deviceDriverType;
	D3D_FEATURE_LEVEL       deviceFeatureLevel;
	ID3D11Device*           device;
	ID3D11DeviceContext*    deviceContext;
	IDXGISwapChain*         deviceSwapChain;
	ID3D11RenderTargetView* deviceRenderTargetView;
	ID3D11DepthStencilView* deviceRenderTargetDepthStencilView;


	MwDirect3D11GraphicsDevice(void);
	~MwDirect3D11GraphicsDevice(void);

	MwDeviceMesh *CreateMesh();
	MwDeviceTexture2D *CreateTexture();
	MwDeviceShader *CreateShader();

	MwDeviceTexture2D *defaultTexture;

	bool SetRenderTargetWindow(void *windowHandle);
	bool SetRenderTargetTexture(MwDeviceTexture2D *texture);
	
	MwPixelFormat GetPixelFormat();

	void Clear(MwVector4 &color);

	void BeginScene();
	void EndScene();
	
	void SetViewport(int x, int y, int width, int height);
	
	void SetMesh(MwDeviceMesh &mesh);

	void SetShader(MwDeviceShader &shader);

	void SetRenderState(MwRenderState renderState);

	void RenderMesh();

	bool Present();
};

