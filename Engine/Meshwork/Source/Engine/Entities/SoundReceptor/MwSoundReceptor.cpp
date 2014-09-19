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

#include "MwSoundReceptor.h"

#include "..\..\Meshwork.h"

MwSoundReceptor::MwSoundReceptor(Meshwork *context)
{
	this->context = context;

	this->typeId = MwSoundReceptor::classId;
	this->resourceType = MwResourceType_SoundReceptor;

	this->deviceSoundReceptor = this->context->audioDevice->CreateSoundReceptor();

	this->paramAddressWorldMatrix = this->deviceSoundReceptor->GetParameterAddress("worldMatrix");
	this->paramAddressVelocity = this->deviceSoundReceptor->GetParameterAddress("velocity");
}


MwSoundReceptor::~MwSoundReceptor(void)
{
	delete this->deviceSoundReceptor;
}

void MwSoundReceptor::ApplyWorldLocation(MwMatrix *worldMatrix)
{
	this->deviceSoundReceptor->SetParameter(this->paramAddressWorldMatrix, 0, worldMatrix);
	
	MwMatrix::GetTranslation(this->position, *worldMatrix);
	MwVector3::Subtract(this->velocity, this->position, this->lastPosition);
	this->lastPosition = this->position;

	this->deviceSoundReceptor->SetParameter(this->paramAddressVelocity, 0, &this->velocity);
}
