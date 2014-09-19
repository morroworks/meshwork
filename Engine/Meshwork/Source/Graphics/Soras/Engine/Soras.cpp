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

#include "Soras.h"

#include "Primitive\SrUnit.h"

#include "..\..\..\Tools\\MwMem.h"
#include "..\..\..\Tools\\MwMath.h"
#include "..\..\..\Tools\MwIntegralQuotientDistribution.h"
#include "..\..\..\Tools\OS\MwOSUtils.h"

Soras::Soras(void)
{
	SrMatrix::Identity(this->worldMatrix);
	SrMatrix::Identity(this->viewProjectionMatrix);

    this->material.ambient.a = 0xff;
    this->material.ambient.r = 0x20;
    this->material.ambient.g = 0x20;
    this->material.ambient.b = 0x20;
    this->material.diffuse.a = 0xff;
    this->material.diffuse.r = 0xff;
    this->material.diffuse.g = 0xff;
    this->material.diffuse.b = 0xff;
    this->material.specular.a = 0xff;
    this->material.specular.r = 0xff;
    this->material.specular.g = 0xff;
    this->material.specular.b = 0xff;
    this->material.gloss = 60.0f;

	this->shadingParameters.fogStart = 0;
    this->shadingParameters.fogEnd = 1000;
    this->shadingParameters.fogColor = SrARGB(0xff, 0xff, 0xff, 0xff);
    this->shadingParameters.refractionFactor = 20.0f;
    this->shadingParameters.basicLightColor = SrARGB(0xff, 0xff, 0xff, 0xff);
    this->shadingParameters.globalAmbient = SrARGBInt(0xff, 0xff, 0xff, 0xff);
    this->shadingParameters.cellDiffuseSegmentation = 0xff / 4;
    this->shadingParameters.cellSpecularSegmentation = 0xff / 3;
    this->shadingParameters.cellEnvMapSegmentation = SrUnit::high / 4;
    this->shadingParameters.tintColor = SrARGB(0xc0, 0xf5, 0xe4, 0x9c);

	this->cullMode = SrCullModes::CounterClockWise;
	this->textureSampler = SrTextureSamplers::Linear;
	this->blending = 0;

	this->threadsPool = 0;
	this->zBuffer = 0;
	this->zBufferStencil = 0;
	this->zBufferSize = 0;

	this->renderSurface = 0;

	this->maxBones = 64;
	this->bones = new SrMatrix[this->maxBones];

	this->numLights = 0;
	this->maxLights = 0;
	this->SetLighsCount(8);

	this->SetThreadCount(MwOSUtils::GetNumberOfProcessors());
}


Soras::~Soras(void)
{
	this->SetThreadCount(0);

	delete[] this->zBuffer;
	delete[] this->zBufferStencil;

	delete[] this->bones;
	
	delete[] this->lights;
}

bool Soras::NormalizationNecessary()
{
    const float necessityThreshold = 0.001f;

    float l = MwMath::Sqrt(this->worldMatrixNormals._11 * this->worldMatrixNormals._11 +
						  this->worldMatrixNormals._12 * this->worldMatrixNormals._12 +
						  this->worldMatrixNormals._13 * this->worldMatrixNormals._13);
    if (MwMath::Abs(1.0f - l) > necessityThreshold)
        return true;

    l = MwMath::Sqrt(this->worldMatrixNormals._21 * this->worldMatrixNormals._21 +
					this->worldMatrixNormals._22 * this->worldMatrixNormals._22 +
					this->worldMatrixNormals._23 * this->worldMatrixNormals._23);
    if (MwMath::Abs(1.0f - l) > necessityThreshold)
        return true;

	l = MwMath::Sqrt(this->worldMatrixNormals._31 * this->worldMatrixNormals._31 +
					this->worldMatrixNormals._32 * this->worldMatrixNormals._32 +
					this->worldMatrixNormals._33 * this->worldMatrixNormals._33);
    if (MwMath::Abs(1.0f - l) > necessityThreshold)
        return true;

    return false;
}


void Soras::Clear(SrARGB color)
{
    this->renderSurface->Fill(color);
}

void Soras::ClearZ()
{
	MwMem::Copy(this->zBuffer, this->zBufferStencil, this->renderSurface->width * this->renderSurface->height * sizeof(float));
}

void Soras::SetThreadCount(int threadCount)
{
	for (int i = 0; i < this->renderThreads.count; i++)
		delete this->renderThreads[i];
	this->renderThreads.Clear();

    for (int i = 0; i < threadCount; i++)
		this->renderThreads.Add(new SrRenderThread(this));

	if (this->threadsPool != 0)
	{
		delete this->threadsPool;
		this->threadsPool = 0;
	}

	if (threadCount != 0)
		this->threadsPool = new MwThreadsPool(threadCount);
}

