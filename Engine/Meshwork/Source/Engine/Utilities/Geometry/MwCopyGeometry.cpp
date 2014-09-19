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

#include "MwCopyGeometry.h"


// Copies the source mesh into the given ont
// Position, normal and texture coordinates are copied
// Indices are copied
MwCopyGeometry::MwCopyGeometry(MwDeviceMesh &result, MwDeviceMesh &source)
{
	if (&result == &source)
		return;

	int numVertices = source.GetVertexCount();
	result.CreateVertexBuffer(numVertices);

	MwVector3 position;
	MwVector3 normal;
	MwVector2 texCoords;

	for (int i = 0; i < numVertices; i++)
	{
		source.GetVertexPosition(i, position);
		source.GetVertexNormal(i, normal);
		source.GetVertexTexCoords(i, texCoords);

		result.SetVertexPosition(i, position);
		result.SetVertexNormal(i, normal);
		result.SetVertexTexCoords(i, texCoords);
	}


	int numIndices = source.GetIndexCount();
	result.CreateIndexBuffer(numIndices);

	for (int i = 0; i < numIndices; i++)
	{
		result.SetIndex(i, source.GetIndex(i));
	}
	 
}


MwCopyGeometry::~MwCopyGeometry(void)
{
}
