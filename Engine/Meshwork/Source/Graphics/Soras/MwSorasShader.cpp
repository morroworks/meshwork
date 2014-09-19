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

#include "MwSorasShader.h"

#include "MwSorasGraphicsDevice.h"
#include "MwSorasTexture2D.h"

MwSorasShader::MwSorasShader(void)
	: MwDeviceIndependentShader()
{
}


MwSorasShader::~MwSorasShader(void)
{
}

void MwSorasShader::MwToSrARGBInt(SrARGBInt &result, MwVector4 &source)
{
	result.r = (int)(source.x * 255.0f);
	result.g = (int)(source.y * 255.0f);
	result.b = (int)(source.z * 255.0f);
	result.a = (int)(source.w * 255.0f);
}

int MwSorasShader::GetParameterAddress(MwString parameterName)
{
	if (parameterName.Equals("materialAmbient"))
		return 0;
	else if (parameterName.Equals("materialDiffuse"))
		return 1;
	else if (parameterName.Equals("materialSpecular"))
		return 2;
	else if (parameterName.Equals("materialGloss"))
		return 3;
	else if (parameterName.Equals("colorMap"))
		return 4;
	else if (parameterName.Equals("envMap"))
		return 5;
	else if (parameterName.Equals("normalMap"))
		return 6;
	else if (parameterName.Equals("refractionMap"))
		return 7;
	else if (parameterName.Equals("activeLightsCount"))
		return 8;
	else if (parameterName.Equals("viewMatrix"))
		return 9;
	else if (parameterName.Equals("projectionMatrix"))
		return 10;
	
	else if (parameterName.Equals("worldMatrix"))
		return 11;
	else if (parameterName.Equals("lightsPos"))
		return 12;
	else if (parameterName.Equals("lightsColor"))
		return 13;
	else if (parameterName.Equals("lightsIntensity"))
		return 14;
	else if (parameterName.Equals("ambientLight"))
		return 15;

	return -1;
}

void MwSorasShader::SetParameter(int address, int index, void *value)
{
	switch (address)
	{
		case 0:
		{
			this->MwToSrARGBInt(this->context->soras->material.ambient, *(MwVector4*)value);
			break;
		}
		case 1:
		{
			this->MwToSrARGBInt(this->context->soras->material.diffuse, *(MwVector4*)value);
			break;
		}
		case 2:
		{
			this->MwToSrARGBInt(this->context->soras->material.specular, *(MwVector4*)value);
			break;
		}
		case 3:
		{
			this->context->soras->material.gloss = *(float*)value;
			break;
		}
		case 4:
		{
			if (this->colorMapIndex != -1)
				if (value != 0)
					this->pixelOpsTextures[this->colorMapIndex] = ((MwSorasTexture2D*)value)->sorasTexture;
			break;
		}
		case 5:
		{
			if (this->envMapIndex != -1)
				if (value != 0)
					this->pixelOpsTextures[this->envMapIndex] = ((MwSorasTexture2D*)value)->sorasTexture;
			break;
		}
		case 6:
		{
			if (this->normalMapIndex != -1)
				if (value != 0)
					this->pixelOpsTextures[this->normalMapIndex] = ((MwSorasTexture2D*)value)->sorasTexture;
			break;
		}
		case 7:
		{
			if (this->refractionMapIndex != -1)
				if (value != 0)
					this->pixelOpsTextures[this->refractionMapIndex] = ((MwSorasTexture2D*)value)->sorasTexture;
			break;
		}
		case 8:
		{
			if (value != 0)
				this->context->soras->SetLighsCount(*(int*)value);
			break;
		}
		case 9:
		{
			if (value != 0)
				this->viewMatrix = *(MwMatrix*)value;
			break;
		}
		case 10:
		{
			if (value != 0)
				this->projectionMatrix = *(MwMatrix*)value;
			break;
		}

		case 11:
		{
			if (value != 0)
			{
				if (index < this->context->soras->maxBones)
				{
					this->isAnimated |= index > 0;
					this->context->soras->bones[index] = *(SrMatrix*)((MwMatrix*)value);
					if (!this->isAnimated)
						this->context->soras->worldMatrix = *(SrMatrix*)((MwMatrix*)value);
				}
			}

			break;
		}

		// Lights position
		case 12:
		{
			if (value != 0)
			{
				if (index < this->context->soras->numLights)
				{
					this->context->soras->lights[index].position = *(SrVector3*)((MwVector3*)value);
				}
			}

			break;
		}

		// Lights color
		case 13:
		{
			if (value != 0)
			{
				if (index < this->context->soras->numLights)
				{
					this->MwToSrARGBInt(this->context->soras->lights[index].color, *(MwVector4*)value);
				}
			}

			break;
		}
		
		// Lights intensity
		case 14:
		{
			if (value != 0)
			{
				if (index < this->context->soras->numLights)
				{
					this->context->soras->lights[index].range = *(float*)value;
				}
			}

			break;
		}

		// Global ambient lighting
		case 15:
		{
			if (value != 0)
			{
				this->MwToSrARGBInt(this->context->soras->shadingParameters.globalAmbient, *(MwVector4*)value);
			}

			break;
		}

	}
}

