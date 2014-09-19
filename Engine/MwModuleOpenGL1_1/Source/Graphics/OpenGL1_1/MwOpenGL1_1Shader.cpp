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

#include "MwOpenGL1_1Shader.h"

#include "MwOpenGL1_1GraphicsDevice.h"
#include "MwOpenGL1_1Texture2D.h"

#include <gl\GL.h>

MwOpenGL1_1Shader::MwOpenGL1_1Shader(void)
	: MwDeviceIndependentShader()
{
}


MwOpenGL1_1Shader::~MwOpenGL1_1Shader(void)
{
}

int MwOpenGL1_1Shader::GetParameterAddress(MwString parameterName)
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

void MwOpenGL1_1Shader::SetParameter(int address, int index, void *value)
{
	switch (address)
	{
		case 0:
		{
	    	glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat*)((MwVector4*)value));
	    	glColor4f(((float*)value)[0], ((float*)value)[1], ((float*)value)[2], ((float*)value)[3]);
			break;
		}
		case 1:
		{
			glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)((MwVector4*)value));
			break;
		}
		case 2:
		{
	    	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat*)((MwVector4*)value));
			break;
		}
		case 3:
		{
			glMaterialfv(GL_FRONT, GL_SHININESS, (GLfloat*)((MwVector4*)value));
			break;
		}
		case 4:
		{
			if (value != 0)
			{
				MwOpenGL1_1Texture2D *colorMap = (MwOpenGL1_1Texture2D*)value;
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, colorMap->textureId);
				glEnable(GL_TEXTURE_2D);
			}
			break;
		}
		case 5:
		{
			if (value != 0)
			{
				MwOpenGL1_1Texture2D *envMap = (MwOpenGL1_1Texture2D*)value;

				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, envMap->textureId);
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
			}
			break;
		}
		case 6:
		{
			break;
		}
		case 7:
		{
			break;
		}
		case 8:
		{
			if (value != 0)
			{
				int numLights = *(int*)value;
				for (int i = 0; i < 8; i++)
					if (i < numLights)
						glEnable(GL_LIGHT0 + i);
					else
						glDisable(GL_LIGHT0 + i);
			}
			break;
		}
		case 9:
		{
			if (value != 0)
			{
				MwMatrix::Copy(this->viewTransform, *(MwMatrix*)value);
				MwMatrix::Multiply(this->modelViewTransform, this->modelTransform, this->viewTransform);

				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf((GLfloat*)&this->modelViewTransform);
			}
			break;
		}
		case 10:
		{
			if (value != 0)
			{
				MwMatrix::Copy(this->projectionTransform, *(MwMatrix*)value);

				glMatrixMode(GL_PROJECTION);
				glLoadMatrixf((GLfloat*)&this->projectionTransform);
			}
			break;
		}

		case 11:
		{
			if (value != 0)
			{
				if (index < this->context->maxBones)
				{
					this->isAnimated |= index > 0;
					this->context->bones[index] = *(MwMatrix*)value;

					if (!this->isAnimated)
					{
						MwMatrix::Copy(this->modelTransform, *(MwMatrix*)value);
						MwMatrix::Multiply(this->modelViewTransform, this->modelTransform, this->viewTransform);
			
						glMatrixMode(GL_MODELVIEW);
						glLoadMatrixf((GLfloat*)&this->modelViewTransform);
					}
				}
			}
			break;
		}
		case 12:
		{
			if (value != 0)
			{
				if (index < 8)
				{
					glLightfv(GL_LIGHT0 + index, GL_POSITION, (GLfloat*)&MwVector4(*(MwVector3*)value, 1.0f));
				}
			}
			break;
		}
		case 13:
		{
			if (value != 0)
			{
				if (index < 8)
				{
					glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, (GLfloat*)((MwVector4*)value));
					glLightfv(GL_LIGHT0 + index, GL_SPECULAR, (GLfloat*)((MwVector4*)value));
				}
			}
			break;
		}
		case 14:
		{
			// No intensity setting
			break;
		}
		// Global ambient light
		case 15:
		{
			glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat*)((MwVector4*)value));
			break;
		}
	}
}

bool MwOpenGL1_1Shader::Update(MwString &compilationMessage)
{
	this->isAnimated = false;
	for (int i = 0; i < this->shadingOps.count; i++)
	{
		if (this->shadingOps[i].shaderOp == MwShaderOperation_Skinning)
		{
			this->isAnimated = true;
			break;
		}
	}

	return true;
}