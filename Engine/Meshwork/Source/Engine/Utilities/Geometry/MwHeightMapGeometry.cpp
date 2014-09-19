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

#include "MwHeightMapGeometry.h"

#include "..\Normals\MwGenerateNormals.h"

// Performs a height map modification to the given mesh, based on its normals and the given map
// The given mesh must have vertices with their position and normal set
// The position of the mesh's vertices is modified
// TODO: consider different pixel formats!
MwHeightMapGeometry::MwHeightMapGeometry(MwDeviceMesh &result, MwImage &map, float scale)
{
	int numVertices = result.GetVertexCount();
	for (int i = 0; i < numVertices; i++)
	{
		MwVector3 position, normal;
		MwVector2 texCoords;

		result.GetVertexPosition(i, position);
		result.GetVertexNormal(i, normal);
		result.GetVertexTexCoords(i, texCoords);

		int color = map.GetSample(texCoords.x, texCoords.y, 0);
		unsigned char *argb = (unsigned char*)&color;
		float heightFactor = (argb[0] + argb[1] + argb[2] + argb[3]) / (float)(0xff * 4);

		MwVector3::Scale(normal, normal, scale * heightFactor);
		MwVector3::Add(position, position, normal);

		result.SetVertexPosition(i, position);
	}

}


MwHeightMapGeometry::~MwHeightMapGeometry(void)
{
}
