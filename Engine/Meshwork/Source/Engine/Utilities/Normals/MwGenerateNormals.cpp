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

#include "MwGenerateNormals.h"


MwGenerateNormals::MwGenerateNormals(MwDeviceMesh &result)
{
	MwVector3 dv1, dv2,
			  v0, v1, v2,
			  n;

	int numVertices = result.GetVertexCount();
	int numIndices = result.GetIndexCount();
	MwVector3 *normals = new MwVector3[numVertices];
    int i;

    for (i = 0; i < numVertices; i++)
    {
		normals[i].Set(0.0f);
    }

    for (i = 0; i < numIndices; i += 3)
    {
		int index0 = result.GetIndex(i);
		int index1 = result.GetIndex(i + 1);
		int index2 = result.GetIndex(i + 2);

		result.GetVertexPosition(index0, v0); 
		result.GetVertexPosition(index1, v1); 
		result.GetVertexPosition(index2, v2); 
        	
        MwVector3::Subtract(dv1, v1, v0);
        MwVector3::Subtract(dv2, v2, v0);

        MwVector3::Cross(n, dv2, dv1);
        MwVector3::Normalize(n, n);

		MwVector3::Add(normals[index0], normals[index0], n);
        MwVector3::Add(normals[index1], normals[index1], n);
        MwVector3::Add(normals[index2], normals[index2], n);
    }

    for (i = 0; i < numVertices; i++)
    {
        MwVector3::Normalize(v0, normals[i]);
        result.SetVertexNormal(i, v0);
    }

	delete[] normals;
}


MwGenerateNormals::~MwGenerateNormals(void)
{
}
