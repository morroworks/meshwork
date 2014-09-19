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

#include "MwRayIntersectionEvents.h"


MwRayIntersectionEvents::MwRayIntersectionEvents(Meshwork &meshwork)
	: MwTraceEvents(meshwork)
{
}


MwRayIntersectionEvents::~MwRayIntersectionEvents(void)
{
}

void MwRayIntersectionEvents::SetupRay(MwVector3 &rayPoint1, MwVector3 &rayPoint2)
{
    MwVector3::Copy(this->rayPoint, rayPoint1);
    MwVector3::Subtract(rayVector, rayPoint2, rayPoint1);
    MwVector3::Normalize(rayVector, rayVector);
	intersectionDistance = MwMath::FloatMax;
    intersected = false;
}
    
void MwRayIntersectionEvents::OnMesh(MwTraceParameters &parameters)
{
	MwMatrix transform;
	MwVector3 point1, point2;
    MwIntersectionInfo intersectionInfo;

	MwMatrix::Invert(transform, parameters.transformRef->matrix);
    MwVector3::Transform(point1, this->rayPoint, transform);
    MwVector3::TransformNormal(point2, this->rayVector, transform);
    if (parameters.meshRef->Intersection(point1, point2, intersectionInfo))
        if (intersectionInfo.distance < this->intersectionDistance)
        {
            traceResult = parameters;
            this->intersectionInfo = intersectionInfo;
            intersectionDistance = intersectionInfo.distance;
            intersected = true;
        }
}