bool MwSorasShader::Update(MwString &compilationMessage)
{
	this->isAnimated = false;

	this->vertexShaderOps.Clear();
	this->vertexColorOps.Clear();
	this->pixelShaderOps.Clear();
	this->pixelColorOps.Clear();
	this->pixelOpsTextures.Clear();

	this->colorMapIndex = -1;
	this->envMapIndex = -1;
	this->normalMapIndex = -1;
	this->refractionMapIndex = -1;

	for (int i = 0; i < this->shadingOps.count; i++)
	{
		MwColorOperation colorOp = this->shadingOps[i].colorOp;

		SrShaderOperation srColorOp = 0;
		switch (colorOp)
		{
			case MwColorOperation_None:
			{
				srColorOp = 0;
				break;
			}

			case MwColorOperation_Set:
			{
				srColorOp = SrShaderOperations::Color_Set;
				break;
			}

			case MwColorOperation_Add:
			{
				srColorOp = SrShaderOperations::Color_Add;
				break;
			}

			case MwColorOperation_Subtract:
			{
				srColorOp = SrShaderOperations::Color_Subtract;
				break;
			}

			case MwColorOperation_Modulate:
			{
				srColorOp = SrShaderOperations::Color_Modulate;
				break;
			}
		}

		MwShaderOperation shaderOp = this->shadingOps[i].shaderOp;

		switch (shaderOp)
		{
			case MwShaderOperation_BasicShading:
			{
				this->vertexShaderOps.Add(SrShaderOperations::BasicLighting);
				this->vertexColorOps.Add(srColorOp);
				break;
			}

			case MwShaderOperation_LightSource:
			{
				break;
			}

			case MwShaderOperation_VertexLighting:
			{
				this->vertexShaderOps.Add(SrShaderOperations::Lighting);
				this->vertexColorOps.Add(srColorOp);
				break;
			}

			case MwShaderOperation_PixelLighting:
			{
				this->pixelShaderOps.Add(SrShaderOperations::Lighting);
				this->pixelColorOps.Add(srColorOp);
				break;
			}

			case MwShaderOperation_ColorMap:
			{
				this->colorMapIndex = this->pixelShaderOps.count;
				this->pixelShaderOps.Add(SrShaderOperations::ColorMap);
				this->pixelColorOps.Add(srColorOp);
				break;
			}

			case MwShaderOperation_EnvMap:
			{
				this->envMapIndex = this->pixelShaderOps.count;
				this->pixelShaderOps.Add(SrShaderOperations::EnvMap);
				this->pixelColorOps.Add(srColorOp);
				break;
			}

			case MwShaderOperation_NormalMap:
			{
				this->normalMapIndex = this->pixelShaderOps.count;
				this->pixelShaderOps.Add(SrShaderOperations::NormalMap);
				this->pixelColorOps.Add(srColorOp);
				break;
			}

			case MwShaderOperation_RefractionMap:
			{
				this->refractionMapIndex = this->pixelShaderOps.count;
				this->pixelShaderOps.Add(SrShaderOperations::RefractionMap);
				this->pixelColorOps.Add(srColorOp);
				break;
			}

		}
	}

	this->pixelOpsTextures.SetSize(this->pixelShaderOps.count);
	for (int i = 0; i < this->pixelOpsTextures.count; i++)
		this->pixelOpsTextures[i] = 0;

	return true;
}

