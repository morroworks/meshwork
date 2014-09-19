#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwDeviceShader.h"

#include "..\..\Tools\MwList.h"

struct MwDeviceIndependentMaterialShadingOperation
{
	MwShaderOperation shaderOp;
	MwColorOperation colorOp;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwDeviceIndependentMaterialShadingOperation>;

class MWDLLCLASS MwDeviceIndependentShader :
	public MwDeviceShader
{
public:
	MwList<MwDeviceIndependentMaterialShadingOperation> shadingOps;

	MwDeviceIndependentShader(void);
	virtual ~MwDeviceIndependentShader(void);

	virtual int GetOperationCount();
	virtual void AddOperation(MwShaderOperation shaderOp, MwColorOperation colorOp);
	virtual void GetOperation(int index, MwShaderOperation &shaderOp, MwColorOperation &colorOp);
	virtual void SetOperation(int index, MwShaderOperation shaderOp, MwColorOperation colorOp);
	virtual void ClearOperations();

	virtual int GetParameterAddress(MwString parameterName);
	virtual void SetParameter(int address, void *value);

	virtual bool Update();

	int IndexOf(MwShaderOperation shaderOp);
};

