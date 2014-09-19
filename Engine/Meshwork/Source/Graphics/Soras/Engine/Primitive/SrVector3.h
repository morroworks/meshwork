#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\MwMath.h"

struct SrVector3
{
    float x, y, z;

	static void Normalize(SrVector3 &vector)
	{
		float k = MwMath::Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		if (k != 0.0f)
		{
			k = 1.0f / k;

			vector.x *= k;
			vector.y *= k;
			vector.z *= k;
		}	
	};
};
