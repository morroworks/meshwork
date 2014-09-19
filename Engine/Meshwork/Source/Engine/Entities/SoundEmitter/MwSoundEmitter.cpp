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

#include "MwSoundEmitter.h"

#include "..\..\Meshwork.h"

MwSoundEmitter::MwSoundEmitter(Meshwork *context)
{
	this->context = context;

	this->typeId = MwSoundEmitter::classId;
	this->resourceType = MwResourceType_SoundEmitter;

	this->deviceSoundEmitter = this->context->audioDevice->CreateSoundEmitter();

	this->properties.Add(new MwBoundProperty("sound", MwString("Sound"), MwParameterType_ReferenceSound, 0));
    this->properties.Add(new MwBoundProperty("ambient", MwString("Ambient"), false));
    this->properties.Add(new MwBoundProperty("play", MwString("Play"), true));
    this->properties.Add(new MwBoundProperty("loop", MwString("Loop"), true));
    this->properties.Add(new MwBoundProperty("volume", MwString("Volume"), 1.0f));
    this->properties.Add(new MwBoundProperty("rate", MwString("Rate"), 1.0f));

	for (int i = 0; i < this->properties.count; i++)
		((MwBoundProperty*)this->properties[i])->boundIndex = this->deviceSoundEmitter->GetParameterAddress(((MwBoundProperty*)this->properties[i])->boundName);

	this->paramAddressWorldMatrix = this->deviceSoundEmitter->GetParameterAddress("worldMatrix");
	this->paramAddressVelocity = this->deviceSoundEmitter->GetParameterAddress("velocity");
}


MwSoundEmitter::~MwSoundEmitter(void)
{
	delete this->deviceSoundEmitter;
}

void MwSoundEmitter::ApplyProperty(MwBoundProperty *emitterProperty)
{
	switch (emitterProperty->type)
	{
		case MwParameterType_ReferenceSound:
		{
			MwSound *sound = (MwSound*)emitterProperty->GetEffectiveValue();
			if (sound != 0)
				this->deviceSoundEmitter->SetParameter(emitterProperty->boundIndex, 0, sound->deviceSound);
			break;
		}

		default:
		{
			this->deviceSoundEmitter->SetParameter(emitterProperty->boundIndex, 0, emitterProperty->GetEffectiveValue());
			break;
		}
	}
}

void MwSoundEmitter::ApplyProperties()
{
	int count = this->properties.count;
	for (int i = 0; i < count; i++)
		this->ApplyProperty((MwBoundProperty*)this->properties[i]);
}

void MwSoundEmitter::ApplyWorldLocation(MwMatrix *worldMatrix)
{
	this->deviceSoundEmitter->SetParameter(this->paramAddressWorldMatrix, 0, worldMatrix);
	
	MwMatrix::GetTranslation(this->position, *worldMatrix);
	MwVector3::Subtract(this->velocity, this->position, this->lastPosition);
	this->lastPosition = this->position;

	this->deviceSoundEmitter->SetParameter(this->paramAddressVelocity, 0, &this->velocity);
}
