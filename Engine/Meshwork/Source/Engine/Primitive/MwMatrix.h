#pragma once

#include "..\..\MwGlobals.h"

class MwVector3;

class MWDLLCLASS MwMatrix
{
public:
	float _11, _12, _13, _14,
          _21, _22, _23, _24,
          _31, _32, _33, _34,
          _41, _42, _43, _44;	
	
	MwMatrix(void);
	MwMatrix(MwMatrix &source);
	~MwMatrix(void);
	
	float GetDeterminant();

	static void Copy(MwMatrix &result, MwMatrix &source);
	static void CreateIdentity(MwMatrix &result);
	static void CreateRotationX(MwMatrix &result, float phi);
	static void CreateRotationY(MwMatrix &result, float phi);
	static void CreateRotationZ(MwMatrix &result, float phi);
	static void CreateRotationAxis(MwMatrix &result, float x, float y, float z, float phi);
	static void CreateRotationAxis(MwMatrix &result, MwVector3 &axis, float phi);
	static void CreateTranslation(MwMatrix &result, float x, float y, float z);
	static void CreateTranslation(MwMatrix &result, MwVector3 &translation);
	static void CreateScale(MwMatrix &result, float x, float y, float z);
	static void CreateScale(MwMatrix &result, MwVector3 &scaling);
	static void CreateLookAt(MwMatrix &result, MwVector3 &position, MwVector3 &lookAt, MwVector3 &up);
	static void CreatePerspectiveFieldOfView(MwMatrix &result, float fov, float aspect, float zn, float zf);
	static void CreateOrthographic(MwMatrix &result, float width, float height, float zn, float zf);
	static void CreateOrientation(MwMatrix &result, MwVector3 &orientationVector, MwVector3 &orientationOrigin);
	static void CreateOrientedPosition(MwMatrix &result, MwVector3 &position, MwVector3 &target, MwVector3 &orientationOrigin);
	static void CreateOrientationAxis(MwMatrix &result, MwVector3 &orientationVector, MwVector3 &orientationOrigin, MwVector3 &axis);
	static void CreateOrientationAxis(MwMatrix &result, MwVector3 &position, MwVector3 &target, MwVector3 &orientationOrigin, MwVector3 &axis);
	static void Multiply(MwMatrix &result, MwMatrix &matrix1, MwMatrix &matrix2);
	static void Transpose(MwMatrix &result, MwMatrix &source);
	static void Invert(MwMatrix &result, MwMatrix &source);
	static void Invert3x3(MwMatrix &result, MwMatrix &source);
	static void GetAxisX(MwVector3 &result, MwMatrix &source);
	static void SetAxisX(MwMatrix &result, MwVector3 &source);
	static void GetAxisY(MwVector3 &result, MwMatrix &source);
	static void SetAxisY(MwMatrix &result, MwVector3 &source);
	static void GetAxisZ(MwVector3 &result, MwMatrix &source);
	static void SetAxisZ(MwMatrix &result, MwVector3 &source);
	static void GetTranslation(MwVector3 &result, MwMatrix &source);
	static void SetTranslation(MwMatrix &result, MwVector3 &source);
	static void ExtractScaling(MwVector3 &result, MwMatrix &source);
	static void ExtractEulerRotation(MwVector3 &result, MwMatrix &source);
};

