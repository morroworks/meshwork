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

#include "MwBoxGeometry.h"

#include "MwPlaneGeometry.h"
#include "MwMergeGeometry.h"

#include "..\..\..\Graphics\DeviceIndependent\MwDeviceIndependentMesh.h"

// Creates a box with the given number of segments, along the given vectors
// New mesh vertices are created with their position filled
// New mesh indices are created
MwBoxGeometry::MwBoxGeometry(MwDeviceMesh &result, int xSegments, int ySegments, int zSegments, MwVector3 &xAxis, MwVector3 &yAxis, MwVector3 &zAxis)
{
	this->CreateGeometry(result, xSegments, ySegments, zSegments, xAxis, yAxis, zAxis);
}


// Creates a box with the given number of segments
// New mesh vertices are created with their position filled
// New mesh indices are created
MwBoxGeometry::MwBoxGeometry(MwDeviceMesh &result, int xSegments, int ySegments, int zSegments)
{
	MwVector3 xAxis(1.0f, 0.0f, 0.0f), 
			  yAxis(0.0f, 1.0f, 0.0f),
			  zAxis(0.0f, 0.0f, 1.0f);
		
	this->CreateGeometry(result, xSegments, ySegments, zSegments, xAxis, yAxis, zAxis);
}

MwBoxGeometry::~MwBoxGeometry(void)
{
}

void MwBoxGeometry::CreateGeometry(MwDeviceMesh &result, int xSegments, int ySegments, int zSegments, MwVector3 &xAxis, MwVector3 &yAxis, MwVector3 &zAxis)
{
	MwDeviceIndependentMesh plane;
	MwMatrix transform, identity;
	MwVector3 x, y, up;

	MwMatrix::CreateIdentity(identity);

	// Top
	MwVector3::Scale(x, xAxis, 1.0f);
	MwVector3::Scale(y, zAxis, 1.0f);
	MwVector3::Scale(up, yAxis, 0.5f);
	MwPlaneGeometry(plane, xSegments, zSegments, x, y);
	MwMatrix::CreateTranslation(transform, up);
	MwMergeGeometry(result, result, identity, plane, transform);

	// Bottom
	MwVector3::Scale(x, xAxis, 1.0f);
	MwVector3::Scale(y, zAxis, -1.0f);
	MwVector3::Scale(up, yAxis, -0.5f);
	MwPlaneGeometry(plane, xSegments, zSegments, x, y);
	MwMatrix::CreateTranslation(transform, up);
	MwMergeGeometry(result, result, identity, plane, transform);

	// Back
	MwVector3::Scale(x, xAxis, 1.0f);
	MwVector3::Scale(y, yAxis, -1.0f);
	MwVector3::Scale(up, zAxis, 0.5f);
	MwPlaneGeometry(plane, xSegments, ySegments, x, y);
	MwMatrix::CreateTranslation(transform, up);
	MwMergeGeometry(result, result, identity, plane, transform);

	// Front
	MwVector3::Scale(x, xAxis, 1.0f);
	MwVector3::Scale(y, yAxis, 1.0f);
	MwVector3::Scale(up, zAxis, -0.5f);
	MwPlaneGeometry(plane, xSegments, ySegments, x, y);
	MwMatrix::CreateTranslation(transform, up);
	MwMergeGeometry(result, result, identity, plane, transform);

	// Right
	MwVector3::Scale(x, zAxis, 1.0f);
	MwVector3::Scale(y, yAxis, 1.0f);
	MwVector3::Scale(up, xAxis, 0.5f);
	MwPlaneGeometry(plane, zSegments, ySegments, x, y);
	MwMatrix::CreateTranslation(transform, up);
	MwMergeGeometry(result, result, identity, plane, transform);

	// Left
	MwVector3::Scale(x, zAxis, 1.0f);
	MwVector3::Scale(y, yAxis, -1.0f);
	MwVector3::Scale(up, xAxis, -0.5f);
	MwPlaneGeometry(plane, zSegments, ySegments, x, y);
	MwMatrix::CreateTranslation(transform, up);
	MwMergeGeometry(result, result, identity, plane, transform);
}