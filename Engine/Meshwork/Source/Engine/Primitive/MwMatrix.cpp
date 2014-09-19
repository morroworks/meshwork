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

#include "MwMatrix.h"

#include "..\..\Tools\MwMath.h"

#include "..\Utilities\MwMaths.h"

#include "MwVector3.h"

MwMatrix::MwMatrix(void)
{
	MwMatrix::CreateIdentity(*this);
}

MwMatrix::MwMatrix(MwMatrix &source)
{
	MwMatrix::Copy(*this, source);
}


MwMatrix::~MwMatrix(void)
{
}

float MwMatrix::GetDeterminant()
{
    return this->_11 * this->_22 * this->_33 * this->_44 +
		   this->_11 * this->_23 * this->_34 * this->_42 +
		   this->_11 * this->_24 * this->_32 * this->_43 +

		   this->_12 * this->_21 * this->_34 * this->_43 +
		   this->_12 * this->_23 * this->_31 * this->_44 +
		   this->_12 * this->_24 * this->_33 * this->_41 +

		   this->_13 * this->_21 * this->_32 * this->_44 +
		   this->_13 * this->_22 * this->_34 * this->_41 +
		   this->_13 * this->_24 * this->_31 * this->_42 +

		   this->_14 * this->_21 * this->_33 * this->_42 +
		   this->_14 * this->_22 * this->_31 * this->_43 +
		   this->_14 * this->_23 * this->_32 * this->_41 -

		   this->_11 * this->_22 * this->_34 * this->_43 -
		   this->_11 * this->_23 * this->_32 * this->_44 -
		   this->_11 * this->_24 * this->_33 * this->_42 -

		   this->_12 * this->_21 * this->_33 * this->_44 -
		   this->_12 * this->_23 * this->_34 * this->_41 -
		   this->_12 * this->_24 * this->_31 * this->_43 -

		   this->_13 * this->_21 * this->_34 * this->_42 -
		   this->_13 * this->_22 * this->_31 * this->_44 -
		   this->_13 * this->_24 * this->_32 * this->_41 -

		   this->_14 * this->_21 * this->_32 * this->_43 -
		   this->_14 * this->_22 * this->_33 * this->_41 -
		   this->_14 * this->_23 * this->_31 * this->_42;
}



// Static Methods

void MwMatrix::Copy(MwMatrix &result, MwMatrix &source)
{
	result._11 = source._11;
	result._12 = source._12;
	result._13 = source._13;
	result._14 = source._14;
	result._21 = source._21;
	result._22 = source._22;
	result._23 = source._23;
	result._24 = source._24;
	result._31 = source._31;
	result._32 = source._32;
	result._33 = source._33;
	result._34 = source._34;
	result._41 = source._41;
	result._42 = source._42;
	result._43 = source._43;
	result._44 = source._44;
}
	
void MwMatrix::CreateIdentity(MwMatrix &result)
{
    result._11 = 1.0f;
    result._12 = 0.0f;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = 1.0f;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = 0.0f;
    result._33 = 1.0f;
    result._34 = 0.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}
	
void MwMatrix::CreateRotationX(MwMatrix &result, float phi)
{
    float SinPhi = MwMath::Sin(phi);
    float CosPhi = MwMath::Cos(phi);

    result._11 = 1.0f;
    result._12 = 0.0f;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = CosPhi;
    result._23 = SinPhi;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = -SinPhi;
    result._33 = CosPhi;
    result._34 = 0.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}

void MwMatrix::CreateRotationY(MwMatrix &result, float phi)
{
    float SinPhi = MwMath::Sin(phi);
    float CosPhi = MwMath::Cos(phi);

    result._11 = CosPhi;
    result._12 = 0.0f;
    result._13 = -SinPhi;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = 1.0f;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = SinPhi;
    result._32 = 0.0f;
    result._33 = CosPhi;
    result._34 = 0.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}

void MwMatrix::CreateRotationZ(MwMatrix &result, float phi)
{
    float SinPhi = MwMath::Sin(phi);
    float CosPhi = MwMath::Cos(phi);

    result._11 = CosPhi;
    result._12 = SinPhi;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = -SinPhi;
    result._22 = CosPhi;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = 0.0f;
    result._33 = 1.0f;
    result._34 = 0.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}	

