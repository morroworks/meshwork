#pragma once

#include "..\..\MwGlobals.h"

enum MwColorOperation
{
    MwColorOperation_None,
    MwColorOperation_Set,
    MwColorOperation_Add,
    MwColorOperation_Subtract,
    MwColorOperation_Modulate,
    MwColorOperation_Lighter,
    MwColorOperation_Darker
};