void Soras::SetRenderSurface(SrTexture *renderSurface)
{
	if (renderSurface != 0)
	{
		unsigned int newZBufferSize = renderSurface->width * renderSurface->height;
		if (newZBufferSize != this->zBufferSize)
		{
			if (this->zBuffer != 0)
			{
				delete[] this->zBuffer;
				delete[] this->zBufferStencil;
			}

			this->zBufferSize = newZBufferSize;
			this->zBuffer = new float[this->zBufferSize];
			this->zBufferStencil = new float[this->zBufferSize];

			for (unsigned int i = 0; i < this->zBufferSize; i++)
				this->zBufferStencil[i] = MwMath::FloatMax;
		}
	}

	this->renderSurface = renderSurface;
}

void Soras::SetMesh(SrMesh *mesh)
{
	this->mesh = mesh;
}

void Soras::ClearShaderOperations()
{
    this->pixelOps.Clear();
    this->vertexOps.Clear();
    this->shaderTextures.Clear();
}

void Soras::AddVertexShader(SrShaderOperation shaderOperation, SrShaderOperation colorOperation)
{
	this->vertexOps.Add(shaderOperation);

	if (colorOperation != 0)
		this->vertexOps.Add(colorOperation);
}

void Soras::AddPixelShader(SrShaderOperation shaderOperation, SrShaderOperation colorOperation, SrTexture* texture)
{
	this->pixelOps.Add(shaderOperation);

	if (colorOperation != 0)
		this->pixelOps.Add(colorOperation);

	if (texture != 0)
		this->shaderTextures.Add(texture);
}

void Soras::SetLighsCount(int numLights)
{
	if (numLights > this->maxLights)
	{
		const int stride = 8;
		int newMax = this->maxLights + stride;
		while (newMax < numLights)
			newMax += stride;

		SrLight *newLights = new SrLight[newMax];
		if (this->maxLights > 0)
		{
			MwMem::Copy(newLights, this->lights, this->maxLights * sizeof(SrLight));
			delete[] this->lights;
		}

		this->lights = newLights;
		this->maxLights = newMax;
	}

	this->numLights = numLights;
}

void Soras::RenderMesh()
{
	SrMatrix::InvertTranspose3x3(this->worldMatrixNormals, this->worldMatrix);
    
	this->normalizeNormals = this->NormalizationNecessary();

    this->materialAmbient.a = (this->material.ambient.a * this->shadingParameters.globalAmbient.a) >> 8;
    this->materialAmbient.r = (this->material.ambient.r * this->shadingParameters.globalAmbient.r) >> 8;
    this->materialAmbient.g = (this->material.ambient.g * this->shadingParameters.globalAmbient.g) >> 8;
    this->materialAmbient.b = (this->material.ambient.b * this->shadingParameters.globalAmbient.b) >> 8;

    this->numVisiblePrimitives = 0;

    
	MwIntegralQuotientDistribution distribution(this->mesh->numVertices, this->renderThreads.count);

    int indexStart, 
		indexEnd = -1;
    for (int i = 0; i < this->renderThreads.count; i++)
    {
		int numVertices = distribution.PullSequential();

		indexStart = indexEnd + 1;
        indexEnd = indexEnd + numVertices;

        this->renderThreads[i]->vertexStart = indexStart;
        this->renderThreads[i]->vertexEnd = indexEnd;

		if (numVertices != 0)
			this->threadsPool->QueueTask(SrRenderThread::ComputeVertices, this->renderThreads[i]);
			//SrRenderThread::ComputeVertices(this->renderThreads[i]);
    }

	this->threadsPool->WaitAll();


    this->mesh->numVisiblePrimitives = 0;
    this->cull_PrimitiveIndex = 0;
    int numPrimitives = this->mesh->numIndices / 3;
    for (int i = 0; i < numPrimitives; i++)
    {
		if (this->cullMode(this))
        {
            this->mesh->visiblePrimitives[this->mesh->numVisiblePrimitives] = cull_PrimitiveIndex;
            this->mesh->numVisiblePrimitives++;
        }
        this->cull_PrimitiveIndex += 3;
    }


	distribution.Setup(this->mesh->numVisiblePrimitives, this->renderThreads.count);

    indexEnd = -1;
    for (int i = 0; i < this->renderThreads.count; i++)
    {
		int numPrimitives = distribution.PullSequential();

		indexStart = indexEnd + 1;
        indexEnd = indexEnd + numPrimitives;

        this->renderThreads[i]->primitiveStart = indexStart;
        this->renderThreads[i]->primitiveEnd = indexEnd;
        
		if (numPrimitives != 0)
			this->threadsPool->QueueTask(SrRenderThread::RenderPrimitives, this->renderThreads[i]);
			//SrRenderThread::RenderPrimitives(this->renderThreads[i]);
    }

	this->threadsPool->WaitAll();
}