void MwMatrix::CreateRotationAxis(MwMatrix &result, float x, float y, float z, float phi)
{
	float SinPhi = MwMath::Sin(phi);
    float CosPhi = MwMath::Cos(phi);
    float InvCosPhi = 1 - CosPhi;
    float SinPhiX = SinPhi * x;
    float SinPhiY = SinPhi * y;
    float SinPhiZ = SinPhi * z;
    float InvCosPhiXY = InvCosPhi * x * y;
    float InvCosPhiXZ = InvCosPhi * x * z;
    float InvCosPhiYZ = InvCosPhi * y * z;

    result._11 = CosPhi + InvCosPhi * x * x;
    result._12 = InvCosPhiXY - SinPhiZ;
    result._13 = InvCosPhiXZ + SinPhiY;
    result._14 = 0.0f;
    result._21 = InvCosPhiXY + SinPhiZ;
    result._22 = CosPhi + InvCosPhi * y * y;
    result._23 = InvCosPhiYZ - SinPhiX;
    result._24 = 0.0f;
    result._31 = InvCosPhiXZ - SinPhiY;
    result._32 = InvCosPhiYZ + SinPhiX;
    result._33 = CosPhi + InvCosPhi * z * z;
    result._34 = 0.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}

void MwMatrix::CreateRotationAxis(MwMatrix &result, MwVector3 &axis, float phi)
{
	MwMatrix::CreateRotationAxis(result, axis.x, axis.y, axis.z, phi);
}

void MwMatrix::CreateTranslation(MwMatrix &result, float x, float y, float z)
{
    result._11 = 1.0f;
    result._12 = 0.0f;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = 1.0f;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = 0.0f;
    result._33 = 1.0f;
    result._34 = 0.0f;
    result._41 = x;
    result._42 = y;
    result._43 = z;
    result._44 = 1.0f;
}

void MwMatrix::CreateTranslation(MwMatrix &result, MwVector3 &translation)
{
    MwMatrix::CreateTranslation(result, translation.x, translation.y, translation.z);
}

void MwMatrix::CreateScale(MwMatrix &result, float x, float y, float z)
{
    result._11 = x;
    result._12 = 0.0f;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = y;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = 0.0f;
    result._33 = z;
    result._34 = 0.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}

void MwMatrix::CreateScale(MwMatrix &result, MwVector3 &scaling)
{
    MwMatrix::CreateScale(result, scaling.x, scaling.y, scaling.z);
}

void MwMatrix::CreateLookAt(MwMatrix &result, MwVector3 &position, MwVector3 &lookAt, MwVector3 &up)
{
	MwVector3 xAxis, yAxis, zAxis;

	MwVector3::Subtract(zAxis, position, lookAt);
	MwVector3::Normalize(zAxis, zAxis);
    MwVector3::Cross(xAxis, up, zAxis);
	MwVector3::Normalize(xAxis, xAxis);
    MwVector3::Cross(yAxis, zAxis, xAxis);

    result._11 = xAxis.x;
    result._12 = yAxis.x;
    result._13 = zAxis.x;
    result._14 = 0.0f;
    result._21 = xAxis.y;
    result._22 = yAxis.y;
    result._23 = zAxis.y;
    result._24 = 0.0f;
    result._31 = xAxis.z;
    result._32 = yAxis.z;
    result._33 = zAxis.z;
    result._34 = 0.0f;
    result._41 = -MwVector3::Dot(xAxis, position);
    result._42 = -MwVector3::Dot(yAxis, position);
    result._43 = -MwVector3::Dot(zAxis, position);
    result._44 = 1.0f;
}

void MwMatrix::CreatePerspectiveFieldOfView(MwMatrix &result, float fov, float aspect, float zn, float zf)
{
    float f = 1.0f / MwMath::Tan(fov / 2.0f);
    float dz = zn - zf;

    result._11 = f;
    result._12 = 0.0f;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = f * aspect;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = 0.0f;
    result._33 = zf / dz;
    result._34 = -1.0f;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = (zn * zf) / dz;
    result._44 = 0.0f;
}
    
