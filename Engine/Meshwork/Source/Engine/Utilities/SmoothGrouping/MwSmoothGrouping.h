#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwSmoothGroupingPrimitiveTypes.h"

#include "..\..\..\Tools\MwList.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwSmoothGroupingVertexInfo>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwSmoothGroupingVertex>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwSmoothGroupingFace>;

// The class assumes a mesh built of polygon faces, where each face is formed by indices to a vertex array.
// Each face may belong to a number of smoothing groups, which are denoted by the bits of a value.
// The input data is loaded through the SetFaceSmoothingGroup() and AddFaceVertex() methods, by which the original geometry of a mesh is input.
// While using the SetFaceSmoothingGroup() and AddFaceVertex() methods, a set of vertex indices and faces are being created, in which faces with no matching smoothing groups no longer share the same vertices. This is achieved by creating a new vertex whenever an original vertex is shared between faces whose smoothing groups do not match.
// The vertices of the newly build mesh can be accessed by the vertexIndices member variable, where each element represents a vertex and the value of each element is an index to the originally input vertex
// The faces of the newly build mesh can be accessed by the faces member variable, where each element represents a face with vertices represented by indices that point to the vertexIndices member variable. For example, the index to the original vertex of the n-th new face's m-th vertex would be vertexIndices[faces[n].indices[m]]
// The algorithm simply accumulates for each vertex all the smoothing groups of each face the vertex has been used by, and when a face's smoothing groups do not match any of the accumulated smoothing groups of a vertex it uses, then a new vertex is created and the face is fed with the index of that new vertex.
// The new mesh data may have more vertices than the original and will always have the same number of faces.
class MWDLLCLASS MwSmoothGrouping
{
private:
	MwList<MwSmoothGroupingVertexInfo> originalVerticesInfo;

public:
    MwList<MwSmoothGroupingVertex> vertexIndices;
    MwList<MwSmoothGroupingFace> faces;

	MwSmoothGrouping(int originalFacesCount, int originalVertexCount);
	~MwSmoothGrouping(void);

	// Sets a face's smoothing groups
	// faceIndex - index of the face to set the smoothing groups to
	// smoothingGroupFlags - its bits denote which smoothing groups the face belongs to. Being a 64-bit value means that there are a maximum 64 different smoothing groups possible
	void SetFaceSmoothingGroups(int faceIndex, unsigned long long smoothingGroupFlags);
	
	// Adds a vertex to a face.
	// faceIndex - index of face to add the vertex to
	// originalVertexIndex - index of the vertex in the original geometry
	// returns the index of the added vertex in the vertexIndices member variable
	int AddFaceVertex(int faceIndex, int originalVertexIndex);
};

