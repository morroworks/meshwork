//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwDirect3D11GraphicsDevice.h"

#include "MwDirect3D11Mesh.h"
#include "MwDirect3D11Shader.h"
#include "MwDirect3D11Texture2D.h"

#include <Direct3D11\xnamath.h>

MwDirect3D11GraphicsDevice::MwDirect3D11GraphicsDevice(void)
{
	this->deviceDriverType = D3D_DRIVER_TYPE_NULL;
	this->deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	this->device = NULL;
	this->deviceContext = NULL;
	this->deviceSwapChain = NULL;
	this->deviceRenderTargetView = NULL;
	this->deviceRenderTargetDepthStencilView = NULL;

	this->defaultTexture = 0;
}

MwDirect3D11GraphicsDevice::~MwDirect3D11GraphicsDevice(void)
{
	if (this->defaultTexture != 0)
		delete this->defaultTexture;

	if (this->deviceContext != NULL)
		this->deviceContext->ClearState();

	if (this->deviceRenderTargetDepthStencilView != NULL)
		this->deviceRenderTargetDepthStencilView->Release();
	if (this->deviceRenderTargetView != NULL)
		this->deviceRenderTargetView->Release();
	if (this->deviceSwapChain)
		this->deviceSwapChain->Release();
    if (this->deviceContext)
		this->deviceContext->Release();
	if (this->device)
		this->device->Release();
}

MwDeviceMesh *MwDirect3D11GraphicsDevice::CreateMesh()
{
	MwDirect3D11Mesh *mesh = new MwDirect3D11Mesh();
	mesh->context = this;
	return mesh;
}

MwDeviceTexture2D *MwDirect3D11GraphicsDevice::CreateTexture()
{
	MwDirect3D11Texture2D *texture = new MwDirect3D11Texture2D();
	texture->context = this;
	return texture;
}

MwDeviceShader *MwDirect3D11GraphicsDevice::CreateShader()
{
	MwDirect3D11Shader *shader = new MwDirect3D11Shader();
	shader->context = this;
	return shader;
}

