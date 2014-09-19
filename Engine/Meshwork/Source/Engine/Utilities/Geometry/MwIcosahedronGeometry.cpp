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

#include "MwIcosahedronGeometry.h"

#include "..\..\..\Tools\MwMath.h"

// Creates an icosahedron with the given radius
// New mesh vertices are created with their position filled
// New mesh indices are created
MwIcosahedronGeometry::MwIcosahedronGeometry(MwDeviceMesh &result, float radius)
{
	// Generate icosahedron as from the vertices of three concentric, mutually orthogonal golden rectangles
	float k = radius / MwMath::Sqrt(1.0f * 1.0f + MwMath::Phi * MwMath::Phi);
	float w = MwMath::Phi * k;
	float h = 1.0f * k;

	result.CreateVertexBuffer(12);

	result.SetVertexPosition(0, MwVector3(-h,	0.0f,	w));
	result.SetVertexPosition(1, MwVector3(h,	0.0f,	w));
	result.SetVertexPosition(2, MwVector3(-h,	0.0f,	-w));
	result.SetVertexPosition(3, MwVector3(h,	0.0f,	-w));
	result.SetVertexPosition(4, MwVector3(0.0f,	w,	h));
	result.SetVertexPosition(5, MwVector3(0.0f,	w,	-h));
	result.SetVertexPosition(6, MwVector3(0.0f,	-w,	h));
	result.SetVertexPosition(7, MwVector3(0.0f,	-w,	-h));
	result.SetVertexPosition(8, MwVector3(w,	h,	0.0f));
	result.SetVertexPosition(9, MwVector3(-w,	h,	0.0f));
	result.SetVertexPosition(10, MwVector3(w,	-h,	0.0f));
	result.SetVertexPosition(11, MwVector3(-w,	-h,	0.0f));

	result.CreateIndexBuffer(20 * 3);

	result.SetIndex(0, 0);
	result.SetIndex(1, 4);
	result.SetIndex(2, 1);
	result.SetIndex(3, 0);
	result.SetIndex(4, 9);
	result.SetIndex(5, 4);
	result.SetIndex(6, 9);
	result.SetIndex(7, 5);
	result.SetIndex(8, 4);
	result.SetIndex(9, 4);
	result.SetIndex(10, 5);
	result.SetIndex(11, 8);
	result.SetIndex(12, 4);
	result.SetIndex(13, 8);
	result.SetIndex(14, 1);
	result.SetIndex(15, 8);
	result.SetIndex(16, 10);
	result.SetIndex(17, 1);
	result.SetIndex(18, 8);
	result.SetIndex(19, 3);
	result.SetIndex(20, 10);
	result.SetIndex(21, 5);
	result.SetIndex(22, 3);
	result.SetIndex(23, 8);
	result.SetIndex(24, 5);
	result.SetIndex(25, 2);
	result.SetIndex(26, 3);
	result.SetIndex(27, 2);
	result.SetIndex(28, 7);
	result.SetIndex(29, 3);
	result.SetIndex(30, 7);
	result.SetIndex(31, 10);
	result.SetIndex(32, 3);
	result.SetIndex(33, 7);
	result.SetIndex(34, 6);
	result.SetIndex(35, 10);
	result.SetIndex(36, 7);
	result.SetIndex(37, 11);
	result.SetIndex(38, 6);
	result.SetIndex(39, 11);
	result.SetIndex(40, 0);
	result.SetIndex(41, 6);
	result.SetIndex(42, 0);
	result.SetIndex(43, 1);
	result.SetIndex(44, 6);
	result.SetIndex(45, 6);
	result.SetIndex(46, 1);
	result.SetIndex(47, 10);
	result.SetIndex(48, 9);
	result.SetIndex(49, 0);
	result.SetIndex(50, 11);
	result.SetIndex(51, 9);
	result.SetIndex(52, 11);
	result.SetIndex(53, 2);
	result.SetIndex(54, 9);
	result.SetIndex(55, 2);
	result.SetIndex(56, 5);
	result.SetIndex(57, 7);
	result.SetIndex(58, 2);
	result.SetIndex(59, 11);
}


MwIcosahedronGeometry::~MwIcosahedronGeometry(void)
{
}
