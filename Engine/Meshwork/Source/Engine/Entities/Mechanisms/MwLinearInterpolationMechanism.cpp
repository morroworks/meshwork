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

#include "MwLinearInterpolationMechanism.h"


MwLinearInterpolationMechanism::MwLinearInterpolationMechanism(float min, float max, float argument)
{
	this->typeId = MwLinearInterpolationMechanism::classId;

	this->parameter.SetFloat(min);

	properties.Add(new MwProperty("Min", min));
    properties.Add(new MwProperty("Max", max));
    properties.Add(new MwProperty("Argument", argument));
}


MwLinearInterpolationMechanism::~MwLinearInterpolationMechanism(void)
{
}

bool MwLinearInterpolationMechanism::Process(float deltaTime)
{
    float min = *(float*)this->properties[0]->GetEffectiveParameter()->value;
    float max = *(float*)this->properties[1]->GetEffectiveParameter()->value;
    float argument = *(float*)this->properties[2]->GetEffectiveParameter()->value;

    *(float*)parameter.value = min + (max - min) * argument;

	return true;
}
