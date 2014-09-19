#pragma once

#include "..\..\MeshworkEngine.h"

#include "MwDirect3D11GraphicsDevice.h"

class MwDirect3D11ConstantBuffer
{
public:
	ID3D11Buffer *buffer;

	void *data;
	int dataSize;

	MwDirect3D11ConstantBuffer(void);
	~MwDirect3D11ConstantBuffer(void);

	void SetDataSize(int dataSizeInBytes);
};

