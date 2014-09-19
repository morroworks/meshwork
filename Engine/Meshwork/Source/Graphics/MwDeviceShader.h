#pragma once

#include "..\MwGlobals.h"

#include "..\Tools\MwString.h"

#include "..\Engine\Primitive\MwShaderOperation.h"
#include "..\Engine\Primitive\MwColorOperation.h"

class MWDLLCLASS MwDeviceShader
{
public:
	MwDeviceShader(void);
	virtual ~MwDeviceShader(void);

	virtual int GetOperationCount() = 0;
	virtual void AddOperation(MwShaderOperation shaderOp, MwColorOperation colorOp) = 0;
	virtual void GetOperation(int index, MwShaderOperation &shaderOp, MwColorOperation &colorOp) = 0;
	virtual void SetOperation(int index, MwShaderOperation shaderOp, MwColorOperation colorOp) = 0;
	virtual void ClearOperations() = 0;

	virtual int GetParameterAddress(MwString parameterName) = 0;
	virtual void SetParameter(int address, int index, void *value) = 0;

	virtual bool Update(MwString &compilationMessage) = 0;
};

