#pragma once

#include "..\..\..\..\MwGlobals.h"

class MWDLLCLASS SrUnit
{
public:
    static const int bitCount = 14;
    static const int high = 0x4000;
    static const int max = 0xffff;
    static const int min = -0xffff;

	static int FromFloat(float value)
	{
		return (int)(value * SrUnit::high);
	};

	static float ToFloat(int value)
	{
		return (float)value / (float)SrUnit::high;
	};
};