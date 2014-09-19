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

#include "MwDynamicShaderWriter.h"


MwDynamicShaderWriter::MwDynamicShaderWriter(bool animated, MwList<MwDynamicShaderConstantBufferInfo*> *constantBuffersInfo, MwStrings *textureBuffersInfo)
{
	this->animated = animated;
	
	this->numLights = 0;
	this->textureSlots = 0;
	this->texCoordSlots = 0;

	this->constantBuffersInfo = constantBuffersInfo;
	this->textureBuffersInfo = textureBuffersInfo;
	
	this->constantBuffersInfo->Add(new MwDynamicShaderConstantBufferInfo());

	if (this->animated)
	{
		this->parameters.ProvideDefinition("bones", 
			"cbuffer Bones : register(b1)\r\n{\r\n"
			"\tfloat4x4 worldMatrix[64];\r\n};\r\n");

		this->constantBuffersInfo->Add(new MwDynamicShaderConstantBufferInfo());
		this->constantBuffersInfo->Get(1)->Add("worldMatrix", 64, 64);
	}

	this->parameters.ProvideDefinition("", "cbuffer Parameters : register(b0)\r\n{");

	if (!this->animated)
	{
		this->parameters.ProvideDefinition("worldMatrix", "\tfloat4x4 worldMatrix : World;");
		this->constantBuffersInfo->Get(0)->Add("worldMatrix", 64);
	}

	this->parameters.ProvideDefinition("viewProjectionMatrix", "\tfloat4x4 viewProjectionMatrix : ViewProjection;");//
	this->parameters.ProvideDefinition("ambientLight", "\tfloat4 ambientLight;");
	this->parameters.ProvideDefinition("viewPosition", "\tfloat3 viewPosition;");
	this->constantBuffersInfo->Get(0)->Add("viewProjectionMatrix", 64);
	this->constantBuffersInfo->Get(0)->Add("ambientLight", 16);
	this->constantBuffersInfo->Get(0)->Add("viewPosition", 12);

	this->vsInputType.ProvideDefinition("", "struct VSInput\r\n{");
	this->vsInputType.ProvideDefinition("pos", "\tfloat3 pos: POSITION;");
	if (this->animated)
	{
		this->vsInputType.ProvideDefinition("boneIndices", "\tfloat4 boneIndices: BLENDINDICES;");
		this->vsInputType.ProvideDefinition("boneWeights", "\tfloat4 boneWeights: BLENDWEIGHT;");
	}

	this->sIOType.ProvideDefinition("", "struct SIO\r\n{");
	this->sIOType.ProvideDefinition("pos", "\tfloat4 pos: SV_POSITION;");

	this->psOutputType.ProvideDefinition("PSOutput", "struct PSOutput\r\n{");
	this->psOutputType.ProvideDefinition("color", "\tfloat4 color: SV_TARGET;");

	this->vsCode.ProvideDefinition("", "SIO VSMain(VSInput input)\r\n{");
	this->vsCode.ProvideDefinition("output", "\tSIO output;\r\n");
	if (this->animated)
	{
		this->vsCode.ProvideDefinition("\tbonesMatrix", "\tfloat4x4 bonesMatrix;");
		this->vsCode.ProvideDefinition("", "\tbonesMatrix = \r\n"
			"\t\tworldMatrix[input.boneIndices.x] * input.boneWeights.x +\r\n"
			"\t\tworldMatrix[input.boneIndices.y] * input.boneWeights.y +\r\n"
			"\t\tworldMatrix[input.boneIndices.z] * input.boneWeights.z +\r\n"
			"\t\tworldMatrix[input.boneIndices.w] * input.boneWeights.w;");

        vsCode.ProvideDefinition("worldPos", "\tfloat4 worldPos = mul(bonesMatrix, float4(input.pos, 1.0));\r\n");
	}
	else
	{
        vsCode.ProvideDefinition("worldPos", "\tfloat4 worldPos = mul(worldMatrix, float4(input.pos, 1.0));\r\n");
	}
	this->vsCode.ProvideDefinition(".pos", "\toutput.pos = mul(viewProjectionMatrix, worldPos);\r\n");

	this->psCode.ProvideDefinition("", "PSOutput PSMain(SIO input)\r\n{");
	this->psCode.ProvideDefinition("output", "\tPSOutput output;\r\n");
}