bool MwDirect3D11GraphicsDevice::SetRenderTargetWindow(void *windowHandle)
{
	if (this->device != 0)
	{
		if (this->currentRenderTargetView == this->deviceRenderTargetView)
			return true;
		
		this->currentRenderTargetView = this->deviceRenderTargetView;
		this->currentRenderTargetDepthStencilView = this->deviceRenderTargetDepthStencilView;
		this->deviceContext->OMSetRenderTargets(1, &this->currentRenderTargetView, this->currentRenderTargetDepthStencilView);
		this->SetViewport(0, 0, this->width, this->height);

		return true;
	}
    
	HRESULT result = S_OK;

	// Set up parameters needed to create the device

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Window size
	MwOSUtils::GetWindowClientSize(windowHandle, this->width, this->height);

	// Swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));
    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Width = this->width;
	swapChainDescription.BufferDesc.Height = this->height;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow = *(HWND*)windowHandle;
    swapChainDescription.SampleDesc.Count = 1;
    swapChainDescription.SampleDesc.Quality = 0;
    swapChainDescription.Windowed = TRUE;

	// Driver types
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    // Feature levels
	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );
	
    // Use the parameters to create a device
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
		this->deviceDriverType = driverTypes[driverTypeIndex];
		result = 
			D3D11CreateDeviceAndSwapChain(
			NULL,
			this->deviceDriverType,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION, 
			&swapChainDescription, 
			&this->deviceSwapChain, 
			&this->device, 
			&this->deviceFeatureLevel, 
			&this->deviceContext);

        if(SUCCEEDED(result))
            break;
    }

    if (FAILED(result))
		return false;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    result = this->deviceSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(result))
        return false;

	result = this->device->CreateRenderTargetView(pBackBuffer, NULL, &this->deviceRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(result))
        return false;

	// Create depth stencil texture
	ID3D11Texture2D* depthStencil = NULL;
	D3D11_TEXTURE2D_DESC depthStencilDescription;
	MwMem::Zero(&depthStencilDescription, sizeof(depthStencilDescription));
	depthStencilDescription.Width = this->width;
	depthStencilDescription.Height = this->height;
	depthStencilDescription.MipLevels = 1;
	depthStencilDescription.ArraySize = 1;
	depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;//DXGI_FORMAT_R32_TYPELESS;
	depthStencilDescription.SampleDesc.Count = 1;
	depthStencilDescription.SampleDesc.Quality = 0;
	depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;//D3D10_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
	depthStencilDescription.CPUAccessFlags = 0;
	depthStencilDescription.MiscFlags = 0;
	if (FAILED(this->device->CreateTexture2D(&depthStencilDescription, NULL, &depthStencil)))
		return false;


	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC renderTargetDepthStencilViewDescription;
	MwMem::Zero(&renderTargetDepthStencilViewDescription, sizeof(renderTargetDepthStencilViewDescription));
	renderTargetDepthStencilViewDescription.Format = depthStencilDescription.Format;//DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	renderTargetDepthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	renderTargetDepthStencilViewDescription.Texture2D.MipSlice = 0;
	if (FAILED(this->device->CreateDepthStencilView(depthStencil, &renderTargetDepthStencilViewDescription, &this->deviceRenderTargetDepthStencilView)))
		return false;
	
	this->currentRenderTargetView = this->deviceRenderTargetView;
	this->currentRenderTargetDepthStencilView = this->deviceRenderTargetDepthStencilView;
	this->deviceContext->OMSetRenderTargets(1, &this->currentRenderTargetView, this->currentRenderTargetDepthStencilView);

    //D3D11_VIEWPORT vp;
    //vp.Width = (FLOAT)windowWidth;
    //vp.Height = (FLOAT)windowHeight;
    //vp.MinDepth = 0.0f;
    //vp.MaxDepth = 1.0f;
    //vp.TopLeftX = 0.0f;
    //vp.TopLeftY = 0.0f;
	//this->deviceContext->RSSetViewports(1, &vp);

	this->SetViewport(0, 0, this->width, this->height);

	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	
	
	//D3D11_RASTERIZER_DESC rasterizerDescription;

	//// Get current rs and descr
	//ID3D11RasterizerState *rs;
	//this->deviceContext->RSGetState(&rs);
	//rs->GetDesc(&rasterizerDescription);

	//rasterizerDescription.FillMode = D3D11_FILL_SOLID;
	//rasterizerDescription.CullMode = D3D11_CULL_BACK;
	//rasterizerDescription.FrontCounterClockwise = FALSE;
	//rasterizerDescription.DepthBias = 0;
	//rasterizerDescription.SlopeScaledDepthBias = 0.0f;
	//rasterizerDescription.DepthBiasClamp = 0.0f;
	//rasterizerDescription.DepthClipEnable = TRUE;
	//rasterizerDescription.ScissorEnable = FALSE;
	//rasterizerDescription.MultisampleEnable = FALSE;
	//rasterizerDescription.AntialiasedLineEnable = FALSE;

	//// create a new rs with the changed desrc
	//ID3D11RasterizerState *rasterizerState;
	//this->device->CreateRasterizerState(&rasterizerDescription, &rasterizerState);
	//this->deviceContext->RSSetState(rasterizerState);

	//rs->Release();






	//D3D11_DEPTH_STENCIL_DESC dsDesc;
	//// Depth test parameters
	//dsDesc.DepthEnable = true;
	//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//// Stencil test parameters
	//dsDesc.StencilEnable = true;
	//dsDesc.StencilReadMask = 0xFF;
	//dsDesc.StencilWriteMask = 0xFF;
	//// Stencil operations if pixel is front-facing
	//dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	//dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//// Stencil operations if pixel is back-facing
	//dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	//dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//// Create depth stencil state
	//ID3D11DepthStencilState * pDSState;
	//this->device->CreateDepthStencilState(&dsDesc, &pDSState);

	//// Bind depth stencil state
	//this->deviceContext->OMSetDepthStencilState(pDSState, 1);



	if (this->defaultTexture != 0)
		delete this->defaultTexture;

	unsigned int color = 0xffffffff;
	this->defaultTexture = this->CreateTexture();
	this->defaultTexture->Update(&color, 1, 1);

	return true;
}

