#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "SrVector3.h"
#include "SrARGBInt.h"

class MWDLLCLASS SrLight
{
public:
    SrVector3 position;
    SrARGBInt color;
    float range;

    SrLight()
    {
        this->color = SrARGBInt(0xff, 0xff, 0xff, 0xff);
        this->range = 500;
    };

	~SrLight(void)
	{
	};
};