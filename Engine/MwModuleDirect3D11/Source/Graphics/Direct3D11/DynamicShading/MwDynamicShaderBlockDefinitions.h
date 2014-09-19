#pragma once

#include "..\..\..\MeshworkEngine.h"

struct MwDynamicShaderDefinition
{
	MwString name, code;
};

class MwDynamicShaderBlockDefinitions
{
private:
	MwList<MwDynamicShaderDefinition*> definitions;

public:
	MwDynamicShaderBlockDefinitions(void);
	~MwDynamicShaderBlockDefinitions(void);

	bool ProvideDefinition(MwString name, MwString code);
	MwString GetCode();
};

