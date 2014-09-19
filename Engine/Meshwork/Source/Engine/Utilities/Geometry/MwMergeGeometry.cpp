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

#include "MwMergeGeometry.h"

#include "..\..\..\Graphics\DeviceIndependent\MwDeviceIndependentMesh.h"

#include "MwCopyGeometry.h"


// Merges two meshes into a new one, incorporating the given transformations to the source meshes
// If the resulting mesh is also used as a source, its original geometry will be put into the final result
// Position, normals and texture coordinates are copied
// Indices are copied
MwMergeGeometry::MwMergeGeometry(MwDeviceMesh &result, MwDeviceMesh &geometry1, MwMatrix &transform1, MwDeviceMesh &geometry2, MwMatrix &transform2)
{
	this->CreateGeometry(result, geometry1, transform1, geometry2, transform2);
}

// Merges two meshes into a new one
// If the resulting mesh is also used as a source, its original geometry will be put into the final result
// Position, normals and texture coordinates are copied
// Indices are copied
MwMergeGeometry::MwMergeGeometry(MwDeviceMesh &result, MwDeviceMesh &geometry1, MwDeviceMesh &geometry2)
{
	MwMatrix identity;
	MwMatrix::CreateIdentity(identity);

	this->CreateGeometry(result, geometry1, identity, geometry2, identity);
}


MwMergeGeometry::~MwMergeGeometry(void)
{
}

void MwMergeGeometry::CreateGeometry(MwDeviceMesh &result, MwDeviceMesh &geometry1, MwMatrix &transform1, MwDeviceMesh &geometry2, MwMatrix &transform2)
{
	MwDeviceMesh *finalResult;

	bool buffered = (&result == &geometry1) || (&result == &geometry2);
	if (buffered)
		finalResult = new MwDeviceIndependentMesh();
	else
		finalResult = &result;

	finalResult->CreateVertexBuffer(geometry1.GetVertexCount() + geometry2.GetVertexCount());

	MwVector3 position;
	MwVector3 normal;
	MwVector2 texCoords;

	int finalVertices = finalResult->GetVertexCount();
	for (int i = 0; i < finalVertices; i++)
	{
		int i2 = i - geometry1.GetVertexCount();
		MwDeviceMesh *source = i2 < 0 ? &geometry1 : &geometry2;
		int sourceIndex = i2 < 0 ? i : i2;
		MwMatrix *transform = i2 < 0 ? &transform1 : &transform2;

		source->GetVertexPosition(sourceIndex, position);
		source->GetVertexNormal(sourceIndex, normal);
		source->GetVertexTexCoords(sourceIndex, texCoords);

		MwVector3::Transform(position, position, *transform);
		MwVector3::TransformNormal(normal, normal, *transform);

		finalResult->SetVertexPosition(i, position);
		finalResult->SetVertexNormal(i, normal);
		finalResult->SetVertexTexCoords(i, texCoords);
	}


	finalResult->CreateIndexBuffer(geometry1.GetIndexCount() + geometry2.GetIndexCount());

	int finalIndices = finalResult->GetIndexCount();
	for (int i = 0; i < finalIndices; i++)
	{
		int i2 = i - geometry1.GetIndexCount();
		MwDeviceMesh *source = i2 < 0 ? &geometry1 : &geometry2;
		int sourceIndex = i2 < 0 ? i : i2;
		int destIndex = i2 < 0 ? source->GetIndex(sourceIndex) : source->GetIndex(sourceIndex) + geometry1.GetVertexCount();

		finalResult->SetIndex(i, destIndex);
	}

	if (buffered)
	{
		MwCopyGeometry(result, *finalResult);
		delete finalResult;
	}
};