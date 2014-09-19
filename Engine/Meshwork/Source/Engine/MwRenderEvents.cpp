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

#include "MwRenderEvents.h"

#include "Meshwork.h"


MwRenderEvents::MwRenderEvents(Meshwork &meshwork) 
	: MwTraceEvents(meshwork)
{
}
	
MwRenderEvents::~MwRenderEvents(void)
{
}

void MwRenderEvents::SetupNewFrame()
{
	this->numRenderedObjects = 0;
	this->updateState = !this->updateState;
}

void MwRenderEvents::OnMaterial(MwTraceParameters &parameters)
{
	if (!parameters.materialRef->successfullyCompiled)
		return;

	parameters.materialRef->deviceShader->SetParameter(parameters.materialRef->paramAddressAmbientLight, 0, &parameters.materialRef->context->ambientLighting);

	parameters.materialRef->ApplyProperties();
}
    
   
void MwRenderEvents::OnMesh(MwTraceParameters &parameters)
{
	if (!parameters.materialRef->successfullyCompiled)
		return;

	if (parameters.transformRef == 0)
		return;
	
	MwMatrix transform;
	MwMatrix::Multiply(transform, parameters.transformRef->matrix, parameters.cameraRef->viewProjection);
	if (parameters.meshRef->properties[MwMesh::propertyIndex_Cull]->GetBool())
		if (!parameters.meshRef->bounds.InsideViewFrustum(transform))
	        return;

	parameters.materialRef->deviceShader->SetParameter(parameters.materialRef->paramAddressViewMatrix, 0, &parameters.cameraRef->view);
	parameters.materialRef->deviceShader->SetParameter(parameters.materialRef->paramAddressProjectionMatrix, 0, &parameters.cameraRef->projection);
	parameters.materialRef->deviceShader->SetParameter(parameters.materialRef->paramAddressViewPosition, 0, &parameters.cameraRef->position);
	
	if (parameters.materialRef->isAnimated)
		parameters.materialRef->ApplyBones();
	else
		parameters.materialRef->deviceShader->SetParameter(parameters.materialRef->paramAddressWorldMatrix, 0, &parameters.transformRef->matrix);

	MwVector3 lightsReferenceLocation;
	MwMatrix::GetTranslation(lightsReferenceLocation, parameters.transformRef->matrix);
	parameters.materialRef->ApplyLights(lightsReferenceLocation);

	this->meshwork->graphicsDevice->SetShader(*parameters.materialRef->deviceShader);

	this->meshwork->graphicsDevice->SetMesh(*parameters.meshRef->deviceMesh);

    this->meshwork->graphicsDevice->RenderMesh();
        
	this->numRenderedObjects++;
}
    
void MwRenderEvents::OnMechanism(MwTraceParameters &parameters)
{
    if (parameters.mechanismRef->_updateState != this->updateState)
    {
        parameters.mechanismRef->Process(this->meshwork->timer->time);
        parameters.mechanismRef->_updateState = this->updateState;
    }
}

void MwRenderEvents::OnTransform(MwTraceParameters &parameters)
{
	if (parameters.transformRef->_updateState != this->updateState)
    {
        parameters.transformRef->Process();
        parameters.transformRef->_updateState = this->updateState;
    }
}

void MwRenderEvents::OnLight(MwTraceParameters &parameters)
{
	if(parameters.lightRef->properties[MwLight::propertyIndex_Active]->GetBool())
	{
		this->meshwork->activeLightsCollecting->SetSize(this->meshwork->activeLightsCollecting->count + 1);
		MwActiveLightInfo *lightInfo = &this->meshwork->activeLightsCollecting->Get(this->meshwork->activeLightsCollecting->count - 1);

		lightInfo->lightRef = parameters.lightRef;
		lightInfo->lightTransform = parameters.transformRef->matrix;
		MwMatrix::GetTranslation(lightInfo->lightPos, lightInfo->lightTransform);
	}
}

void MwRenderEvents::OnSoundEmitter(MwTraceParameters &parameters)
{
	if (parameters.transformRef != 0)
		parameters.soundEmitterRef->ApplyWorldLocation(&parameters.transformRef->matrix);

	parameters.soundEmitterRef->ApplyProperties();
}

void MwRenderEvents::OnSoundReceptor(MwTraceParameters &parameters)
{
	if (parameters.transformRef != 0)
		parameters.soundReceptorRef->ApplyWorldLocation(&parameters.transformRef->matrix);
}

void MwRenderEvents::OnTexture2D(MwTraceParameters &parameters)
{
	parameters.textureRef->UpdateToProperties();

	this->meshwork->graphicsDevice->SetRenderTargetTexture(parameters.textureRef->deviceTexture);

	this->meshwork->currentRenderTarget = parameters.textureRef;
}

void MwRenderEvents::OnExitedBranch(MwTraceParameters &parameters)
{
	if (this->meshwork->currentRenderTarget != parameters.textureRef)
	{
		if (parameters.textureRef == 0)
			this->meshwork->graphicsDevice->SetRenderTargetWindow(this->meshwork->windowHandle);
		else
			this->meshwork->graphicsDevice->SetRenderTargetTexture(parameters.textureRef->deviceTexture);

		this->meshwork->currentRenderTarget = parameters.textureRef;
	}
}
