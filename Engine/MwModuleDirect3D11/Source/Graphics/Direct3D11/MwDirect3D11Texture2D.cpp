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

#include "MwDirect3D11Texture2D.h"


MwDirect3D11Texture2D::MwDirect3D11Texture2D(void)
{
	this->deviceTexture = NULL;
	this->deviceShaderResourceView = NULL;
	this->deviceRenderTargetView = NULL;
	this->deviceRenderTargetDepthStencil = NULL;
	this->deviceRenderTargetDepthStencilView = NULL;
	this->deviceSampler = NULL;
}


MwDirect3D11Texture2D::~MwDirect3D11Texture2D(void)
{
	this->Release();
}

void MwDirect3D11Texture2D::Update(void *data, int width, int height)
{
	if ((width != this->width) || (height != this->height) || (this->deviceTexture == NULL))
	{
		this->Release();
		this->Create(data, width, height, false);
	}
	else
		this->Fill(data);
}

void MwDirect3D11Texture2D::GetData(void *data)
{
	// Create the device texture object
	D3D11_TEXTURE2D_DESC stagingTextureDescription;
	MwMem::Zero(&stagingTextureDescription, sizeof(stagingTextureDescription));
	stagingTextureDescription.Width = width;
	stagingTextureDescription.Height = height;
	stagingTextureDescription.ArraySize = 1;
	stagingTextureDescription.MipLevels = 1;
	stagingTextureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	stagingTextureDescription.SampleDesc.Count = 1;
	stagingTextureDescription.SampleDesc.Quality = 0;
	stagingTextureDescription.Usage = D3D11_USAGE_DEFAULT;
	stagingTextureDescription.BindFlags = D3D11_USAGE_STAGING;
	stagingTextureDescription.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	stagingTextureDescription.MiscFlags = 0;

	ID3D11Texture2D *stagingTexture = NULL;
	if (FAILED(this->context->device->CreateTexture2D(&stagingTextureDescription, NULL, &stagingTexture)))
	{
		if (stagingTexture != NULL)
			stagingTexture->Release();
		return;
	}

	this->context->deviceContext->CopyResource(stagingTexture, this->deviceTexture);
	
	D3D11_MAPPED_SUBRESOURCE mappedData;
	this->context->deviceContext->Map(stagingTexture, 0, D3D11_MAP_READ, 0, &mappedData);
	MwMem::Copy(data, mappedData.pData, this->width * this->height * 4);
	this->context->deviceContext->Unmap(stagingTexture, 0);

	stagingTexture->Release();
}

