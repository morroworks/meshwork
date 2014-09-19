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

#include "MwLinearMechanism.h"


MwLinearMechanism::MwLinearMechanism(float min, float max, float speed, bool loop)
	: MwBaseMechanism()
{
	this->typeId = MwLinearMechanism::classId;

	this->parameter.SetFloat(min);

	properties.Add(new MwProperty("Min", min));
    properties.Add(new MwProperty("Max", max));
    properties.Add(new MwProperty("Speed", speed));
    properties.Add(new MwProperty("Loop", loop));
    //properties.Add(new MwProperty("Oscilate", oscilate));
}


MwLinearMechanism::~MwLinearMechanism(void)
{
}

bool MwLinearMechanism::Process(float deltaTime)
{
	float min = *(float*)this->properties[MwLinearMechanism::propertyIndex_Min]->GetEffectiveParameter()->value;
	float max = *(float*)this->properties[MwLinearMechanism::propertyIndex_Max]->GetEffectiveParameter()->value;
	float speed = *(float*)this->properties[MwLinearMechanism::propertyIndex_Speed]->GetEffectiveParameter()->value;
    bool loop = *(bool*)this->properties[MwLinearMechanism::propertyIndex_Loop]->GetEffectiveParameter()->value;
	//bool oscilate = *(bool*)this->properties[MwLinearMechanism::propertyIndex_Oscilate]->GetEffectiveParameter()->value;

    bool result = true;
    float newValue = *(float*)this->parameter.value + deltaTime * speed;

    if (newValue >= max)
        if (loop)
            newValue = min + newValue - max;
        else
        {
            newValue = max;
            result = false;
        }

    if (newValue < min)
        if (loop)
            newValue = max - (min - newValue);
        else
        {
            newValue = min;
            result = false;
        }

    *(float*)parameter.value = newValue;
    return result;
}