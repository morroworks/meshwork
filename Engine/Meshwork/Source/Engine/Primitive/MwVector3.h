#pragma once

#include "..\..\MwGlobals.h"

class MwMatrix;
class MwVector2;

class MWDLLCLASS MwVector3
{
public:
	float x, y, z;

	MwVector3(void);
	MwVector3(float value);
	MwVector3(float x, float y, float z);
	MwVector3(MwVector3 &source);
	MwVector3(MwVector2 &source, float z);
	~MwVector3(void);

	float GetLength();
	void Set(float value);
	void Set(float x, float y, float z);
	
	static void Copy(MwVector3 &result, MwVector3 &source);
	static void SetLength(MwVector3 &result, MwVector3 &v, float length);
	static void Normalize(MwVector3 &result, MwVector3 &v);
	static float Distance(MwVector3 &v1, MwVector3 &v2);
	static void Lerp(MwVector3 &result, MwVector3 &v1, MwVector3 &v2, float factor);
	static void Subtract(MwVector3 &result, MwVector3 &v1, MwVector3 &v2);
	static void Add(MwVector3 &result, MwVector3 &v1, MwVector3 &v2);
	static float Dot(MwVector3 &v1, MwVector3 &v2);
	static void Cross(MwVector3 &result, MwVector3 &v1, MwVector3 &v2);
	static void Scale(MwVector3 &result, MwVector3 &v1, MwVector3 &v2);
	static void Scale(MwVector3 &result, MwVector3 &v1, float factor);
	static void Min(MwVector3 &result, MwVector3 &v1, MwVector3 &v2);
	static void Max(MwVector3 &result, MwVector3 &v1, MwVector3 &v2);
	static void Transform(MwVector3 &result, MwVector3 &v, MwMatrix &transformation);
	static void TransformNormal(MwVector3 &result, MwVector3 &v, MwMatrix &transformation);

	static void CartesianToSphere(MwVector3 &result, float x, float y, float z);
	static void CartesianToSphere(MwVector3 &result, MwVector3 &cartesian);
	static void SphereToCartesian(MwVector3 &result, float azimuth, float elevation, float radius);
	static void SphereToCartesian(MwVector3 &result, MwVector3 &spherical);
	static void LerpSherical(MwVector3 &result, MwVector3 &v1, MwVector3 &v2, float factor);
};

