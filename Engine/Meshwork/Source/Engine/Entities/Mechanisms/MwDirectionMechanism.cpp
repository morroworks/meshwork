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

#include "MwDirectionMechanism.h"

#include "..\..\..\Tools\MwMath.h"

#include "..\..\Primitive\MwMatrix.h"
#include "..\..\Primitive\MwVector3.h"

#include "..\..\Entities\Transform\MwTransform.h"

MwDirectionMechanism::MwDirectionMechanism(void)
	: MwBaseMechanism()
{
	this->typeId = MwDirectionMechanism::classId;

	this->parameter.SetType(MwParameterType_None);

	this->properties.Add(new MwProperty("Transform", MwParameterType_ReferenceTransform, 0));
    this->properties.Add(new MwProperty("Target Transform", MwParameterType_ReferenceTransform, 0));

    this->properties.Add(new MwProperty("Inertness", 0.1f));
}


MwDirectionMechanism::~MwDirectionMechanism(void)
{
}

bool MwDirectionMechanism::Process(float deltaTime)
{
	MwVector3 currentPosition, targetPosition, targetVector,
			  spherical, newSpherical;
    
	MwMatrix azimuth, elevation;

	MwTransform *transform = (MwTransform*)this->properties[0]->value,
                *target = (MwTransform*)this->properties[1]->value;
    float inertness = *(float*)properties[2]->value;

    MwMatrix::GetTranslation(currentPosition, transform->matrix);
	MwMatrix::GetTranslation(targetPosition, target->matrix);
    MwVector3::Subtract(targetVector, currentPosition, targetPosition);
    MwVector3::CartesianToSphere(spherical, targetVector);
    if (inertness == 0)
        MwVector3::Copy(newSpherical, spherical);
    else
        MwVector3::LerpSherical(newSpherical, this->lastSpherical, spherical, MwMath::Min(deltaTime / inertness, 1.0f));

    MwVector3::Copy(this->lastSpherical, newSpherical);

    MwMatrix::CreateRotationZ(azimuth, lastSpherical.y);
    MwMatrix::CreateRotationY(elevation, -lastSpherical.x);
    MwMatrix::Multiply(azimuth, azimuth, elevation);
    MwMatrix::Multiply(transform->matrix, azimuth, transform->matrix);

    return true;
}