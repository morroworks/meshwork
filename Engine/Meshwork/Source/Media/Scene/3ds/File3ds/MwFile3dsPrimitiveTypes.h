#pragma once

#include "..\..\..\..\MwGlobals.h"

// Represents a header of a 3ds file chunk. Headers consist of an id and length of the chunk (including the header)
struct MwFile3dsChunkHeader
{
    unsigned short id;
    int length;
};

// Defines a vertex of a mesh. Contains the vertex' location coordinates and texture coordinates
struct MwFile3dsMeshVertex
{
    float x, y, z;
    float tu, tv;
};

// Represents a triangle of a mesh. Contains the indices of the 3 vertices which form the triangle and a 32-bit value, whose bits denote the respective smooth groups to which the triangle belongs. The info field is disregarded.
struct MwFile3dsMeshFace
{
    unsigned short a, b, c, info;
    unsigned int smoothGroups;
};

// Contains the transformation matrix of a mesh in the 3ds file.
struct MwFile3dsObjectTransformation
{
    float 
		_11, _12, _13, _14,
        _21, _22, _23, _24,
        _31, _32, _33, _34,
        _41, _42, _43, _44;
};

// Represents a color in floating point rgb format, each channel normally ranging in [0, 1]. Used for lights colors in the 3ds file.
struct MwFile3dsColorFloat
{
    float r, g, b;
};

// Represents a color in integer rgb format, each channel normally ranging in [0, 255]. Used for materials colors in the 3ds file.
struct MwFile3dsColorByte
{
    unsigned char r, g, b;
};

// Represents a 3d vector in the 3ds file. Used by various 3ds objects for denoting position and orientation.
struct MwFile3dsVector
{
    float x, y, z;
};