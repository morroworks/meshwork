#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwDirect3D11GraphicsDevice.h"
#include "DynamicShading\MwDynamicShaderConstantBufferInfo.h"

#include "MwDirect3D11ConstantBuffer.h"

class MwDirect3D11Shader :
	public MwDeviceIndependentShader
{
private:
	MwList<MwDynamicShaderConstantBufferInfo*> constantBuffersInfo;
	MwStrings textureBuffersInfo;

	MwString compilationErrorMessage;


	bool CompileShader(MwString &shaderCode);
	bool CompileShaderFunction(MwString &shaderCode, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	void Release();

public:
	MwMatrix viewMatrix, projectionMatrix;

	MwDirect3D11GraphicsDevice *context;

	ID3D11VertexShader*     vertexShader;
	ID3D11PixelShader*      pixelShader;
	
	ID3D11InputLayout*      vertexLayout;

	MwList<MwDirect3D11ConstantBuffer> constantBuffers;

	MwDirect3D11Shader(void);
	~MwDirect3D11Shader(void);

	int GetParameterAddress(MwString parameterName);
	void SetParameter(int address, int index, void *value);

	bool Update(MwString &compilationMessage);
};