void MwMatrix::CreateOrthographic(MwMatrix &result, float width, float height, float zn, float zf)
{
    float dz = zn - zf;

    result._11 = 2.0f / width;
    result._12 = 0.0f;
    result._13 = 0.0f;
    result._14 = 0.0f;
    result._21 = 0.0f;
    result._22 = 2.0f / height;
    result._23 = 0.0f;
    result._24 = 0.0f;
    result._31 = 0.0f;
    result._32 = 0.0f;
    result._33 = 1.0f / dz;
    result._34 = zn / dz;
    result._41 = 0.0f;
    result._42 = 0.0f;
    result._43 = 0.0f;
    result._44 = 1.0f;
}
    
// Creates a matrix tranformation oriented towards the given vector
void MwMatrix::CreateOrientation(MwMatrix &result, MwVector3 &orientationVector, MwVector3 &orientationOrigin)
{
	MwVector3 rotationAxis;
	
	float phi = MwMaths::VectorAngle(orientationOrigin, orientationVector);
	MwVector3::Cross(rotationAxis, orientationOrigin, orientationVector);
	MwVector3::Normalize(rotationAxis, rotationAxis);
	MwMatrix::CreateRotationAxis(result, rotationAxis, -phi);
}

// Creates a matrix tranformation with the given position, oriented towards the given target
void MwMatrix::CreateOrientedPosition(MwMatrix &result, MwVector3 &position, MwVector3 &target, MwVector3 &orientationOrigin)
{
	MwVector3 orientationVector;
	MwVector3::Subtract(orientationVector, target, position);

	MwMatrix::CreateOrientation(result, orientationVector, orientationOrigin);
	MwMatrix::SetTranslation(result, position);
	//MwMatrix translation;
	//MwMatrix::CreateTranslation(translation, position);
	//MwMatrix::Multiply(result, result, translation);
}

// Creates a matrix tranformation with the given position, oriented as possible towards the given target, with the given axis to rotate around
void MwMatrix::CreateOrientationAxis(MwMatrix &result, MwVector3 &orientationVector, MwVector3 &orientationOrigin, MwVector3 &axis)
{
	MwVector3 actualTarget;
	MwVector3 origin = MwVector3(0.0f, 0.0f, 0.0f);

	MwMaths::PointToPlaneProjection(actualTarget, orientationVector, origin, axis);

	MwMatrix::CreateOrientation(result, actualTarget, orientationOrigin);
}

// Creates a matrix tranformation with the given position, oriented as possible towards the given target, with the given axis to rotate around
void MwMatrix::CreateOrientationAxis(MwMatrix &result, MwVector3 &position, MwVector3 &target, MwVector3 &orientationOrigin, MwVector3 &axis)
{
	MwVector3 actualTarget;

	MwMaths::PointToPlaneProjection(actualTarget, target, position, axis);

	MwMatrix::CreateOrientedPosition(result, position, actualTarget, orientationOrigin);
}

