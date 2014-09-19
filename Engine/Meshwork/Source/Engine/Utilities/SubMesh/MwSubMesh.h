#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwSubMeshPrimitiveTypes.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwSubMeshFace*>;

// Creates geometry from manually selected vertices from original geometry
// The calss simply builds its geometry by consequently adding faces with the AddFace() method, and filling an added face vertices with the AddFaceVertexMethod(), while keeping from creating the same vertex more than once
// The resulting faces can be accessed via the faces member variable, which holds the faces with their vertex indexes pointing to the vertexIndices member variable.
// The resulting vertices can be accessed via the vertexIndices member variable, which elements represent a vertex and the values of its elements being indices to the original vertices used
class MWDLLCLASS MwSubMesh
{
private:
	// a mapping from a vertex index of the original geometry to a vertex index in the new geometry, that is vertexIndices[originalVertexReferences[originalVertexIndex]] = originalVertexIndex. Used to quickly find if an original vertex has been used and if so - its index
	int *originalVertexReferences;
	int originalVertexCount;

public:
	// List of all vertices used by the new geometry. The value of the elements are the indices of vertices of the original geometry.
	MwList<int> vertexIndices;
	// List of all faces used be the new geometry. The faces contain indices to the vertices of the face, the indices pointing to the vertexIndices member variable.
	MwList<MwSubMeshFace*> faces;

	MwSubMesh(int originalVertexCount);
	~MwSubMesh(void);

	// Adds a face to the new geometry and returns its index
	// returns - the index of the added face
	int AddFace();
	// Adds a vertex to a face of the new geometry
	// faceIndex - index of the face from the new geometry to add a vertex to.
	// originalVertexIndex - index of the vertex within the original geometry. It's value must be between 0 and less than the value given as originalVertexCount in the class constructor
	// returns - index of the added vertex within the new geometry
	int AddFaceVertex(int faceIndex, int originalVertexIndex);

	// Resets the geometry of the submesh, making it ready for another use, and able to create a new sub mesh from the original one.
	void Reset();
};

