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

#include "MwTangentsGenerator.h"


MwTangentsGenerator::MwTangentsGenerator(MwDeviceMesh &result)
{
	MwVector3 dv1, dv2,
			  v0, v1, v2;
	MwVector2 dt1, dt2,
			  t0, t1, t2;

	int numVertices = result.GetVertexCount();
	int numIndices = result.GetIndexCount();
	MwVector3 *tangents = new MwVector3[numVertices];
	MwVector3 *biTangents = new MwVector3[numVertices];
    int i;

    for (i = 0; i < numVertices; i++)
    {
		tangents[i].Set(0.0f);
		biTangents[i].Set(0.0f);
    }

    for (i = 0; i < numIndices; i += 3)
    {
		int index0 = result.GetIndex(i);
		int index1 = result.GetIndex(i + 1);
		int index2 = result.GetIndex(i + 2);

		// Calculate triangle positional delta vectors
		result.GetVertexPosition(index0, v0); 
		result.GetVertexPosition(index1, v1); 
		result.GetVertexPosition(index2, v2); 
        	
        MwVector3::Subtract(dv1, v1, v0);
        MwVector3::Subtract(dv2, v2, v0);

		// Calculate triangle texture coordinates delta vectors
		result.GetVertexTexCoords(index0, t0); 
		result.GetVertexTexCoords(index1, t1); 
		result.GetVertexTexCoords(index2, t2); 
        	
        MwVector2::Subtract(dt1, t1, t0);
        MwVector2::Subtract(dt2, t2, t0);




  //      MwVector3::Cross(u, a, b);
  //      MwVector3::Normalize(u, u);

		//MwVector3::Add(normalBuffer[index0], normalBuffer[index0], u);
  //      MwVector3::Add(normalBuffer[index1], normalBuffer[index1], u);
  //      MwVector3::Add(normalBuffer[index2], normalBuffer[index2], u);
    }

    for (i = 0; i < numVertices; i++)
    {
        //MwVector3::Normalize(v0, normalBuffer[i]);
        //result.SetVertexNormal(i, v0);
    }

	delete[] tangents;
	delete[] biTangents;
}


MwTangentsGenerator::~MwTangentsGenerator(void)
{
}
