#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwList.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<int>;

// Holds all the indices that derive from a given original vertex and all their smooth groups accumulated
struct MwSmoothGroupingVertexInfo
{
    unsigned long long accumulatedSmoothingGroups;
    MwList<int> indices;
};

// Holds the smoothing groups of a face and the indices of its vertices
struct MwSmoothGroupingFace
{
    unsigned long long smoothingGroups;
	MwList<int> indices;
};

// Holds the smooth groups of a vetex
struct MwSmoothGroupingVertex
{
    unsigned long long accumulatedSmoothingGroups;
    int index;
};
