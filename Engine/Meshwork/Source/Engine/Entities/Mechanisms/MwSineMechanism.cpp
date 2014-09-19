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

#include "MwSineMechanism.h"

#include "..\..\..\Tools\MwMath.h"

MwSineMechanism::MwSineMechanism(float min, float max, float time, bool loop)
	: MwBaseMechanism()
{
	this->typeId = MwSineMechanism::classId;

	this->parameter.SetFloat(0.0f);

    this->properties.Add(new MwProperty("Min", min));
    this->properties.Add(new MwProperty("Max", max));
    this->properties.Add(new MwProperty("Time", time));
    this->properties.Add(new MwProperty("Loop", loop));

    this->u = 0.0f;
}


MwSineMechanism::~MwSineMechanism(void)
{
}


bool MwSineMechanism::Process(float deltaTime)
{
    float min = *(float*)this->properties[0]->GetEffectiveParameter()->value;
    float max = *(float*)this->properties[1]->GetEffectiveParameter()->value;
    float sineTime = *(float*)this->properties[2]->GetEffectiveParameter()->value;
    bool loop = *(bool*)this->properties[3]->GetEffectiveParameter()->value;

    bool result = true;
    if (u > 1.0f)
	{
        if (loop)
            u -= (int)u;
        else
        {
            u = 1.0f;
            result = false;
        }
	}

	*(float*)this->parameter.value = min + (max - min) * MwMath::Abs(1.0f + MwMath::Sin(this->u * MwMath::Pi * 2.0f)) / 2.0f;

    this->u += deltaTime * (1.0f / sineTime);

    return result;
}