void MwMatrix::Multiply(MwMatrix &result, MwMatrix &matrix1, MwMatrix &matrix2)
{
    float _11 = 	matrix1._11 * matrix2._11 +
	                matrix1._12 * matrix2._21 +
	                matrix1._13 * matrix2._31 +
	                matrix1._14 * matrix2._41;
    float _12 = 	matrix1._11 * matrix2._12 +
	                matrix1._12 * matrix2._22 +
	                matrix1._13 * matrix2._32 +
	                matrix1._14 * matrix2._42;
    float _13 = 	matrix1._11 * matrix2._13 +
	                matrix1._12 * matrix2._23 +
	                matrix1._13 * matrix2._33 +
	                matrix1._14 * matrix2._43;
    float _14 = 	matrix1._11 * matrix2._14 +
	                matrix1._12 * matrix2._24 +
	                matrix1._13 * matrix2._34 +
	                matrix1._14 * matrix2._44;
    float _21 = 	matrix1._21 * matrix2._11 +
	                matrix1._22 * matrix2._21 +
	                matrix1._23 * matrix2._31 +
	                matrix1._24 * matrix2._41;
    float _22 = 	matrix1._21 * matrix2._12 +
	                matrix1._22 * matrix2._22 +
	                matrix1._23 * matrix2._32 +
	                matrix1._24 * matrix2._42;
    float _23 = 	matrix1._21 * matrix2._13 +
	                matrix1._22 * matrix2._23 +
	                matrix1._23 * matrix2._33 +
	                matrix1._24 * matrix2._43;
    float _24 = 	matrix1._21 * matrix2._14 +
	                matrix1._22 * matrix2._24 +
	                matrix1._23 * matrix2._34 +
	                matrix1._24 * matrix2._44;
    float _31 = 	matrix1._31 * matrix2._11 +
	                matrix1._32 * matrix2._21 +
	                matrix1._33 * matrix2._31 +
	                matrix1._34 * matrix2._41;
    float _32 = 	matrix1._31 * matrix2._12 +
	                matrix1._32 * matrix2._22 +
	                matrix1._33 * matrix2._32 +
	                matrix1._34 * matrix2._42;
    float _33 = 	matrix1._31 * matrix2._13 +
	                matrix1._32 * matrix2._23 +
	                matrix1._33 * matrix2._33 +
	                matrix1._34 * matrix2._43;
    float _34 = 	matrix1._31 * matrix2._14 +
	                matrix1._32 * matrix2._24 +
	                matrix1._33 * matrix2._34 +
	                matrix1._34 * matrix2._44;
    float _41 = 	matrix1._41 * matrix2._11 +
	                matrix1._42 * matrix2._21 +
	                matrix1._43 * matrix2._31 +
	                matrix1._44 * matrix2._41;
    float _42 = 	matrix1._41 * matrix2._12 +
	                matrix1._42 * matrix2._22 +
	                matrix1._43 * matrix2._32 +
	                matrix1._44 * matrix2._42;
    float _43 = 	matrix1._41 * matrix2._13 +
	                matrix1._42 * matrix2._23 +
	                matrix1._43 * matrix2._33 +
	                matrix1._44 * matrix2._43;
    float _44 = 	matrix1._41 * matrix2._14 +
	                matrix1._42 * matrix2._24 +
	                matrix1._43 * matrix2._34 +
	                matrix1._44 * matrix2._44;

    result._11 = _11;
    result._12 = _12;
    result._13 = _13;
    result._14 = _14;
    result._21 = _21;
    result._22 = _22;
    result._23 = _23;
    result._24 = _24;
    result._31 = _31;
    result._32 = _32;
    result._33 = _33;
    result._34 = _34;
    result._41 = _41;
    result._42 = _42;
    result._43 = _43;
    result._44 = _44;
}

void MwMatrix::Transpose(MwMatrix &result, MwMatrix &source)
{
    float _11 = source._11;
    float _12 = source._21;
    float _13 = source._31;
    float _14 = source._41;
    float _21 = source._12;
    float _22 = source._22;
    float _23 = source._32;
    float _24 = source._42;
    float _31 = source._13;
    float _32 = source._23;
    float _33 = source._33;
    float _34 = source._43;
    float _41 = source._14;
    float _42 = source._24;
    float _43 = source._34;
    float _44 = source._44;
        
    result._11 = _11;
    result._12 = _12;
    result._13 = _13;
    result._14 = _14;
    result._21 = _21;
    result._22 = _22;
    result._23 = _23;
    result._24 = _24;
    result._31 = _31;
    result._32 = _32;
    result._33 = _33;
    result._34 = _34;
    result._41 = _41;
    result._42 = _42;
    result._43 = _43;
    result._44 = _44;
}
    
