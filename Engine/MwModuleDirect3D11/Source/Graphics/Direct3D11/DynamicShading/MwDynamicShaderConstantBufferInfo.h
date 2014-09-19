#pragma once

#include "..\..\..\MeshworkEngine.h"

struct MwDynamicShaderConstantInfo
{
	MwString name;
	int offset, elementSize, elementCount, elementPitch;
};

class MwDynamicShaderConstantBufferInfo : 
	public MwList<MwDynamicShaderConstantInfo>
{
public:
	// Feature level 10 an higher can create buffers of sizes less or equal to D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT (currently, 4096)
	static const int MaxSize = 4096;
	// Buffer size must be a multiple of 16
	static const int SizeMultiplicity = 16;

	int totalSize;

	MwDynamicShaderConstantBufferInfo(void);
	~MwDynamicShaderConstantBufferInfo(void);

	// Adds info for a constant or an array of constants. Can be used to create info on constants, which share the same vector in the GPU shader. For example, a float4 can hold up to 4 semantically different constants. In such a case, the first 3 should be created with a respective non-zero offset - 4, 8 or 12, and the last one with offset 0, which will also add to the total buffer size
	bool Add(MwString name, int elementSize, int elementCount = 1, int offset = 0);
	// Clears the info added so far.
	void Clear();
};

