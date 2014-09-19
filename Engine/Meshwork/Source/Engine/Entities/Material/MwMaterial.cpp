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

#include "MwMaterial.h"

#include "..\..\..\Tools\MwMath.h"

#include "..\..\Meshwork.h"

MwMaterial::MwMaterial(Meshwork &context)
	: MwBaseResource()
{
	this->context = &context;

	this->typeId = MwMaterial::classId;
	this->resourceType = MwResourceType_Material;

	//this->properties.Add(new MwProperty(MwString("Override Materials"), false));
	this->properties.Add(new MwBoundProperty("", MwString("Override Materials"), false));

	this->deviceShader = this->context->graphicsDevice->CreateShader();

	this->paramAddressWorldMatrix = -1;
	this->paramAddressViewMatrix = -1;
	this->paramAddressProjectionMatrix = -1;
	this->paramAddressViewPosition = -1;
	this->paramAddressLightsPos = -1;
	this->paramAddressLightsColor = -1;
	this->paramAddressLightsIntensity = -1;
	this->paramAddressActiveLightsCount = -1;
	this->paramAddressAmbientLight = -1;

    this->CommitRenderStates();
}

MwMaterial::~MwMaterial(void)
{
	delete this->deviceShader;
}


void MwMaterial::CommitRenderStates()
{
	int numRenderStates = this->renderStates.count;
	for (int i = 0; i < numRenderStates; i++)
			this->context->graphicsDevice->SetRenderState(this->renderStates[i]);
}

void MwMaterial::InsertShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp, int index)
{
	int numProperties = properties.count;

	int propertyIndex = index < this->shaderSlots.count ? shaderSlots[index].propertyFirst : numProperties;
	int propertyFirst = propertyIndex;

	MwTexture2D *defaultTexture = 0;//this->context->defaultTexture;

	switch (shaderOp)
	{
		case MwShaderOperation_BasicShading:
			{
				break;
			}

		case MwShaderOperation_ColorMap:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("colorMap", "Color Map", MwParameterType_ReferenceTexture, defaultTexture));
				break;
			}

		case MwShaderOperation_EnvMap:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("envMap", "Reflection Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("envFactor", "Reflection Factor", 1.0f));
				break;
			}

		case MwShaderOperation_LightSource:
			{
				break;
			}

		case MwShaderOperation_Material:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("materialAmbient", "Ambient", MwVector4(0.5f, 0.5f, 0.5f, 1.0f)));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("materialDiffuse", "Diffuse", MwVector4(0.5f, 0.5f, 0.5f, 1.0f)));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("materialSpecular", "Specular", MwVector4(1.0f, 1.0f, 1.0f, 1.0f)));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("materialGloss", "Gloss", 10.0f));
				break;
			}

		case MwShaderOperation_NormalMap:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("normalMap", "Normal Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("bumpFactor", "Bump Factor", 1.0f));
				break;
			}

		case MwShaderOperation_RefractionMap:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("refractionMap", "Refraction Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("refractionFactor", "Refraction Factor", 0.0f));
				break;
			}

		case MwShaderOperation_VertexLighting:
			{
				break;
			}

		case MwShaderOperation_PixelLighting:
			{
				break;
			}

		case MwShaderOperation_AlignScreenQuad:
			{
				break;
			}

		case MwShaderOperation_BlurMap:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("blurMap", "Blur Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("blurFactor", "Blur Factor", 0.0f));
				break;
			}

		case MwShaderOperation_Tint:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("tintColor", "Tint Color", MwVector4()));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("tintAmount", "Tint Amount", 0.0f));
				break;
			}

		case MwShaderOperation_HBlur:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("hBlurMap", "HBlur Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("hBlurFactor", "HBlur Factor", 0.0f));
				break;
			}

		case MwShaderOperation_VBlur:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("vBlurMap", "VBlur Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("vBlurFactor", "VBlur Factor", 0.0f));
				break;
			}

		case MwShaderOperation_ProjectTexture:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("projectionMap", "Projection Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("projectionCamera", "Projection Cam", MwParameterType_ReferenceCamera, 0));
				break;
			}

		case MwShaderOperation_ProjectPicture:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("projectionMap", "Picture Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("projectionCamera", "Picture Cam", MwParameterType_ReferenceCamera, 0));
				break;
			}

		case MwShaderOperation_ShadowMapWriter:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("shadowMapDepth", "Max", 0.0f));
				break;
			}

		case MwShaderOperation_ShadowMap:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("shadowMapCamera", "ShadowMap Cam", MwParameterType_ReferenceCamera, 0));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("shadowMap", "Shadow Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("shadowMapLight", "Light Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("shadowMapBias", "Bias", 0.0f));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("shadowMapDepth", "Max", 0.0f));
				break;
			}

		case MwShaderOperation_BlendTexture:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("blendMap", "Blend Map", MwParameterType_ReferenceTexture, defaultTexture));
				this->properties.Insert(propertyIndex++, new MwBoundProperty("blendFactor", "Blend Factor", 0.0f));
				break;
			}

		case MwShaderOperation_TextureTransform:
			{
				this->properties.Insert(propertyIndex++, new MwBoundProperty("textureTransform", "Texture Transform", MwParameterType_ReferenceTransform, 0));
				break;
			}
	}

	int numNewProperties = properties.count - numProperties;
	this->shaderSlots.Insert(index, MwMaterialShaderSlot(shaderOp, colorOp, propertyFirst, numNewProperties));

	int count = shaderSlots.count;
	for (int i = index + 1; i < count; i++)
		this->shaderSlots[i].propertyFirst += numNewProperties;
}