MwDynamicShaderWriter::~MwDynamicShaderWriter(void)
{
}

void MwDynamicShaderWriter::AddShaderSlot(MwShaderOperation shaderOp, MwColorOperation colorOp)
{
	switch (shaderOp)
	{
		case MwShaderOperation_BasicShading:
		{
			this->vsInputType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			this->sIOType.ProvideDefinition("color", "\tfloat4 color: COLOR;");

			if (this->animated)
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(bonesMatrix, input.normal));");
			else
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(worldMatrix, input.normal));");
			this->vsCode.ProvideDefinition("", "\toutput.color = saturate(-normal.z);\r\n");

			psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "input.color", colorOp) + "\r\n");
			break;
		}

		case MwShaderOperation_Material:
		{
			if (this->parameters.ProvideDefinition("material",
				"\tfloat4 materialAmbient;\r\n"
				"\tfloat4 materialDiffuse;\r\n"
				"\tfloat4 materialSpecular;\r\n"
				"\tfloat materialGloss;"))
			{
				this->constantBuffersInfo->Get(0)->Add("materialAmbient", 16);
				this->constantBuffersInfo->Get(0)->Add("materialDiffuse", 16);
				this->constantBuffersInfo->Get(0)->Add("materialSpecular", 16);
				this->constantBuffersInfo->Get(0)->Add("materialGloss", 4);
			}

			psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "materialAmbient", colorOp) + "\r\n");
	
			break;
		}

		case MwShaderOperation_LightSource:
			{
                numLights++;
				break;
			}

		case MwShaderOperation_AlignScreenQuad:
			{
				if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
					this->texCoordSlots++;

				this->vsCode.ProvideDefinition("screenPos", "\tfloat2 screenPos;");
				this->vsCode.ProvideDefinition("",
					"\tscreenPos = sign(input.pos.xy);\r\n"
					"\toutput.pos = float4(screenPos, 0.999, 1.0);\r\n"
					//"\toutput.pos = float4(screenPos, 0.001, 1.0);\r\n"
					"\toutput.pos.y = -output.pos.y; // remove this, instead change vertex order");
               
				this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = (screenPos + 1) / 2;");

				break;
			}

		case MwShaderOperation_VertexLighting:
		{
			if (this->numLights == 0)
				break;

			if (this->parameters.ProvideDefinition("activeLightsCount", "\tint activeLightsCount;"))
			{
				this->constantBuffersInfo->Get(0)->Add("activeLightsCount", 4);
			}

			this->vsInputType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			this->sIOType.ProvideDefinition("color", "\tfloat4 color: COLOR;");

			if (this->animated)
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(bonesMatrix, input.normal));");
			else
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(worldMatrix, input.normal));");

			//this->vsCode.ProvideDefinition("lightDP", "\tfloat lightDP;");
			//this->vsCode.ProvideDefinition("lightDF", "\tfloat lightDF;");
			//this->vsCode.ProvideDefinition("color", "\tfloat4 color;");
			//this->vsCode.ProvideDefinition("", 
			//	"\tcolor = materialAmbient;\r\n"
			//	"\tfor (int lightIndex = 0; lightIndex < activeLightsCount.x; lightIndex++)\r\n"
			//	"\t{\r\n"
			//	"\t\tlightDP = dot(input.normal, normalize(lightsPosIntensity[lightIndex].xyz - worldPos));\r\n"
			//	"\t\tlightDF = 1.0 - distance(worldPos, lightsPosIntensity[lightIndex].xyz) / lightsPosIntensity[lightIndex].w;\r\n"
			//	"\t\tcolor += lightsColor[lightIndex] * (lightDP * lightDF * materialDiffuse + pow(lightDP, materialGloss.x) * materialSpecular);\r\n"
			//	"\t}\r\n"
			//	);

			this->vsCode.ProvideDefinition("viewVector", "\tfloat3 viewVector = normalize(viewPosition - worldPos.xyz);");
			this->vsCode.ProvideDefinition("lightVector", "\tfloat3 lightVector;");
			this->vsCode.ProvideDefinition("lightReflectionVector", "\tfloat3 lightReflectionVector;");
			this->vsCode.ProvideDefinition("lightAttenuation", "\tfloat lightAttenuation;");
			this->vsCode.ProvideDefinition("lightDiffuse", "\tfloat lightDiffuse;");
			this->vsCode.ProvideDefinition("lightSpecular", "\tfloat lightSpecular;");
			this->vsCode.ProvideDefinition("color", "\tfloat4 color;");
			this->vsCode.ProvideDefinition("", 
				"\tcolor = ambientLight * materialAmbient;\r\n"
				"\tfor (int lightIndex = 0; lightIndex < activeLightsCount.x; lightIndex++)\r\n"
				"\t{\r\n"
				"\t\tlightVector = lightsPosIntensity[lightIndex].xyz - worldPos.xyz;\r\n"
				"\t\tlightAttenuation = 1 / length(lightVector);\r\n"
				"\t\tlightVector *= lightAttenuation;\r\n"
				"\t\tlightAttenuation *= lightsPosIntensity[lightIndex].w;\r\n"
				"\t\tlightDiffuse = saturate(dot(normal, lightVector)) * lightAttenuation * lightAttenuation;\r\n"
				"\t\tlightReflectionVector = normalize(lightVector + viewVector);\r\n"
				"\t\tlightSpecular = pow(saturate(dot(normal, lightReflectionVector)), materialGloss);\r\n"
				"\t\tcolor += lightsColor[lightIndex] * (lightDiffuse * materialDiffuse + lightSpecular * materialSpecular);\r\n"
				"\t}\r\n"
				);

			this->vsCode.ProvideDefinition("", "\toutput.color = color;");

			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "input.color", colorOp));
			break;
		}


		case MwShaderOperation_PixelLighting:
		{
			if (this->numLights == 0)
				break;

			if (this->parameters.ProvideDefinition("activeLightsCount", "\tint activeLightsCount;"))
			{
				this->constantBuffersInfo->Get(0)->Add("activeLightsCount", 4);
			}

			this->vsInputType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			this->sIOType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");
			this->sIOType.ProvideDefinition("worldPos", "\tfloat4 worldPos: POSITION;");

			if (this->animated)
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(bonesMatrix, input.normal));");
			else
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(worldMatrix, input.normal));");
			this->vsCode.ProvideDefinition(".normal", "\toutput.normal = normal;");
			this->vsCode.ProvideDefinition(".worldPos", "\toutput.worldPos = worldPos;");

			this->psCode.ProvideDefinition("lightDP", "\tfloat lightDP;");
			this->psCode.ProvideDefinition("lightDF", "\tfloat lightDF;");
			this->psCode.ProvideDefinition("color", "\tfloat4 color;");
			this->psCode.ProvideDefinition("", 
				"\tcolor = ambientLight * materialAmbient;\r\n"
				"\tfor (int lightIndex = 0; lightIndex < activeLightsCount.x; lightIndex++)\r\n"
				"\t{\r\n"
				"\t\tlightDP = dot(input.normal, normalize(lightsPosIntensity[lightIndex].xyz - input.worldPos));\r\n"
				"\t\tlightDF = 1.0 - distance(input.worldPos, lightsPosIntensity[lightIndex].xyz) / lightsPosIntensity[lightIndex].w;\r\n"
				"\t\tcolor += lightsColor[lightIndex] * (lightDP * lightDF * materialDiffuse + pow(lightDP, materialGloss.x) * materialSpecular);\r\n"
				"\t}\r\n"
				);

			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "color", colorOp));

			break;
		}

		case MwShaderOperation_Skinning:
		{
			break;
		}

		case MwShaderOperation_ColorMap:
		{
			if (this->various.ProvideDefinition("colorMap", 
				MwString("Texture2D tColorMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sColorMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("colorMap");
			}

			this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");
			
			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = input.texCoords;");

			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "tColorMap.Sample(sColorMap, input.texCoords)", colorOp));

			break;
		}

		case MwShaderOperation_EnvMap:
		{
			if (this->various.ProvideDefinition("envMap", 
				MwString("Texture2D tEnvMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sEnvMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("envMap");
			}

			if (this->parameters.ProvideDefinition("envFactor", "\tfloat envFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("envFactor", 4);
			}

			this->vsInputType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			this->sIOType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			if (this->animated)
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(bonesMatrix, input.normal));");
			else
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(worldMatrix, input.normal));");
			this->vsCode.ProvideDefinition(".normal", "\toutput.normal = normal;");

			psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "tEnvMap.Sample(sEnvMap, input.normal.xy) * envFactor", colorOp));

			break;
		}

		case MwShaderOperation_NormalMap:
		{
			// TODO: Implement real normal map and keep this operation as "BumpMap"
			if (this->various.ProvideDefinition("normalMap", 
				MwString("Texture2D tNormalMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sNormalMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("normalMap");
			}

			if (this->parameters.ProvideDefinition("bumpFactor", "\tfloat bumpFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("bumpFactor", 4);
			}

			this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");
			this->vsInputType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			this->sIOType.ProvideDefinition("normal", MwString("\tfloat3 normal: NORMAL;"));
			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			if (this->animated)
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(bonesMatrix, input.normal));");
			else
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(worldMatrix, input.normal));");
			this->vsCode.ProvideDefinition(".normal", "\toutput.normal = normal;");
			this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = input.texCoords;");
			
			this->psCode.ProvideDefinition("", 
				"\tfloat3 mapNormal = normalize(tNormalMap.Sample(sNormalMap, input.texCoords)) * bumpFactor * 2.0 - 1.0;\r\n"
				"\tinput.normal += mapNormal;\r\n");
				//"\t" + this->GetColorOperationCode("input.normal", "mapNormal", colorOp) + "\r\n");

			break;
		}

		case MwShaderOperation_RefractionMap:
		{
			if (this->various.ProvideDefinition("refractionMap", 
				MwString("Texture2D tRefractionMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sRefractionMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("refractionMap");
			}
			if (this->parameters.ProvideDefinition("refractionFactor", "\tfloat refractionFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("refractionFactor", 4);
			}

			this->vsInputType.ProvideDefinition("normal", "\tfloat3 normal: NORMAL;");

			if (this->sIOType.ProvideDefinition("screenSpaceNormal", MwString("\tfloat3 screenSpaceNormal: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;
			if (this->sIOType.ProvideDefinition("screenSpacePos", MwString("\tfloat3 screenSpacePos: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;


			if (this->animated)
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(bonesMatrix, input.normal));");
			else
				this->vsCode.ProvideDefinition("normal", "\tfloat3 normal = normalize(mul(worldMatrix, input.normal));");
			this->vsCode.ProvideDefinition("wvpNormal", "\tfloat3 wvpNormal = mul(normal, viewProjectionMatrix);");
			this->vsCode.ProvideDefinition(".screenSpaceNormal", "\toutput.screenSpaceNormal = wvpNormal;");
			this->vsCode.ProvideDefinition(".screenSpacePos", "\toutput.screenSpacePos = ((output.pos.xyz / output.pos.w) - 1.0) / 2.0;\r\n"
				"\toutput.screenSpacePos.y = -output.screenSpacePos.y;");

			//this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "tRefractionMap.Sample(sRefractionMap, input.screenSpacePos.xy - input.screenSpaceNormal.xy * refractionFactor)", colorOp));
			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "tRefractionMap.Sample(sRefractionMap, input.screenSpacePos.xy - input.normal.xy * refractionFactor)", colorOp));

			break;
		}

		case MwShaderOperation_BlurMap:
		{
			if (this->various.ProvideDefinition("blurMap", 
				MwString("Texture2D tBlurMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sBlurMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("blurMap");
			}

            if (this->parameters.ProvideDefinition("blurFactor", "float blurFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("blurFactor", 4);
			}

            this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");
			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = input.texCoords;");

            this->psCode.ProvideDefinition("blurSum", "\tfloat4 blurSum;");
            this->psCode.ProvideDefinition("", 
				"\tblurSum = tBlurMap.Sample(sBlurMap, input.texCoords);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2(-0.326212, -0.405805) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2(-0.840144, -0.073580) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2(-0.695914,  0.457137) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2(-0.203345,  0.620716) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2( 0.962340, -0.194983) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2( 0.473434, -0.480026) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2( 0.519456,  0.767022) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2( 0.185461, -0.893124) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2( 0.507431,  0.064425) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2( 0.896420,  0.412458) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2(-0.321940, -0.932615) * blurFactor);\r\n"
				"\tblurSum += tBlurMap.Sample(sBlurMap, input.texCoords + float2(-0.791559, -0.597705) * blurFactor);\r\n"
				"\tblurSum /= 13;\r\n");
            this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "blurSum", colorOp));
		}

		case MwShaderOperation_Tint:
		{
			if (this->parameters.ProvideDefinition("tint",
				"\tfloat4 tintColor;\r\n"
				"\tfloat tintAmount;"))
			{
				this->constantBuffersInfo->Get(0)->Add("tintColor", 16);
				this->constantBuffersInfo->Get(0)->Add("tintAmount", 4);
			}

			psCode.ProvideDefinition("tintFactor", "float tintFactor;");
			psCode.ProvideDefinition("", "\ttintFactor = (output.color.x + output.color.y + output.color.z) / 3;");
			psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "lerp(output.color, tintColor * float4(tintFactor, tintFactor, tintFactor, output.color.w), tintAmount)", colorOp));
			break;
		}

		case MwShaderOperation_HBlur:
		{
			if (this->various.ProvideDefinition("hBlurMap", 
				MwString("Texture2D tHBlurMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sHBlurMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("hBlurMap");
			}
			if (this->parameters.ProvideDefinition("hBlurFactor", "\tfloat hBlurFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("hBlurFactor", 4);
			}

            this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");
			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = input.texCoords;");

			this->psCode.ProvideDefinition("colorSum", "\tfloat4 colorSum;");

			this->psCode.ProvideDefinition("", 
				"\tcolorSum = tHBlurMap.Sample(sHBlurMap, input.texCoords + float2(-0.99, 0.0) * hBlurFactor);\r\n"
				"\tcolorSum += tHBlurMap.Sample(sHBlurMap, input.texCoords + float2(-0.66, 0.0) * hBlurFactor);\r\n"
				"\tcolorSum += tHBlurMap.Sample(sHBlurMap, input.texCoords + float2(-0.33, 0.0) * hBlurFactor);\r\n"
				"\tcolorSum += tHBlurMap.Sample(sHBlurMap, input.texCoords);\r\n"
				"\tcolorSum += tHBlurMap.Sample(sHBlurMap, input.texCoords + float2(0.33, 0.0) * hBlurFactor);\r\n"
				"\tcolorSum += tHBlurMap.Sample(sHBlurMap, input.texCoords + float2(0.66, 0.0) * hBlurFactor);\r\n"
				"\tcolorSum += tHBlurMap.Sample(sHBlurMap, input.texCoords + float2(0.99, 0.0) * hBlurFactor);\r\n"
				"\tcolorSum /= 7;");
			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "colorSum", colorOp));

			break;
		}

		case MwShaderOperation_VBlur:
		{
			if (this->various.ProvideDefinition("vBlurMap", 
				MwString("Texture2D tVBlurMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sVBlurMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("vBlurMap");
			}
			if (this->parameters.ProvideDefinition("vBlurFactor", "\tfloat vBlurFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("vBlurFactor", 4);
			}

            this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");
			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = input.texCoords;");

			this->psCode.ProvideDefinition("colorSum", "\tfloat4 colorSum;");

			this->psCode.ProvideDefinition("", 
				"\tcolorSum = tVBlurMap.Sample(sVBlurMap, input.texCoords + float2(0.0, -0.99) * vBlurFactor);\r\n"
				"\tcolorSum += tVBlurMap.Sample(sVBlurMap, input.texCoords + float2(0.0, -0.66) * vBlurFactor);\r\n"
				"\tcolorSum += tVBlurMap.Sample(sVBlurMap, input.texCoords + float2(0.0, -0.33) * vBlurFactor);\r\n"
				"\tcolorSum += tVBlurMap.Sample(sVBlurMap, input.texCoords);\r\n"
				"\tcolorSum += tVBlurMap.Sample(sVBlurMap, input.texCoords + float2(0.0, 0.33) * vBlurFactor);\r\n"
				"\tcolorSum += tVBlurMap.Sample(sVBlurMap, input.texCoords + float2(0.0, 0.66) * vBlurFactor);\r\n"
				"\tcolorSum += tVBlurMap.Sample(sVBlurMap, input.texCoords + float2(0.0, 0.99) * vBlurFactor);\r\n"
				"\tcolorSum /= 7;");
			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "colorSum", colorOp));

			break;
		}


		case MwShaderOperation_ProjectTexture:
		{
			if (this->various.ProvideDefinition("projectionMap", 
				MwString("Texture2D tProjectionMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sProjectionMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("projectionMap");
			}

			if (this->parameters.ProvideDefinition("projectionCamera", "\tfloat4x4 projectionCamera;"))
			{
				this->constantBuffersInfo->Get(0)->Add("projectionCamera", 64);
			}

			if (this->sIOType.ProvideDefinition("projectionTexCoords", MwString("\tfloat2 projectionTexCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition("projectionCoords", "\tfloat4 projectionCoords;");
			this->vsCode.ProvideDefinition("", "\tprojectionCoords = mul(projectionCamera, worldPos);");
			this->vsCode.ProvideDefinition(".projectionTexCoords", "\toutput.projectionTexCoords = ((projectionCoords.xy / projectionCoords.w) + 1.0) / 2.0;");

			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "tProjectionMap.Sample(sProjectionMap, input.projectionTexCoords)", colorOp));

			break;
		}

		case MwShaderOperation_ProjectPicture:
		{
			if (this->various.ProvideDefinition("projectionMap", 
				MwString("Texture2D tProjectionMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sProjectionMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("projectionMap");
			}

			if (this->parameters.ProvideDefinition("projectionCamera", "\tfloat4x4 projectionCamera;"))
			{
				this->constantBuffersInfo->Get(0)->Add("projectionCamera", 64);
			}

			if (this->sIOType.ProvideDefinition("projectionTexCoords", MwString("\tfloat2 projectionTexCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition("projectionCoords", "\tfloat4 projectionCoords;");
			this->vsCode.ProvideDefinition("", "\tprojectionCoords = mul(projectionCamera, worldPos);");
			this->vsCode.ProvideDefinition(".projectionTexCoords", "\toutput.projectionTexCoords = ((projectionCoords.xy / projectionCoords.w) + 1.0) / 2.0;");

			this->psCode.ProvideDefinition("", 
				MwString("\tif ((input.projectionTexCoords.x > 0.0) && (input.projectionTexCoords.x < 1.0) && (input.projectionTexCoords.y > 0.0) && (input.projectionTexCoords.y < 1.0))\r\n") +
				"\t\t" + this->GetColorOperationCode("output.color", "tProjectionMap.Sample(sProjectionMap, input.projectionTexCoords)", colorOp));

			break;
		}

		case MwShaderOperation_BlendTexture:
		{
			if (this->various.ProvideDefinition("blendMap", 
				MwString("Texture2D tBlendMap: register(t") + MwString(this->textureBuffersInfo->count) + ");\r\n"
				"sampler sBlendMap: register(s" + MwString(this->textureBuffersInfo->count) + ");\r\n"))
			{
				this->textureBuffersInfo->Add("blendMap");
			}

			if (this->parameters.ProvideDefinition("blendFactor", "\tfloat blendFactor;"))
			{
				this->constantBuffersInfo->Get(0)->Add("blendFactor", 4);
			}


            this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");
			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;

			this->vsCode.ProvideDefinition(".texCoords", "\toutput.texCoords = input.texCoords;");

			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("output.color", "lerp(output.color, tBlendMap.Sample(sBlendMap, input.texCoords), blendFactor)", colorOp));

			break;
		}

		case MwShaderOperation_TextureTransform:
		{
			if (this->parameters.ProvideDefinition("textureTransform", "\tfloat4x4 textureTransform;"))
			{
				this->constantBuffersInfo->Get(0)->Add("textureTransform", 64);
			}

            this->vsInputType.ProvideDefinition("texCoords", "\tfloat2 texCoords: TEXCOORD0;");

			if (this->sIOType.ProvideDefinition("texCoords", MwString("\tfloat2 texCoords: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;
			if (this->sIOType.ProvideDefinition("texCoordsTransform", MwString("\tfloat2 texCoordsTransform: TEXCOORD") + MwString(this->texCoordSlots) + ";"))
				this->texCoordSlots++;


			this->vsCode.ProvideDefinition(".texCoordsTransform", "\toutput.texCoordsTransform = mul(textureTransform, float4(input.texCoords, 0, 1)).xy;");

			this->psCode.ProvideDefinition("", MwString("\t") + this->GetColorOperationCode("input.texCoords", "input.texCoordsTransform", colorOp));
			break;
		}
	}
}

MwString MwDynamicShaderWriter::GetSourceCode()
{
	if (this->numLights > 0)
	{
		MwString numLightsStr(this->numLights);
		this->parameters.ProvideDefinition("",
			MwString("\tfloat4 lightsPosIntensity[") + numLightsStr + "];\r\n" +
			"\tfloat4 lightsColor[" + numLightsStr + "];\r\n");
		// lightsPos and lightsIntensity share the same shader constant - lightsPosIntensity.
		this->constantBuffersInfo->Get(0)->Add("lightsIntensity", 4, this->numLights, 12);
		this->constantBuffersInfo->Get(0)->Add("lightsPos", 12, this->numLights, 0);
		this->constantBuffersInfo->Get(0)->Add("lightsColor", 16, this->numLights);
	}

	return MwString(
		MwString("// Generated by Meshwork HLSL dynamic shader writer\r\n\r\n") +

		this->various.GetCode() + "\r\n" +

		this->parameters.GetCode() + "};\r\n\r\n" +

		this->vsInputType.GetCode() + "};\r\n\r\n" +

		this->sIOType.GetCode() + "};\r\n\r\n" +

		this->psOutputType.GetCode() + "};\r\n\r\n" +

		this->vsCode.GetCode() + "\r\n\treturn output;\r\n}\r\n\r\n" +

		this->psCode.GetCode() + "\r\n\treturn output;\r\n}");
}

MwString MwDynamicShaderWriter::GetColorOperationCode(MwString destArg, MwString sourceArg, MwColorOperation colorOp)
{
	switch (colorOp)
	{
		case MwColorOperation_None:
			return MwString();

		case MwColorOperation_Set:
			return destArg + " = " + sourceArg + ";";

		case MwColorOperation_Add:
			return destArg + " += " + sourceArg + ";";

		case MwColorOperation_Subtract:
			return destArg + " -= " + sourceArg + ";";

		case MwColorOperation_Modulate:
			return destArg + " *= " + sourceArg + ";";

		case MwColorOperation_Lighter:
			return destArg + " = max(" + destArg + ", " + sourceArg + ");";

		case MwColorOperation_Darker:
			return destArg + " = min(" + destArg + ", " + sourceArg + ");";

		default:
			return destArg + " = 0;";
	}
}
