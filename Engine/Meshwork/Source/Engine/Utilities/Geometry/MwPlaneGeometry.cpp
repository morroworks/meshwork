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

#include "MwPlaneGeometry.h"


// Creates a plane with the given number of segments, along the given vectors
// New mesh vertices are created with their position filled
// New mesh indices are created
MwPlaneGeometry::MwPlaneGeometry(MwDeviceMesh &result, int xSegments, int ySegments, MwVector3 &xAxis, MwVector3 &yAxis)
{
	this->CreateGeometry(result, xSegments, ySegments, xAxis, yAxis);
}

// Creates a plane with the given number of segments
// New mesh vertices are created with their position filled
// New mesh indices are created
MwPlaneGeometry::MwPlaneGeometry(MwDeviceMesh &result, int xSegments, int ySegments)
{
	MwVector3 xAxis(1.0f, 0.0f, 0.0f);
	MwVector3 yAxis(0.0f, 1.0f, 0.0f);

	this->CreateGeometry(result, xSegments, ySegments, xAxis, yAxis);
}

MwPlaneGeometry::~MwPlaneGeometry(void)
{
}


void MwPlaneGeometry::CreateGeometry(MwDeviceMesh &result, int xSegments, int ySegments, MwVector3 &xAxis, MwVector3 &yAxis)
{
	result.CreateVertexBuffer((xSegments + 1) * (ySegments + 1));

	MwVector3 pos, xPos, yPos;
	MwVector2 texCoords;
	int index = 0;
	for (int y = 0; y <= ySegments; y++)
	{
		float v = y / (float)ySegments;
		MwVector3::Scale(yPos, yAxis, v - 0.5f);

		for (int x = 0; x <= xSegments; x++)
		{
			float u = x / (float)xSegments;
			MwVector3::Scale(xPos, xAxis, u - 0.5f);

			MwVector3::Add(pos, xPos, yPos);

			result.SetVertexTexCoords(index, MwVector2(u, v));
			result.SetVertexPosition(index++, pos);
		}
	}


	result.CreateIndexBuffer(xSegments * ySegments * 2 * 3);

	index = 0;
	for (int y = 0; y < ySegments; y++)
	{
		for (int x = 0; x < xSegments; x++)
		{
			int line0 = y * (xSegments + 1) + x;
			int line1 = (y + 1) * (xSegments + 1) + x;

			result.SetIndex(index++, line0);
			result.SetIndex(index++, line0 + 1);
			result.SetIndex(index++, line1);

			result.SetIndex(index++, line0 + 1);
			result.SetIndex(index++, line1 + 1);
			result.SetIndex(index++, line1);
		}
	}
}