int MwMaterial::AddShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp)
{
	this->InsertShaderSlot(shaderOp, colorOp, shaderSlots.count);
	return shaderSlots.count - 1;
}

void MwMaterial::RemoveShaderSlot(int index)
{
	int count = this->shaderSlots.count;
	for (int i = index + 1; i < count; i++)
		this->shaderSlots[i].propertyFirst -= this->shaderSlots[index].propertyCount;

	this->properties.RemoveRange(shaderSlots[index].propertyFirst, shaderSlots[index].propertyCount);
	this->shaderSlots.RemoveAt(index);
}

void MwMaterial::MoveShaderSlot(int originalIndex, int newIndex)
{
	int originalIndexPropertiesStart = this->shaderSlots[originalIndex].propertyFirst;
	int originalIndexPropertiesCount = this->shaderSlots[originalIndex].propertyCount;

	int start = MwMath::Min(originalIndex, newIndex);
	int propertyFirst = this->shaderSlots[start].propertyFirst;

	this->shaderSlots.Move(originalIndex, newIndex, 1);

	int count = this->shaderSlots.count;
	for (int i = start; i < count; i++)
	{
		this->shaderSlots[i].propertyFirst = propertyFirst;
		propertyFirst += this->shaderSlots[i].propertyCount;
	}

	this->properties.Move(originalIndexPropertiesStart, this->shaderSlots[newIndex].propertyFirst, originalIndexPropertiesCount);
}

void MwMaterial::ClearShaderSlots()
{
	this->shaderSlots.Clear();
	this->properties.Clear();

	this->shadingProperties.Clear();
}

bool MwMaterial::UpdateShader()
{
	this->successfullyCompiled = false;

	// Setup material
	this->deviceShader->ClearOperations();
	for (int i = 0; i < this->shaderSlots.count; i++)
		this->deviceShader->AddOperation(this->shaderSlots[i].shaderOp, this->shaderSlots[i].colorOp);
	
	// Update shader
	if (!this->deviceShader->Update(this->compilationMessage))
		return false;

	// Setup parameters
	for (int i = 0; i < this->properties.count; i++)
		((MwBoundProperty*)this->properties[i])->boundIndex = this->deviceShader->GetParameterAddress(((MwBoundProperty*)this->properties[i])->boundName);

	this->paramAddressWorldMatrix = this->deviceShader->GetParameterAddress("worldMatrix");
	this->paramAddressViewMatrix = this->deviceShader->GetParameterAddress("viewMatrix");
	this->paramAddressProjectionMatrix = this->deviceShader->GetParameterAddress("projectionMatrix");
	this->paramAddressViewPosition = this->deviceShader->GetParameterAddress("viewPosition");
	this->paramAddressLightsPos = this->deviceShader->GetParameterAddress("lightsPos");
	this->paramAddressLightsColor = this->deviceShader->GetParameterAddress("lightsColor");
	this->paramAddressLightsIntensity = this->deviceShader->GetParameterAddress("lightsIntensity");
	this->paramAddressActiveLightsCount = this->deviceShader->GetParameterAddress("activeLightsCount");
	this->paramAddressAmbientLight = this->deviceShader->GetParameterAddress("ambientLight");

	// Get some common parameters
	this->isAnimated = false;
	this->lightSourcesCount = 0;
	for (int i = 0; i < this->shaderSlots.count; i++)
	{
		if (this->shaderSlots[i].shaderOp == MwShaderOperation_LightSource)
			this->lightSourcesCount++;
		if (this->shaderSlots[i].shaderOp == MwShaderOperation_Skinning)
			this->isAnimated = true;
	}

	this->successfullyCompiled = true;
	return true;
}

void MwMaterial::ApplyProperty(MwBoundProperty *materialProperty)
{
	if (!this->successfullyCompiled)
		return;

	switch (materialProperty->type)
	{
		case MwParameterType_ReferenceTexture:
		{
			MwTexture2D *texture = (MwTexture2D*)materialProperty->GetEffectiveValue();
			if (texture != 0)
				this->deviceShader->SetParameter(materialProperty->boundIndex, 0, texture->deviceTexture);
			break;
		}

		case MwParameterType_ReferenceCamera:
		{
			MwCamera *camera = (MwCamera*)materialProperty->GetEffectiveValue();
			if (camera != 0)
				this->deviceShader->SetParameter(materialProperty->boundIndex, 0, &camera->viewProjection);
			break;
		}

		case MwParameterType_ReferenceTransform:
		{
			MwTransform *transform = (MwTransform*)materialProperty->GetEffectiveValue();
			if (transform != 0)
				this->deviceShader->SetParameter(materialProperty->boundIndex, 0, &transform->matrix);
			break;
		}

		case MwParameterType_ReferenceVector3:
		{
			MwTransform *transform = (MwTransform*)materialProperty->GetEffectiveValue();
			if (transform != 0)
			{
				this->deviceShader->SetParameter(materialProperty->boundIndex, 0, &transform->matrix._41);
			}
			break;
		}

		default:
		{
			this->deviceShader->SetParameter(materialProperty->boundIndex, 0, materialProperty->GetEffectiveValue());
			break;
		}
	}
}

