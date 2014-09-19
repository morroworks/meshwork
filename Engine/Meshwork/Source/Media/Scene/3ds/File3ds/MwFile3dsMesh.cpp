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

#include "MwFile3dsMesh.h"

MwFile3dsMesh::MwFile3dsMesh(void)
{
	this->objectType = MwFile3dsObjectType_Mesh;
	
	localCoordSystem._11 = 1.0f;
	localCoordSystem._12 = 0.0f;
	localCoordSystem._13 = 0.0f;
	localCoordSystem._14 = 0.0f;
	localCoordSystem._21 = 0.0f;
	localCoordSystem._22 = 1.0f;
	localCoordSystem._23 = 0.0f;
	localCoordSystem._24 = 0.0f;
	localCoordSystem._31 = 0.0f;
	localCoordSystem._32 = 0.0f;
	localCoordSystem._33 = 1.0f;
	localCoordSystem._34 = 0.0f;
	localCoordSystem._41 = 0.0f;
	localCoordSystem._42 = 0.0f;
	localCoordSystem._43 = 0.0f;
	localCoordSystem._44 = 1.0f;

	this->vertices = 0;
	this->faces = 0;

	this->numVertices = 0;
	this->numFaces = 0;
}


MwFile3dsMesh::~MwFile3dsMesh(void)
{
	if (this->vertices != 0)
		delete this->vertices;

	if (this->faces != 0)
		delete this->faces;
}

void MwFile3dsMesh::InverseTransformation()
{
    float idet = 1.0f / (this->localCoordSystem._11 * this->localCoordSystem._22 * this->localCoordSystem._33 +
						 this->localCoordSystem._12 * this->localCoordSystem._23 * this->localCoordSystem._31 +
						 this->localCoordSystem._13 * this->localCoordSystem._21 * this->localCoordSystem._32 -
						 this->localCoordSystem._11 * this->localCoordSystem._23 * this->localCoordSystem._32 -
						 this->localCoordSystem._12 * this->localCoordSystem._21 * this->localCoordSystem._33 -
						 this->localCoordSystem._13 * this->localCoordSystem._22 * this->localCoordSystem._31);

    MwFile3dsObjectTransformation inv;
    inv._11 = idet * (this->localCoordSystem._22 * this->localCoordSystem._33 - this->localCoordSystem._23 * this->localCoordSystem._32);
    inv._12 = idet * (this->localCoordSystem._13 * this->localCoordSystem._32 - this->localCoordSystem._12 * this->localCoordSystem._33);
    inv._13 = idet * (this->localCoordSystem._12 * this->localCoordSystem._23 - this->localCoordSystem._13 * this->localCoordSystem._22);
    inv._21 = idet * (this->localCoordSystem._23 * this->localCoordSystem._31 - this->localCoordSystem._21 * this->localCoordSystem._33);
    inv._22 = idet * (this->localCoordSystem._11 * this->localCoordSystem._33 - this->localCoordSystem._13 * this->localCoordSystem._31);
    inv._23 = idet * (this->localCoordSystem._13 * this->localCoordSystem._21 - this->localCoordSystem._11 * this->localCoordSystem._23);
    inv._31 = idet * (this->localCoordSystem._21 * this->localCoordSystem._32 - this->localCoordSystem._22 * this->localCoordSystem._31);
    inv._32 = idet * (this->localCoordSystem._12 * this->localCoordSystem._31 - this->localCoordSystem._11 * this->localCoordSystem._32);
    inv._33 = idet * (this->localCoordSystem._11 * this->localCoordSystem._22 - this->localCoordSystem._12 * this->localCoordSystem._21);

    for (int i = 0; i < this->numVertices; i++)
    {
		float x = this->vertices[i].x - this->localCoordSystem._41;
		float y = this->vertices[i].y - this->localCoordSystem._42;
		float z = this->vertices[i].z - this->localCoordSystem._43;

		this->vertices[i].x = x * inv._11 +
							  y * inv._21 +
						      z * inv._31;
        this->vertices[i].y = x * inv._12 +
                              y * inv._22 +
                              z * inv._32;
        this->vertices[i].z = x * inv._13 +
                              y * inv._23 +
                              z * inv._33;
    }
}