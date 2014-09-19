#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\..\Tools\Streams\MwMemoryStream.h"

class Meshwork;

class MWDLLCLASS MwScript :
	public MwBaseResource
{
private:
	static const unsigned int SerializationId_SourceCode	= 0x2111100d;
	static const unsigned int SerializationId_CompiledCode	= 0x2111200d;

public:
	static const int classId = (MwResourceType_Script << 16) | 0;

	Meshwork *context;

	long long entryPoint;
	MwString errorCode;
	MwString sourceCode;
	MwMemoryStream compiledCode;

	bool successfullyCompiled;

	MwScript(Meshwork *context);
	~MwScript(void);

	bool CompileCode();
	bool RunCode();

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

