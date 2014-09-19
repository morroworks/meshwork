#pragma once

#include "..\..\MwGlobals.h"

enum MwRenderState
{
    AlphaBlendNone = 0,
    AlphaBlendTransparency = 1,
    AlphaBlendAdd = 2,
    DepthEnable = 3,
    DepthDisable = 4,
    CullEnable = 5,
    CullDisable = 6
};