void MwMatrix::Invert(MwMatrix &result, MwMatrix &source)
{
	float det = source.GetDeterminant();
    
	if (det == 0.0f)
        return;

    det = 1.0f / det;

    float _11 = det * (source._22 * source._33 * source._44 +
                       source._23 * source._34 * source._42 +
                       source._24 * source._32 * source._43 -
                       source._22 * source._34 * source._43 -
                       source._23 * source._32 * source._44 -
                       source._24 * source._33 * source._42);

	float _12 = det * (source._12 * source._34 * source._43 +
                       source._13 * source._32 * source._44 +
                       source._14 * source._33 * source._42 -
                       source._12 * source._33 * source._44 -
                       source._13 * source._34 * source._42 -
                       source._14 * source._32 * source._43);

    float _13 = det * (source._12 * source._23 * source._44 +
                       source._13 * source._24 * source._42 +
                       source._14 * source._22 * source._43 -
                       source._12 * source._24 * source._43 -
                       source._13 * source._22 * source._44 -
                       source._14 * source._23 * source._42);
	
	float _14 = det * (source._12 * source._24 * source._33 +
                       source._13 * source._22 * source._34 +
                       source._14 * source._23 * source._32 -
                       source._12 * source._23 * source._34 -
                       source._13 * source._24 * source._32 -
                       source._14 * source._22 * source._33);
	
	float _21 = det * (source._21 * source._34 * source._43 +
                       source._23 * source._31 * source._44 +
                       source._24 * source._33 * source._41 -
                       source._21 * source._33 * source._44 -
                       source._23 * source._34 * source._41 -
                       source._24 * source._31 * source._43);
	
	float _22 = det * (source._11 * source._33 * source._44 +
                       source._13 * source._34 * source._41 +
                       source._14 * source._31 * source._43 -
                       source._11 * source._34 * source._43 -
                       source._13 * source._31 * source._44 -
                       source._14 * source._33 * source._41);
	
	float _23 = det * (source._11 * source._24 * source._43 +
                       source._13 * source._21 * source._44 +
                       source._14 * source._23 * source._41 -
                       source._11 * source._23 * source._44 -
                       source._13 * source._24 * source._41 -
                       source._14 * source._21 * source._43);
	
	float _24 = det * (source._11 * source._23 * source._34 +
                       source._13 * source._24 * source._31 +
                       source._14 * source._21 * source._33 -
                       source._11 * source._24 * source._33 -
                       source._13 * source._21 * source._34 -
                       source._14 * source._23 * source._31);
	
	float _31 = det * (source._21 * source._32 * source._44 +
                       source._22 * source._34 * source._41 +
                       source._24 * source._31 * source._42 -
                       source._21 * source._34 * source._42 -
                       source._22 * source._31 * source._44 -
                       source._24 * source._32 * source._41);
	
	float _32 = det * (source._11 * source._34 * source._42 +
                       source._12 * source._31 * source._44 +
                       source._14 * source._32 * source._41 -
                       source._11 * source._32 * source._44 -
                       source._12 * source._34 * source._41 -
                       source._14 * source._31 * source._42);
	
	float _33 = det * (source._11 * source._22 * source._44 +
                       source._12 * source._24 * source._41 +
                       source._14 * source._21 * source._42 -
                       source._11 * source._24 * source._42 -
                       source._12 * source._21 * source._44 -
                       source._14 * source._22 * source._41);
	
	float _34 = det * (source._11 * source._24 * source._32 +
                       source._12 * source._21 * source._34 +
                       source._14 * source._22 * source._31 -
                       source._11 * source._22 * source._34 -
                       source._12 * source._24 * source._31 -
                       source._14 * source._21 * source._32);
	
	float _41 = det * (source._21 * source._33 * source._42 +
                       source._22 * source._31 * source._43 +
                       source._23 * source._32 * source._41 -
                       source._21 * source._32 * source._43 -
                       source._22 * source._33 * source._41 -
                       source._23 * source._31 * source._42);
	
	float _42 = det * (source._11 * source._32 * source._43 +
                       source._12 * source._33 * source._41 +
                       source._13 * source._31 * source._42 -
                       source._11 * source._33 * source._42 -
                       source._12 * source._31 * source._43 -
                       source._13 * source._32 * source._41);
	
	float _43 = det * (source._11 * source._23 * source._42 +
                       source._12 * source._21 * source._43 +
                       source._13 * source._22 * source._41 -
                       source._11 * source._22 * source._43 -
                       source._12 * source._23 * source._41 -
                       source._13 * source._21 * source._42);
	
	float _44 = det * (source._11 * source._22 * source._33 +
	                   source._12 * source._23 * source._31 +
	                   source._13 * source._21 * source._32 -
	                   source._11 * source._23 * source._32 -
	                   source._12 * source._21 * source._33 -
	                   source._13 * source._22 * source._31);
        
    result._11 = _11;
    result._12 = _12;
    result._13 = _13;
    result._14 = _14;
    result._21 = _21;
    result._22 = _22;
    result._23 = _23;
    result._24 = _24;
    result._31 = _31;
    result._32 = _32;
    result._33 = _33;
    result._34 = _34;
    result._41 = _41;
    result._42 = _42;
    result._43 = _43;
    result._44 = _44;
}