void MwMaterial::ApplyProperties()
{
	if (!this->successfullyCompiled)
		return;

	int count = this->properties.count;
	for (int i = 0; i < count; i++)
		this->ApplyProperty((MwBoundProperty*)this->properties[i]);
}

void MwMaterial::ApplyLights(MwVector3 &location)
{
	if (this->lightSourcesCount > 0)
	{
		this->context->CalculateNearestActiveLights(this->lightSourcesCount, location);
		int lightsCount = this->context->nearestActiveLights.count;
		this->deviceShader->SetParameter(this->paramAddressActiveLightsCount, 0, &lightsCount);
		if (lightsCount > 0)
		{
			if ((this->paramAddressLightsPos != -1) && (this->paramAddressLightsColor != -1) && (this->paramAddressLightsIntensity != -1))
			{
				for (int i = 0; i < lightsCount; i++)
				{
					this->deviceShader->SetParameter(this->paramAddressLightsPos, i, &this->context->nearestActiveLights[i]->lightPos);
					this->deviceShader->SetParameter(this->paramAddressLightsColor, i , this->context->nearestActiveLights[i]->lightRef->properties[MwLight::propertyIndex_Color]->GetEffectiveValue());
					this->deviceShader->SetParameter(this->paramAddressLightsIntensity, i , this->context->nearestActiveLights[i]->lightRef->properties[MwLight::propertyIndex_Intensity]->GetEffectiveValue());
				}
			}
		}
	}
	else
		this->deviceShader->SetParameter(this->paramAddressActiveLightsCount, 0, &this->lightSourcesCount);
}

void MwMaterial::ApplyBones()
{
	// TODO: addresses of parameters should be precalculated, or GetParameterAddress should accept not a parameter name, but an id, so it can map fast and directly to the address
	if (this->isAnimated)
	{
		if (this->paramAddressWorldMatrix != -1)
		{
			for (int i = 0; i < this->context->bones.count; i++)
			{
				this->deviceShader->SetParameter(this->paramAddressWorldMatrix ,i, &this->context->bones[i]);
			}
		}
	}
}


bool MwMaterial::Deserialize(MwBaseStream &source)
{
	if (MwBaseResource::Deserialize(source))
	{
		return this->UpdateShader();
	}

	return false;
}

void MwMaterial::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	writer.BeginChunk(MwMaterial::SerializationId_ShaderSlots);

	for (int i = 0; i < this->shaderSlots.count; i++)
	{
		writer.BeginChunk(MwMaterial::SerializationId_ShaderSlot);

		writer.BeginChunk(MwMaterial::SerializationId_ShaderOp);
		writer.stream->WriteInt16(this->shaderSlots[i].shaderOp);
		writer.EndChunk();

		writer.BeginChunk(MwMaterial::SerializationId_ColorOp);
		writer.stream->WriteInt16(this->shaderSlots[i].colorOp);
		writer.EndChunk();

		writer.EndChunk();
	}

	writer.EndChunk();

	writer.BeginChunk(MwMaterial::SerializationId_RenderStates);

	for (int i = 0; i < this->shaderSlots.count; i++)
	{
		writer.BeginChunk(MwMaterial::SerializationId_RenderState);
		writer.stream->WriteInt16(this->renderStates[i]);
		writer.EndChunk();
	}

	writer.EndChunk();

	// Make base serialization at and, because shader data creates properties, which need to be filled afterwards
	MwBaseResource::SerializeChunks(writer);
}

bool MwMaterial::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwMaterial::SerializationId_ShaderSlots:
		{
			break;
		}

		case MwMaterial::SerializationId_ShaderSlot:
		{
            //TODO: Rightfully, the creation of the shader slot should be here, but as the shader operation is required, for now it's created on ShaderOp, assuming it will be the first encountered data in the shader block
			break;
		}

		case MwMaterial::SerializationId_ShaderOp:
		{
			this->AddShaderSlot(((MwShaderOperation)(reader.stream->ReadInt16())), MwColorOperation_None);
			break;
		}

		case MwMaterial::SerializationId_ColorOp:
		{
			this->shaderSlots[this->shaderSlots.count - 1].colorOp = ((MwColorOperation)(reader.stream->ReadInt16()));
			break;
		}

		case MwMaterial::SerializationId_RenderStates:
		{
			break;
		}

		case MwMaterial::SerializationId_RenderState:
		{
			this->renderStates.Add((MwRenderState)reader.stream->ReadInt16());
			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}
