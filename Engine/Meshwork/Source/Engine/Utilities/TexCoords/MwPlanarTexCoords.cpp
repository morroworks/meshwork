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

#include "MwPlanarTexCoords.h"

#include "..\MwMaths.h"

MwPlanarTexCoords::MwPlanarTexCoords(MwDeviceMesh &result, MwVector3 &planeX, MwVector3 &planeY)
{
	MwVector2 centerCorrection(0.5f, 0.5f);

	int numVertices = result.GetVertexCount();
	for (int i = 0; i < numVertices; i++)
	{
		MwVector3 vPos;
		result.GetVertexPosition(i, vPos);

		MwVector2 texCoords;
		MwMaths::GetBarycentricCoordinates(texCoords, vPos, planeX, planeY);
				
		MwVector2::Add(texCoords, texCoords, centerCorrection);
		result.SetVertexTexCoords(i, texCoords);
	}
}


MwPlanarTexCoords::~MwPlanarTexCoords(void)
{
}
