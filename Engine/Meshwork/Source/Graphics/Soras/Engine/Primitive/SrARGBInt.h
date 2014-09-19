#pragma once

#include "..\..\..\..\MwGlobals.h"

class MWDLLCLASS SrARGBInt
{
public:
    int b, g, r, a;

    SrARGBInt(void)
	{
	};

    SrARGBInt(int a, int r, int g, int b)
    {
        this->b = b;
        this->g = g;
        this->r = r;
        this->a = a;
    };
};