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

#include "MwBounds.h"

#include "MwMatrix.h"
#include "MwVector4.h"

#include "..\Utilities\MwMaths.h"

MwBounds::MwBounds(void)
{
}


MwBounds::~MwBounds(void)
{
}

bool MwBounds::InsideViewFrustum(MwMatrix &transform)
{
    MwVector4 plane;
	
	//Left Plane
    plane.x = transform._14 + transform._11;
    plane.y = transform._24 + transform._21;
    plane.z = transform._34 + transform._31;
    plane.w = transform._44 + transform._41;
    if (-MwMaths::PointToPlaneDistance(this->center, plane) > this->sphere)
        return false;

    //Right Plane
    plane.x = transform._14 - transform._11;
    plane.y = transform._24 - transform._21;
    plane.z = transform._34 - transform._31;
    plane.w = transform._44 - transform._41;
    if (-MwMaths::PointToPlaneDistance(this->center, plane) > this->sphere)
        return false;

    //Bottom Plane
    plane.x = transform._14 + transform._12;
    plane.y = transform._24 + transform._22;
    plane.z = transform._34 + transform._32;
    plane.w = transform._44 + transform._42;
    if (-MwMaths::PointToPlaneDistance(this->center, plane) > this->sphere)
        return false;

    //Top Plane
    plane.x = transform._14 - transform._12;
    plane.y = transform._24 - transform._22;
    plane.z = transform._34 - transform._32;
    plane.w = transform._44 - transform._42;
    if (-MwMaths::PointToPlaneDistance(this->center, plane) > this->sphere)
        return false;

    //Near Plane
    plane.x = transform._13;
    plane.y = transform._23;
    plane.z = transform._33;
    plane.w = transform._43;
    if (-MwMaths::PointToPlaneDistance(this->center, plane) > this->sphere)
        return false;

    //Far Plane
    plane.x = transform._14 - transform._13;
    plane.y = transform._24 - transform._23;
    plane.z = transform._34 - transform._33;
    plane.w = transform._44 - transform._43;
    if (-MwMaths::PointToPlaneDistance(this->center, plane) > this->sphere)
        return false;
        
    return true;
}
