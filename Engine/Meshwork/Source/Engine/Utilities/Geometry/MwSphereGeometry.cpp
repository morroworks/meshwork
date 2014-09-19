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

#include "MwSphereGeometry.h"

#include "..\..\..\Tools\MwMath.h"

#include "..\..\..\Graphics\DeviceIndependent\MwDeviceIndependentMesh.h"

#include "MwIcosahedronGeometry.h"

// Creates a sphere (geosphere) with the given radius and number of subdivisions, starting from an icosahedron
// New mesh vertices are created with their position filled
// New mesh indices are created
MwSphereGeometry::MwSphereGeometry(MwDeviceMesh &result, float radius, int subDivisions)
{
	this->result = &result;
	this->radius = radius;

	MwDeviceIndependentMesh icosa;
	MwIcosahedronGeometry(icosa, radius);

	this->result->CreateIndexBuffer(icosa.GetIndexCount() * MwMath::Power(4, subDivisions));
	this->result->CreateVertexBuffer(this->result->GetIndexCount() / 6 + 2);
	
	this->currentVertexIndex = icosa.numVertices;
	this->currentIndex = 0;

	MwVector3 position;
	MwVector3 normal;
	MwVector2 texCoords;

	int numVertices = icosa.numVertices;
	for (int i = 0; i < numVertices; i++)
	{
		icosa.GetVertexPosition(i, position);
		icosa.GetVertexNormal(i, normal);
		icosa.GetVertexTexCoords(i, texCoords);

		this->result->SetVertexPosition(i, position);
		this->result->SetVertexNormal(i, normal);
		this->result->SetVertexTexCoords(i, texCoords);
	}


	int numTriangles = icosa.GetPrimitiveCount();
	int index = 0;
	for (int triangleIndex = 0; triangleIndex < numTriangles; triangleIndex++)
	{
		this->result->SetIndex(this->currentIndex++, icosa.GetIndex(index++));
		this->result->SetIndex(this->currentIndex++, icosa.GetIndex(index++));
		this->result->SetIndex(this->currentIndex++, icosa.GetIndex(index++));

		this->SubDivideTriangle(this->currentIndex - 3, subDivisions);
	}
}


MwSphereGeometry::~MwSphereGeometry(void)
{
}


void MwSphereGeometry::SubDivideTriangle(int triangleIndex, int subLevel)
{
	if (subLevel == 0)
		return;

	int i0 = this->result->GetIndex(triangleIndex);
	int i1 = this->result->GetIndex(triangleIndex + 1);
	int i2 = this->result->GetIndex(triangleIndex + 2);

	int s0 = this->GetEdgeSubIndex(i0, i1);
	int s1 = this->GetEdgeSubIndex(i1, i2);
	int s2 = this->GetEdgeSubIndex(i2, i0);

	this->result->SetIndex(triangleIndex, i0);
	this->result->SetIndex(triangleIndex + 1, s0);
	this->result->SetIndex(triangleIndex + 2, s2);
	this->SubDivideTriangle(triangleIndex, subLevel - 1);

	this->result->SetIndex(this->currentIndex++, i1);
	this->result->SetIndex(this->currentIndex++, s1);
	this->result->SetIndex(this->currentIndex++, s0);
	this->SubDivideTriangle(this->currentIndex - 3, subLevel - 1);

	this->result->SetIndex(this->currentIndex++, i2);
	this->result->SetIndex(this->currentIndex++, s2);
	this->result->SetIndex(this->currentIndex++, s1);
	this->SubDivideTriangle(this->currentIndex - 3, subLevel - 1);

	this->result->SetIndex(this->currentIndex++, s0);
	this->result->SetIndex(this->currentIndex++, s1);
	this->result->SetIndex(this->currentIndex++, s2);
	this->SubDivideTriangle(this->currentIndex - 3, subLevel - 1);
}

int MwSphereGeometry::GetEdgeSubIndex(int edgeIndex1, int edgeIndex2)
{
	// Look for existing subvertex
	for (int i = 0; i < this->edges.count; i++)
		if (((this->edges[i].index1 == edgeIndex1) && (this->edges[i].index2 == edgeIndex2)) ||
			((this->edges[i].index1 == edgeIndex2) && (this->edges[i].index2 == edgeIndex1)))
			return this->edges[i].subIndex;

	// Generate subvertex
	MwVector3 v1, v2, vsub;
	this->result->GetVertexPosition(edgeIndex1, v1);
	this->result->GetVertexPosition(edgeIndex2, v2);
	MwVector3::Subtract(vsub, v2, v1);
	MwVector3::Scale(vsub, vsub, 0.5f);
	MwVector3::Add(vsub, v1, vsub);
	MwVector3::SetLength(vsub, vsub, this->radius);
	this->result->SetVertexPosition(this->currentVertexIndex, vsub);

	// Add the edge's subvertex to the list
	MwEdge newEdge;
	newEdge.index1 = edgeIndex1;
	newEdge.index2 = edgeIndex2;
	newEdge.subIndex = this->currentVertexIndex;
	this->edges.Add(newEdge);

	this->currentVertexIndex++;

	return newEdge.subIndex;
}