bool MwDirect3D11GraphicsDevice::SetRenderTargetTexture(MwDeviceTexture2D *texture)
{

	MwDirect3D11Texture2D *d3dTexture = (MwDirect3D11Texture2D*)texture;

	if (d3dTexture->deviceTexture == NULL)
		return false;

	if (d3dTexture->deviceRenderTargetView == this->currentRenderTargetView)
		return true;

	if (!d3dTexture->isRenderTarget)
	{
		d3dTexture->Create(0, d3dTexture->width, d3dTexture->height, true);
	}

	this->currentRenderTargetView = d3dTexture->deviceRenderTargetView;
	this->currentRenderTargetDepthStencilView = d3dTexture->deviceRenderTargetDepthStencilView;
	this->deviceContext->OMSetRenderTargets(1, &this->currentRenderTargetView, this->currentRenderTargetDepthStencilView);
	this->SetViewport(0, 0, d3dTexture->width, d3dTexture->height);
	this->deviceContext->ClearDepthStencilView(this->currentRenderTargetDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return true;
}

MwPixelFormat MwDirect3D11GraphicsDevice::GetPixelFormat()
{
	return MwPixelFormat(4, 4, 8, 8, 8, 8, MwPixelFormat::ChannelIdRed, MwPixelFormat::ChannelIdGreen, MwPixelFormat::ChannelIdBlue, MwPixelFormat::ChannelIdAlpha);
}

void MwDirect3D11GraphicsDevice::Clear(MwVector4 &color)
{
	this->deviceContext->ClearRenderTargetView(this->currentRenderTargetView, (FLOAT*)&color);
	this->deviceContext->ClearDepthStencilView(this->currentRenderTargetDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void MwDirect3D11GraphicsDevice::BeginScene()
{
}

void MwDirect3D11GraphicsDevice::EndScene()
{
}

void MwDirect3D11GraphicsDevice::SetViewport(int x, int y, int width, int height)
{
	//DXGI_SWAP_CHAIN_DESC swapChainDescription;
	//if (FAILED(this->deviceSwapChain->GetDesc(&swapChainDescription)))
	//	return;

	//if (FAILED(this->deviceSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_D24_UNORM_S8_UINT, 0)))
	//	return;

	// Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = (FLOAT)x;
    vp.TopLeftY = (FLOAT)y;

	this->deviceContext->RSSetViewports(1, &vp);
}

void MwDirect3D11GraphicsDevice::SetMesh(MwDeviceMesh &mesh)
{
	this->currentMesh = (MwDirect3D11Mesh*)&mesh;	
    
	UINT stride = this->currentMesh->vertexSize;
    UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, &this->currentMesh->vertexBuffer, &stride, &offset);

	this->deviceContext->IASetIndexBuffer(this->currentMesh->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void MwDirect3D11GraphicsDevice::SetShader(MwDeviceShader &shader)
{
	this->currentShader = (MwDirect3D11Shader*)&shader;

	this->deviceContext->IASetInputLayout(this->currentShader->vertexLayout);

	this->deviceContext->VSSetShader(this->currentShader->vertexShader, NULL, 0);
	this->deviceContext->PSSetShader(this->currentShader->pixelShader, NULL, 0);

	MwMatrix::Multiply(this->viewProjection, this->currentShader->viewMatrix, this->currentShader->projectionMatrix);
	this->currentShader->SetParameter(this->currentShader->GetParameterAddress("viewProjectionMatrix"), 0, &this->viewProjection);

	for (int i = 0; i < this->currentShader->constantBuffers.count; i++)
	{
		MwDirect3D11ConstantBuffer *constantBuffer = &this->currentShader->constantBuffers[i];
		this->deviceContext->UpdateSubresource(constantBuffer->buffer, 0, NULL, constantBuffer->data, 0, 0);

		this->deviceContext->VSSetConstantBuffers(i, 1, &constantBuffer->buffer);
		this->deviceContext->PSSetConstantBuffers(i, 1, &constantBuffer->buffer);
	}
}

void MwDirect3D11GraphicsDevice::SetRenderState(MwRenderState renderState)
{
}

void MwDirect3D11GraphicsDevice::RenderMesh()
{
	this->deviceContext->DrawIndexed(this->currentMesh->indexCount, 0, 0);
}

bool MwDirect3D11GraphicsDevice::Present()
{
	this->deviceSwapChain->Present(0, 0);
	return true;
}
