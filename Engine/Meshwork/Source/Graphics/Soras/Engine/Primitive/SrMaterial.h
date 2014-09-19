#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "SrARGBInt.h"

struct SrMaterial
{
    SrARGBInt ambient, diffuse, specular;
    float gloss;
};