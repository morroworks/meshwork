#pragma once

#include "..\..\MwGlobals.h"

class MwMatrix;

class MWDLLCLASS MwVector2
{
public:
	float x, y;

	MwVector2(void);
	MwVector2(float value);
	MwVector2(float x, float y);
	MwVector2(MwVector2 &source);
	~MwVector2(void);

	float GetLength();
	void Set(float value);
	void Set(float x, float y);

	static void Copy(MwVector2 &result, MwVector2 &source);
	static void SetLength(MwVector2 &result, MwVector2 &v, float length);
	static void Normalize(MwVector2 &result, MwVector2 &v);
	static float Distance(MwVector2 &v1, MwVector2 &v2);
	static void Lerp(MwVector2 &result, MwVector2 &v1, MwVector2 &v2, float factor);
	static void Subtract(MwVector2 &result, MwVector2 &v1, MwVector2 &v2);
	static void Add(MwVector2 &result, MwVector2 &v1, MwVector2 &v2);
	static float Dot(MwVector2 &v1, MwVector2 &v2);
	static void Cross(MwVector2 &result, MwVector2 &v1);
	static void Scale(MwVector2 &result, MwVector2 &v1, MwVector2 &v2);
	static void Scale(MwVector2 &result, MwVector2 &v1, float factor);
	static void Min(MwVector2 &result, MwVector2 &v1, MwVector2 &v2);
	static void Max(MwVector2 &result, MwVector2 &v1, MwVector2 &v2);
	static void Transform(MwVector2 &result, MwVector2 &v, MwMatrix &transformation);
	static void TransformNormal(MwVector2 &result, MwVector2 &v, MwMatrix &transformation);
};

