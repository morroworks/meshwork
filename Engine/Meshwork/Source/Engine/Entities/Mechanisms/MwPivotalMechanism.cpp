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

#include "MwPivotalMechanism.h"

#include "..\..\Primitive\MwVector3.h"

#include "..\..\Entities\Transform\MwTransform.h"

MwPivotalMechanism::MwPivotalMechanism(void)
	: MwBaseMechanism()
{
	this->typeId = MwPivotalMechanism::classId;

	this->parameter.SetType(MwParameterType_None);

    this->properties.Add(new MwProperty("Loop", MwParameterType_ReferenceTransform, 0));
    this->properties.Add(new MwProperty("Target Transform", MwParameterType_ReferenceTransform, 0));

	this->properties.Add(new MwProperty("Environment Resistance", 0.5f));
    this->properties.Add(new MwProperty("Gravity Strength", 0.0f));

    this->properties.Add(new MwProperty("Connection Length", 50.0f));
    this->properties.Add(new MwProperty("Elasticity Length", 100.0f));
    this->properties.Add(new MwProperty("Connection Solid", false));

    this->properties.Add(new MwProperty("Target Mass", 5.0f));

	this->gravityVector = MwVector3(0.0f, -1.0f, 0.0f);
}


MwPivotalMechanism::~MwPivotalMechanism(void)
{
}


bool MwPivotalMechanism::Process(float deltaTime)
{
	MwVector3 pivot, moveVector, newTargetPos;

	MwTransform *transform = (MwTransform*)properties[0]->value,
                *target = (MwTransform*)properties[1]->value;
    float environmentResistance = *(float*)properties[2]->value,
            gravityStrength = *(float*)properties[3]->value,
            connectionLength = *(float*)properties[4]->value,
            elasticityLength = *(float*)properties[5]->value;
    bool connectionSolid = *(bool*)properties[6]->value;
    float targetMass = *(float*)properties[7]->value;

	MwMatrix::GetTranslation(pivot, transform->matrix);
    MwVector3::Add(newTargetPos, this->targetPos, this->targetMoveVector);
    MwVector3::Subtract(moveVector, pivot, newTargetPos);
    float distance = moveVector.GetLength();
        
    float vectorLength = distance - connectionLength;

    if (distance > 0.0f)
        MwVector3::Scale(moveVector, moveVector, 1.0f / distance);

    if ((vectorLength > 0.0f) || connectionSolid)
    {
        MwVector3::Scale(moveVector, moveVector, vectorLength / elasticityLength);
        MwVector3::Add(targetMoveVector, targetMoveVector, moveVector);
    }

    MwVector3::Scale(gravityVector, gravityVector, gravityStrength);
    MwVector3::Add(targetMoveVector, targetMoveVector, gravityVector);

    MwVector3::Scale(targetMoveVector, targetMoveVector, 1.0f - environmentResistance / targetMass);

    MwVector3::Add(targetPos, targetPos, targetMoveVector);

	MwMatrix::SetTranslation(target->matrix, targetPos);

    return true;
}