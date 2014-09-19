#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "SrARGB.h"
#include "SrARGBInt.h"

struct SrShadingParameters
{
    int fogStart, fogEnd;
    SrARGB fogColor, basicLightColor, tintColor;
    float refractionFactor;
    SrARGBInt globalAmbient;
    int cellDiffuseSegmentation, cellSpecularSegmentation;
    int cellEnvMapSegmentation;
};