void MwMatrix::Invert3x3(MwMatrix &result, MwMatrix &source)
{
    float det = source._12 * source._23 * source._31 +
                source._13 * source._21 * source._32 -
                source._11 * source._23 * source._32 -
                source._12 * source._21 * source._33 -
                source._13 * source._22 * source._31;

    if (det == 0.0f)
        return;

    det = 1.0f / det;

    float _11 = det * (source._22 * source._33 - source._23 * source._32);
    float _12 = det * (source._13 * source._32 - source._12 * source._33);
    float _13 = det * (source._12 * source._23 - source._13 * source._22);
    float _21 = det * (source._23 * source._31 - source._21 * source._33);
    float _22 = det * (source._11 * source._33 - source._13 * source._31);
    float _23 = det * (source._13 * source._21 - source._11 * source._23);
    float _31 = det * (source._21 * source._32 - source._22 * source._31);
    float _32 = det * (source._12 * source._31 - source._11 * source._32);
    float _33 = det * (source._11 * source._22 - source._12 * source._21);

	result._11 = _11;
	result._12 = _12;
	result._13 = _13;
	result._21 = _21;
	result._22 = _22;
	result._23 = _23;
	result._31 = _31;
	result._32 = _32;
	result._33 = _33;
}

void MwMatrix::GetAxisX(MwVector3 &result, MwMatrix &source)
{
	result.x = source._11;
	result.y = source._12;
	result.z = source._13;
}

void MwMatrix::SetAxisX(MwMatrix &result, MwVector3 &source)
{
	result._11 = source.x;
	result._12 = source.y;
	result._13 = source.z;
}

void MwMatrix::GetAxisY(MwVector3 &result, MwMatrix &source)
{
	result.x = source._21;
	result.y = source._22;
	result.z = source._23;
}

void MwMatrix::SetAxisY(MwMatrix &result, MwVector3 &source)
{
	result._21 = source.x;
	result._22 = source.y;
	result._23 = source.z;
}

void MwMatrix::GetAxisZ(MwVector3 &result, MwMatrix &source)
{
	result.x = source._31;
	result.y = source._32;
	result.z = source._33;
}

void MwMatrix::SetAxisZ(MwMatrix &result, MwVector3 &source)
{
	result._31 = source.x;
	result._32 = source.y;
	result._33 = source.z;
}

void MwMatrix::GetTranslation(MwVector3 &result, MwMatrix &source)
{
	result.x = source._41;
	result.y = source._42;
	result.z = source._43;
}

void MwMatrix::SetTranslation(MwMatrix &result, MwVector3 &source)
{
	result._41 = source.x;
	result._42 = source.y;
	result._43 = source.z;
}

void MwMatrix::ExtractScaling(MwVector3 &result, MwMatrix &source)
{
	result.x = MwMath::Sqrt(source._11 * source._11 + source._12 * source._12 + source._13 * source._13);
	result.y = MwMath::Sqrt(source._21 * source._21 + source._22 * source._22 + source._23 * source._23);
	result.z = MwMath::Sqrt(source._31 * source._31 + source._32 * source._32 + source._33 * source._33);
}

void MwMatrix::ExtractEulerRotation(MwVector3 &result, MwMatrix &source)
{
	result.x = MwMath::ArcTan2(source._23, source._33);
	
	float cosY = MwMath::Sqrt(source._11 * source._11 + source._12 * source._12);
	result.y = MwMath::ArcTan2(-source._13, cosY);
	
	float sinX = MwMath::Sin(result.x);
	float cosX = MwMath::Cos(result.x);
	result.z = MwMath::ArcTan2(sinX * source._31 - cosX * source._21, cosX * source._22 - sinX * source._32);
}