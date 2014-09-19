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

#include "MwDirect3D11Shader.h"

#include <Direct3D11\D3Dcompiler.h>

#include "DynamicShading\MwDynamicShaderWriter.h"

#include "MwDirect3D11Texture2D.h"

MwDirect3D11Shader::MwDirect3D11Shader(void)
{
	this->vertexShader = 0;
	this->pixelShader = 0;

	this->vertexLayout = 0;
}


MwDirect3D11Shader::~MwDirect3D11Shader(void)
{
	this->Release();
}

int MwDirect3D11Shader::GetParameterAddress(MwString parameterName)
{
	
	if (parameterName.Equals("viewMatrix"))
		return -2;
	if (parameterName.Equals("projectionMatrix"))
		return -3;

	for (int cBufferIndex = 0; cBufferIndex < this->constantBuffersInfo.count; cBufferIndex++)
	{
		MwList<MwDynamicShaderConstantInfo> *cbufferInfo = this->constantBuffersInfo[cBufferIndex];
		for (int cIndex = 0; cIndex < cbufferInfo->count; cIndex++)
			if (cbufferInfo->Get(cIndex).name.Equals(parameterName))
				return (cBufferIndex << 16) | cIndex;
	}

	for (int tBufferIndex = 0; tBufferIndex < this->textureBuffersInfo.count; tBufferIndex++)
		if (this->textureBuffersInfo[tBufferIndex].Equals(parameterName))
			return (this->constantBuffersInfo.count + tBufferIndex) << 16;

	return -1;
}

void MwDirect3D11Shader::SetParameter(int address, int index, void *value)
{
	if (value == 0)
		return;

	if (address == -2)
		this->viewMatrix = *(MwMatrix*)(value);
	if (address == -3)
		this->projectionMatrix = *(MwMatrix*)(value);

	if (address < 0)
		return;

	int bufferIndex = address >> 16;
	int parameterIndex = address & 0xffff;

	if (bufferIndex < this->constantBuffersInfo.count)
	{
		int paramAddress = this->constantBuffersInfo[bufferIndex]->Get(parameterIndex).offset;
		int paramSize = this->constantBuffersInfo[bufferIndex]->Get(parameterIndex).elementSize;
		int paramPitch = this->constantBuffersInfo[bufferIndex]->Get(parameterIndex).elementPitch;

		MwMem::Copy((char*)this->constantBuffers[bufferIndex].data + paramAddress + index * paramPitch, value, paramSize);
	}
	else
	{
		bufferIndex -= this->constantBuffersInfo.count;
		if (bufferIndex < this->textureBuffersInfo.count)
		{
			MwDirect3D11Texture2D *texture = (value != 0) ? (MwDirect3D11Texture2D*)value : (MwDirect3D11Texture2D*)this->context->defaultTexture;
			this->context->deviceContext->PSSetShaderResources(bufferIndex, 1, &texture->deviceShaderResourceView);
			this->context->deviceContext->PSSetSamplers(bufferIndex, 1, &texture->deviceSampler);
		}
	}
}

bool MwDirect3D11Shader::Update(MwString &compilationMessage)
{
	this->Release();

	MwDynamicShaderWriter shaderWriter(this->IndexOf(MwShaderOperation_Skinning) != -1, &this->constantBuffersInfo, &this->textureBuffersInfo);

	for (int i = 0; i < this->shadingOps.count; i++)
		shaderWriter.AddShaderSlot(this->shadingOps[i].shaderOp, this->shadingOps[i].colorOp);

	MwString shaderCode = shaderWriter.GetSourceCode();
	//MwFileStream(L"LastShader.fx", FileStreamAccessMode_Write).WriteText(shaderCode);

	if (!this->CompileShader(shaderCode))
	{
		compilationMessage = this->compilationErrorMessage;
		return false;
	}

	this->constantBuffers.SetSize(this->constantBuffersInfo.count);
	for (int constantBufferIndex = 0; constantBufferIndex < this->constantBuffersInfo.count; constantBufferIndex++)
	{
		MwDirect3D11ConstantBuffer *constantBuffer = &this->constantBuffers[constantBufferIndex];
		
		// Create a data buffer, which will be used to store constants into, and have its whole contents instantly to the constant buffer of the device, when rendering with the shader
		// Constant buffer size must be a multiple of MwDynamicShaderConstantBufferInfo::SizeMultiplicity (the size of a float4 = 16)
		constantBuffer->SetDataSize(MwMaths::GetBoundary(this->constantBuffersInfo[constantBufferIndex]->totalSize,MwDynamicShaderConstantBufferInfo::SizeMultiplicity));

		// Create the constant buffer
		D3D11_BUFFER_DESC bufferDescription;
		MwMem::Zero(&bufferDescription, sizeof(bufferDescription));
		bufferDescription.Usage = D3D11_USAGE_DEFAULT;
		bufferDescription.ByteWidth = constantBuffer->dataSize;
		bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDescription.CPUAccessFlags = 0;
		if (FAILED(this->context->device->CreateBuffer(&bufferDescription, NULL, &constantBuffer->buffer)))
			return false;
	}

	return true;
}

