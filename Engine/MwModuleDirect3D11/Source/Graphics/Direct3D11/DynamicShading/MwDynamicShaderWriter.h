#pragma once

#include "..\..\..\MeshworkEngine.h"

#include "MwDynamicShaderBlockDefinitions.h"
#include "MwDynamicShaderConstantBufferInfo.h"

class MwDynamicShaderWriter
{
private:
	MwList<MwDynamicShaderConstantBufferInfo*> *constantBuffersInfo;
	MwStrings *textureBuffersInfo;

	MwDynamicShaderBlockDefinitions various, parameters, vsInputType, vsCode, sIOType, psCode, psOutputType;
    int textureSlots, texCoordSlots, numLights;

	MwString GetColorOperationCode(MwString destArg, MwString sourceArg, MwColorOperation colorOp);

	bool animated;

public:
	MwDynamicShaderWriter(bool animated, MwList<MwDynamicShaderConstantBufferInfo*> *constantBuffersInfo, MwStrings *textureBuffersInfo);
	~MwDynamicShaderWriter(void);
	
	void AddShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp);
	MwString GetSourceCode();
};

