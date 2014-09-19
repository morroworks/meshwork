#pragma once

#include "..\..\MwGlobals.h"

class MwMatrix;
class MwVector3;
class MwVector2;

class MWDLLCLASS MwVector4
{
public:
	float x, y, z, w;

	MwVector4(void);
	MwVector4(float value);
	MwVector4(float x, float y, float z, float w);
	MwVector4(MwVector4 &source);
	MwVector4(MwVector3 &source, float w);
	MwVector4(MwVector2 &source, float z, float w);
	~MwVector4(void);

	float GetLength();
	void Set(float value);
	void Set(float x, float y, float z, float w);

	static void Copy(MwVector4 &result, MwVector4 &source);
	static void SetLength(MwVector4 &result, MwVector4 &v, float length);
	static void Normalize(MwVector4 &result, MwVector4 &v);
	static float Distance(MwVector4 &v1, MwVector4 &v2);
	static void Lerp(MwVector4 &result, MwVector4 &v1, MwVector4 &v2, float factor);
	static void Subtract(MwVector4 &result, MwVector4 &v1, MwVector4 &v2);
	static void Add(MwVector4 &result, MwVector4 &v1, MwVector4 &v2);
	static float Dot(MwVector4 &v1, MwVector4 &v2);
	static void Cross(MwVector4 &result, MwVector4 &v1, MwVector4 &v2, MwVector4 &v3);
	static void Scale(MwVector4 &result, MwVector4 &v1, MwVector4 &v2);
	static void Scale(MwVector4 &result, MwVector4 &v1, float factor);
	static void Min(MwVector4 &result, MwVector4 &v1, MwVector4 &v2);
	static void Max(MwVector4 &result, MwVector4 &v1, MwVector4 &v2);
	static void Transform(MwVector4 &result, MwVector4 &v, MwMatrix &transformation);
	static void Transform(MwVector4 &result, MwVector3 &v, MwMatrix &transformation);
};

