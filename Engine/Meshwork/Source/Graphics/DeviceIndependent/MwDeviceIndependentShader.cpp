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

#include "MwDeviceIndependentShader.h"


MwDeviceIndependentShader::MwDeviceIndependentShader(void)
{
}


MwDeviceIndependentShader::~MwDeviceIndependentShader(void)
{
}

int MwDeviceIndependentShader::GetOperationCount()
{
	return this->shadingOps.count;
}

void MwDeviceIndependentShader::AddOperation(MwShaderOperation shaderOp, MwColorOperation colorOp)
{
	MwDeviceIndependentMaterialShadingOperation shadingOperation;
	shadingOperation.shaderOp = shaderOp;
	shadingOperation.colorOp = colorOp;

	this->shadingOps.Add(shadingOperation);
}

void MwDeviceIndependentShader::GetOperation(int index, MwShaderOperation &shaderOp, MwColorOperation &colorOp)
{
	shaderOp = this->shadingOps[index].shaderOp;
	colorOp = this->shadingOps[index].colorOp;
}

void MwDeviceIndependentShader::SetOperation(int index, MwShaderOperation shaderOp, MwColorOperation colorOp)
{
	this->shadingOps[index].shaderOp = shaderOp;
	this->shadingOps[index].colorOp = colorOp;
}

void MwDeviceIndependentShader::ClearOperations()
{
	this->shadingOps.Clear();
}

int MwDeviceIndependentShader::GetParameterAddress(MwString parameterName)
{
	return -1;
}

void MwDeviceIndependentShader::SetParameter(int address, void *value)
{
}

bool MwDeviceIndependentShader::Update()
{
	return true;
}

int MwDeviceIndependentShader::IndexOf(MwShaderOperation shaderOp)
{
	for (int i = 0; i < this->shadingOps.count; i++)
		if (this->shadingOps[i].shaderOp == shaderOp)
			return i;

	return -1;
}
