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

#include "MwSorasGraphicsDevice.h"

#include <windows.h>

#include "MwSorasMesh.h"
#include "MwSorasTexture2D.h"
#include "MwSorasShader.h"

#include "..\..\Engine\Entities\Textures\MwTexture2D.h"

#include "..\..\Tools\OS\MwOSUtils.h"

MwSorasGraphicsDevice::MwSorasGraphicsDevice()
{
	this->windowHandle_HWND = new HWND();
	this->deviceContext_HDC = new HDC();

	this->drawSurface = new MwDrawSurface();
	this->soras = new Soras();
	this->soras->SetRenderSurface(new SrTexture());

	this->pixelFormat = MwPixelFormat(4, 4, 8, 8, 8, 8, MwPixelFormat::ChannelIdBlue, MwPixelFormat::ChannelIdGreen, MwPixelFormat::ChannelIdRed, MwPixelFormat::ChannelIdAlpha);
}


MwSorasGraphicsDevice::~MwSorasGraphicsDevice(void)
{
	delete this->soras->renderSurface;
	delete this->soras;
	delete this->drawSurface;

	delete this->windowHandle_HWND;
	delete this->deviceContext_HDC;
}

MwDeviceMesh *MwSorasGraphicsDevice::CreateMesh()
{
	return new MwSorasMesh();
}

MwDeviceTexture2D *MwSorasGraphicsDevice::CreateTexture()
{
	return new MwSorasTexture2D();
}

MwDeviceShader *MwSorasGraphicsDevice::CreateShader()
{
	MwSorasShader *shader = new MwSorasShader();
	shader->context = this;
	return shader;
}

bool MwSorasGraphicsDevice::SetRenderTargetWindow(void *windowHandle)
{
	if (*(HWND*)this->windowHandle_HWND == *(HWND*)windowHandle)
		return true;
	
	*(HWND*)this->windowHandle_HWND = *(HWND*)windowHandle;
	*(HDC*)this->deviceContext_HDC = GetDC(*(HWND*)this->windowHandle_HWND);

	int width, height;
	MwOSUtils::GetWindowClientSize(windowHandle, width, height);

	this->SetViewport(0, 0, width, height);

	return true;
}

bool MwSorasGraphicsDevice::SetRenderTargetTexture(MwDeviceTexture2D *texture)
{
	return false;
}

MwPixelFormat MwSorasGraphicsDevice::GetPixelFormat()
{
	return this->pixelFormat;
}

void MwSorasGraphicsDevice::Clear(MwVector4 &color)
{
	this->soras->Clear(SrARGB((unsigned char)(color.w * 0xff), (unsigned char)(color.x * 0xff), (unsigned char)(color.y * 0xff), (unsigned char)(color.z * 0xff)));
	this->soras->ClearZ();
}

void MwSorasGraphicsDevice::BeginScene()
{
}

void MwSorasGraphicsDevice::EndScene()
{
}

void MwSorasGraphicsDevice::SetViewport(int x, int y, int width, int height)
{
	this->soras->renderSurface->SetSize(width, height);
	this->soras->SetRenderSurface(this->soras->renderSurface);
	this->drawSurface->SetSize(width, height);
}

void MwSorasGraphicsDevice::SetMesh(MwDeviceMesh &mesh)
{
	this->soras->SetMesh(((MwSorasMesh*)(&mesh))->sorasMesh);
}

void MwSorasGraphicsDevice::SetShader(MwDeviceShader &shader)
{
	MwSorasShader *srShader = (MwSorasShader*)&shader;

	this->soras->ClearShaderOperations();
	
	for (int i = 0; i < srShader->vertexShaderOps.count; i++)
	{
		this->soras->AddVertexShader(srShader->vertexShaderOps[i], srShader->vertexColorOps[i]);
	}

	for (int i = 0; i < srShader->pixelShaderOps.count; i++)
	{
		this->soras->AddPixelShader(srShader->pixelShaderOps[i], srShader->pixelColorOps[i], srShader->pixelOpsTextures[i]);
	}

	MwMatrix::Multiply(this->viewProjection, srShader->viewMatrix, srShader->projectionMatrix);
	this->soras->viewProjectionMatrix = *(SrMatrix*)&this->viewProjection;

	this->soras->skeletalAnimationOn = srShader->isAnimated;
}

void MwSorasGraphicsDevice::SetRenderState(MwRenderState renderState)
{
}

void MwSorasGraphicsDevice::RenderMesh()
{
	this->soras->RenderMesh();
}

bool MwSorasGraphicsDevice::Present()
{
	this->drawSurface->Copy(this->soras->renderSurface->data);
	this->drawSurface->Present(0, 0, *(HDC*)this->deviceContext_HDC);

	return true;
}
