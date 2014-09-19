#pragma once

#include "..\..\..\MwGlobals.h"

// TODO: Consider moving each of these operations into mechanisms
// Consider making mechanisms, that work on the CURRENT object - that way moving a mechanism, let's say, from one Transform to another will immediately work on the second transform 
enum MwTransformOperation
{
    MwTransformOperation_Translate,
    MwTransformOperation_RotateX,
    MwTransformOperation_RotateY,
    MwTransformOperation_RotateZ,
    MwTransformOperation_Scale,
    MwTransformOperation_TranslateAbsolute,
    MwTransformOperation_RotateAbsoluteX,
    MwTransformOperation_RotateAbsoluteY,
    MwTransformOperation_RotateAbsoluteZ,
    MwTransformOperation_ScaleAbsolute
};