void MwDirect3D11Texture2D::Create(void *data, int width, int height, bool isRenderTarget)
{
	if ((width <= 0) || (height <= 0))
		return;

	this->width = width;
	this->height = height;
	this->isRenderTarget = isRenderTarget;

	// Create the device texture object
	D3D11_TEXTURE2D_DESC textureDescription;
	MwMem::Zero(&textureDescription, sizeof(textureDescription));
	textureDescription.Width = width;
	textureDescription.Height = height;
	textureDescription.ArraySize = 1;
	textureDescription.MipLevels = 1;
	textureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDescription.SampleDesc.Count = 1;
	textureDescription.SampleDesc.Quality = 0;
	textureDescription.Usage = D3D11_USAGE_DEFAULT;
	textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	if (isRenderTarget)
		textureDescription.BindFlags |= D3D11_BIND_RENDER_TARGET;
	textureDescription.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE;
	textureDescription.MiscFlags = 0;

	if (data != 0)
	{
		D3D11_SUBRESOURCE_DATA textureData;
		textureData.pSysMem = data;
		textureData.SysMemPitch = width * 4;
		textureData.SysMemSlicePitch = width * height * 4;

		if (FAILED(this->context->device->CreateTexture2D(&textureDescription, &textureData, &this->deviceTexture)))
		{
			this->Release();
			return;
		}
	}
	else
	{
		if (FAILED(this->context->device->CreateTexture2D(&textureDescription, NULL, &this->deviceTexture)))
		{
			this->Release();
			return;
		}
	}


	// Create the device shader resource view object, which is the one to be set to a shader when using the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC deviceShaderResourceViewDescription;
	MwMem::Zero(&deviceShaderResourceViewDescription, sizeof(deviceShaderResourceViewDescription));
	deviceShaderResourceViewDescription.Format = textureDescription.Format;
	deviceShaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	deviceShaderResourceViewDescription.Texture2D.MipLevels = textureDescription.MipLevels;

	if (FAILED(this->context->device->CreateShaderResourceView(this->deviceTexture, &deviceShaderResourceViewDescription, &this->deviceShaderResourceView)))
	{
		this->Release();
		return;
	}

	if (isRenderTarget)
	{
		// Create the render target object, which is to be set as a render target to the device when setting the texture to render onto
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDescription;
		renderTargetViewDescription.Format = textureDescription.Format;
		renderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDescription.Texture2D.MipSlice = 0;

		if (FAILED(this->context->device->CreateRenderTargetView(this->deviceTexture, &renderTargetViewDescription, &this->deviceRenderTargetView)))
		{
			this->Release();
			return;
		}

		// Create the render target's depth stencil texture
		D3D11_TEXTURE2D_DESC renderTargetDepthStencilDescription;
		MwMem::Zero(&renderTargetDepthStencilDescription, sizeof(renderTargetDepthStencilDescription));
		renderTargetDepthStencilDescription.Width = width;
		renderTargetDepthStencilDescription.Height = height;
		renderTargetDepthStencilDescription.MipLevels = 1;
		renderTargetDepthStencilDescription.ArraySize = 1;
		renderTargetDepthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;//DXGI_FORMAT_R32_TYPELESS;
		renderTargetDepthStencilDescription.SampleDesc.Count = 1;
		renderTargetDepthStencilDescription.SampleDesc.Quality = 0;
		renderTargetDepthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
		renderTargetDepthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;//D3D10_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
		renderTargetDepthStencilDescription.CPUAccessFlags = 0;
		renderTargetDepthStencilDescription.MiscFlags = 0;

		if (FAILED(this->context->device->CreateTexture2D(&renderTargetDepthStencilDescription, NULL, &this->deviceRenderTargetDepthStencil)))
			return;

		// Create the render target's depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC renderTargetDepthStencilViewDescription;
		MwMem::Zero(&renderTargetDepthStencilViewDescription, sizeof(renderTargetDepthStencilViewDescription));
		renderTargetDepthStencilViewDescription.Format = renderTargetDepthStencilDescription.Format;//DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		renderTargetDepthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		renderTargetDepthStencilViewDescription.Texture2D.MipSlice = 0;
		if (FAILED(this->context->device->CreateDepthStencilView(this->deviceRenderTargetDepthStencil, &renderTargetDepthStencilViewDescription, &this->deviceRenderTargetDepthStencilView)))
			return;
	}


	// TODO: device samplers should be in graphics device
	// Create a device sampler object
	D3D11_SAMPLER_DESC sampDescription;
	MwMem::Zero(&sampDescription, sizeof(sampDescription));
	sampDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDescription.MinLOD = 0;
	sampDescription.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(this->context->device->CreateSamplerState(&sampDescription, &this->deviceSampler)))
	{
		this->Release();
		return;
	}
}

void MwDirect3D11Texture2D::Fill(void *data)
{
	D3D11_BOX destinationRegion;
	destinationRegion.left = 0;
	destinationRegion.right = this->width;
	destinationRegion.top = 0;
	destinationRegion.bottom = this->height;
	destinationRegion.front = 0;
	destinationRegion.back = 1;

	this->context->deviceContext->UpdateSubresource(this->deviceTexture, 0, &destinationRegion, data, this->width * 4, this->width * this->height * 4);
}

void MwDirect3D11Texture2D::Release()
{
	if (this->deviceTexture != NULL)
	{
		this->deviceTexture->Release();
		this->deviceTexture = NULL;
	}

	if (this->deviceShaderResourceView != NULL)
	{
		this->deviceShaderResourceView->Release();
		this->deviceShaderResourceView = NULL;
	}

	if (this->deviceRenderTargetView != NULL)
	{
		this->deviceRenderTargetView->Release();
		this->deviceRenderTargetView = NULL;
	}

	if (this->deviceRenderTargetDepthStencil != NULL)
	{
		this->deviceRenderTargetDepthStencil->Release();
		this->deviceRenderTargetDepthStencil = NULL;
	}

	if (this->deviceRenderTargetDepthStencilView != NULL)
	{
		this->deviceRenderTargetDepthStencilView->Release();
		this->deviceRenderTargetDepthStencilView = NULL;
	}

	if (this->deviceSampler != NULL)
	{
		this->deviceSampler->Release();
		this->deviceSampler = NULL;
	}
}