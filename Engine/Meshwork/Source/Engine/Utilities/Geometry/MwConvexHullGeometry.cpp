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

#include "MwConvexHullGeometry.h"


// Creates triangle indices in the given mesh, based on the mesh's vertices, so that the resulting triangle geometry is a convex hull which contains all the vertices in its volume
// The mesh has to have the position of its vertices filled
// New mesh indices are created
MwConvexHullGeometry::MwConvexHullGeometry(MwDeviceMesh &result)
{
	int numVertices = result.GetVertexCount();
	if (numVertices < 3)
		return;

	int vertexIndex = 0;

	// Put a triangle
	this->indices.Add(vertexIndex++);
	this->indices.Add(vertexIndex++);
	this->indices.Add(vertexIndex++);

	int triangleIndex = 1;

	this->modifyIndices.SetSize(numVertices);
	for (int i = 0; i < this->modifyIndices.count; i++)
		this->modifyIndices[i] = 0;

	// Begin building convex hull
	while(vertexIndex < numVertices)
	{
		for (int triangleIndex = 0; triangleIndex < this->indices.count; triangleIndex += 3)
		{
			if (this->IsOutside(vertexIndex, triangleIndex))
			{
				this->modifyIndices[result.GetIndex(triangleIndex)]++;
				this->modifyIndices[result.GetIndex(triangleIndex)]++;
				this->modifyIndices[result.GetIndex(triangleIndex)]++;
			}
		}

		vertexIndex++;
	}
}


MwConvexHullGeometry::~MwConvexHullGeometry(void)
{
}

bool MwConvexHullGeometry::IsOutside(int vertexIndex, int triangleIndex)
{
	return true;
}
