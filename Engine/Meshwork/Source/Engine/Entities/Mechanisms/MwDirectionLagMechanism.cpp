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

#include "MwDirectionLagMechanism.h"

#include "..\..\..\Tools\MwMath.h"

#include "..\..\Primitive\MwMatrix.h"
#include "..\..\Primitive\MwVector3.h"

#include "..\..\Entities\Transform\MwTransform.h"

MwDirectionLagMechanism::MwDirectionLagMechanism(void)
	: MwBaseMechanism()
{
	this->typeId = MwDirectionLagMechanism::classId;

	this->parameter.SetType(MwParameterType_None);

	this->properties.Add(new MwProperty("Transform", MwParameterType_ReferenceTransform, 0));
    this->properties.Add(new MwProperty("Target Transform", MwParameterType_ReferenceTransform, 0));

	this->properties.Add(new MwProperty("Inertness", 0.1f));
    this->properties.Add(new MwProperty("Min Angle", 0.1f));
}


MwDirectionLagMechanism::~MwDirectionLagMechanism(void)
{
}

bool MwDirectionLagMechanism::Process(float deltaTime)
{
	MwVector3 currentPosition, targetPosition, targetVector,
			  spherical, newSpherical;
    
	MwMatrix azimuth, elevation;

	MwTransform *transform = (MwTransform*)this->properties[0]->value,
                *target = (MwTransform*)this->properties[1]->value;
    float inertness = *(float*)this->properties[2]->value;
    float minAngle = *(float*)this->properties[3]->value;

    MwMatrix::GetTranslation(currentPosition, transform->matrix);
	MwMatrix::GetTranslation(targetPosition, target->matrix);
    MwVector3::Subtract(targetVector, currentPosition, targetPosition);
    MwVector3::CartesianToSphere(spherical, targetVector);
    if (inertness == 0)
        MwVector3::Copy(newSpherical, spherical);
    else
    {
        float transitionLength = MwMath::Sqrt(spherical.x * spherical.x + spherical.y * spherical.y);
        if (transitionLength < minAngle)
            MwVector3::LerpSherical(newSpherical, lastSpherical, spherical, MwMath::Min(deltaTime / inertness, 1.0f));
        else
            // TODO: What is this "else" for?
			// Well, it seems to be here for, yet unimplemented, handling maximum distance
			MwVector3::LerpSherical(newSpherical, lastSpherical, spherical, MwMath::Min(deltaTime / inertness, 1.0f));
    }

    MwVector3::Copy(lastSpherical, newSpherical);

    MwMatrix::CreateRotationZ(azimuth, lastSpherical.y);
    MwMatrix::CreateRotationY(elevation, -lastSpherical.x);
    MwMatrix::Multiply(azimuth, azimuth, elevation);
    MwMatrix::Multiply(transform->matrix, azimuth, transform->matrix);

    return true;
}