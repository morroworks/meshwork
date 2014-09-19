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

#include "MwScreenPickEvents.h"

#include "Meshwork.h"

MwScreenPickEvents::MwScreenPickEvents(Meshwork &meshwork)
	: MwTraceEvents(meshwork)
{
}

MwScreenPickEvents::~MwScreenPickEvents(void)
{
}

void MwScreenPickEvents::SetupScreenPick(int x, int y, int screenWidth, int screenHeight)
{
    float px = 2.0f * (float)x / (float)screenWidth - 1.0f;
    float py = 1.0f - 2.0f * (float)y / (float)screenHeight;
    this->rayPoint1 = MwVector3(px, py, -1.0f);
    this->rayPoint2 = MwVector3(px, py, 1.0f);
	this->intersectionDistance = MwMath::FloatMax;
	this->intersected = false;
}
	
void MwScreenPickEvents::OnMesh(MwTraceParameters &parameters)
{
	MwMatrix transform;
	MwVector4 origin4, direction4;
	MwVector3 origin, direction;
	MwIntersectionInfo intersectionInfo;

       
	MwMatrix::Multiply(transform, parameters.transformRef->matrix, parameters.cameraRef->viewProjection);
    
	//if (!parameters.meshRef->bounds.InsideViewFrustum(transform))
 //       return;

	MwMatrix::Invert(transform, transform);
    MwVector4::Transform(origin4, this->rayPoint1, transform);
    MwVector4::Transform(direction4, this->rayPoint2, transform);
    origin.x = origin4.x / origin4.w; 
    origin.y = origin4.y / origin4.w; 
    origin.z = origin4.z / origin4.w;
    direction.x = direction4.x / direction4.w;
    direction.y = direction4.y / direction4.w;
    direction.z = direction4.z / direction4.w;
    MwVector3::Subtract(direction, direction, origin);
    MwVector3::Normalize(direction, direction);
    if (parameters.meshRef->Intersection(origin, direction, intersectionInfo))
        if (intersectionInfo.distance < this->intersectionDistance)
        {
            this->entityInfo = parameters;
            this->intersectionInfo = intersectionInfo;
            this->intersectionDistance = intersectionInfo.distance;
			this->intersected = true;
        }
}

void MwScreenPickEvents::OnTransform(MwTraceParameters &parameters)
{
	parameters.transformRef->Process();
}