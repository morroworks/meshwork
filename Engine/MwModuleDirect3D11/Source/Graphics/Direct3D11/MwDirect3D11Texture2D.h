#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwDirect3D11GraphicsDevice.h"

class MwDirect3D11Texture2D :
	public MwDeviceTexture2D
{

public:
	int width, height;
	bool isRenderTarget;
	
	void Create(void *data, int width, int height, bool isRenderTarget);
	void Fill(void *data);
	void Release();

	ID3D11Texture2D *deviceTexture;
	ID3D11ShaderResourceView *deviceShaderResourceView;
	ID3D11RenderTargetView *deviceRenderTargetView;
	ID3D11Texture2D *deviceRenderTargetDepthStencil;
	ID3D11DepthStencilView *deviceRenderTargetDepthStencilView;

	ID3D11SamplerState *deviceSampler;

	MwDirect3D11GraphicsDevice *context;

	MwDirect3D11Texture2D(void);
	~MwDirect3D11Texture2D(void);

	void Update(void *data, int width, int height);
	void GetData(void *data);
};