bool MwDirect3D11Shader::CompileShader(MwString &shaderCode)
{
	// Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;
	if (!this->CompileShaderFunction(shaderCode, "VSMain", "vs_4_0", &pVSBlob))
        return false;

	HRESULT hr;
	hr = this->context->device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &this->vertexShader);
	// Create the vertex shader
	if (FAILED(hr))
	{	
		pVSBlob->Release();
        return false;
	}

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 3 * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, (3 + 3) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, (3 + 3 + 2) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, (3 + 3 + 2 + 4) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
	hr = this->context->device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &this->vertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
        return false;

	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	if (!this->CompileShaderFunction(shaderCode, "PSMain", "ps_4_0", &pPSBlob))
        return false;

	// Create the pixel shader
	hr = this->context->device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &this->pixelShader);
	pPSBlob->Release();
    if (FAILED(hr))
        return false;

	return true;
}

bool MwDirect3D11Shader::CompileShaderFunction(MwString &shaderCode, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	const char *c = shaderCode.GetCharContents();
	int cl = shaderCode.GetLength();

	ID3DBlob* pErrorBlob;
	if (FAILED(D3DCompile(
		shaderCode.GetCharContents(),		// HLSL code of the shader
		shaderCode.GetLength(), 			// Size of the HLSL code in bytes
		NULL,								// File name
		NULL,								// Macro definitions
		NULL,								// Pointer to the shader's include files. Should be non-NULL, if the shader contains #include
		szEntryPoint,						// Entry point function name. The shader function which is to be compiled
		szShaderModel,						// Shader model compiling profile string. Valid values are "vs_4_0", "ps_4_0" and so on.
		dwShaderFlags,						// Shader compile flags
		0,									// Effect compile flags. Should be 0 when compiling a shader and not an effect
		ppBlobOut,							// The compiled shader code
		&pErrorBlob)))						// Error msg if compilation went wrong
	{
        if (pErrorBlob != NULL)
		{
            this->compilationErrorMessage = (char*)pErrorBlob->GetBufferPointer();
			pErrorBlob->Release();
		}


		return false;
	}

    if (pErrorBlob)
		pErrorBlob->Release();

    return true;
}

void MwDirect3D11Shader::Release()
{
	for (int i = 0; i < this->constantBuffers.count; i++)
	{
		if (this->constantBuffers[i].data != 0)
		{
			delete[] this->constantBuffers[i].data;
			this->constantBuffers[i].data = 0;
		}

		if (this->constantBuffers[i].buffer != 0)
		{
			this->constantBuffers[i].buffer->Release();
			this->constantBuffers[i].buffer = 0;
		}
	}
	this->constantBuffers.Clear();

	for (int i = 0; i < this->constantBuffersInfo.count; i++)
		delete this->constantBuffersInfo[i];
	this->constantBuffersInfo.Clear();

	this->textureBuffersInfo.Clear();


	if (this->vertexShader != 0)
	{
		this->vertexShader->Release();
		this->vertexShader = 0;
	}

	if (this->pixelShader != 0)
	{
		this->pixelShader->Release();
		this->pixelShader = 0;
	}


	if (this->vertexLayout != 0)
	{
		this->vertexLayout->Release();
		this->vertexLayout = 0;
	}
}