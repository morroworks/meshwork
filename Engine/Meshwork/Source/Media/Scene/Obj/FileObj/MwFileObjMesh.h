#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\MwList.h"
#include "..\..\..\..\Tools\MwString.h"

#include "MwFileObjPrimitiveTypes.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjFace*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjVector4>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjVector3>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjFaceVertex>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFileObjBufferedFace*>;

class MWDLLCLASS MwFileObjMesh
{
private:
	int FindEquivalentBufferedVertexIndex(MwFileObjFaceVertex *faceVertex);

public:
	MwString name, materialName;

	// The raw faces data from the Obj file
	MwList<MwFileObjFace*> faces;
	// The raw vertices data from the Obj file
	MwList<MwFileObjVector4> vertices;
	// The raw nomals and texCoords data from the Obj file
	MwList<MwFileObjVector3> normals, texCoords;

	// Filled by CreateBuffers(), a set of all used unique combinations of vertex position/texCoords/normal
	MwList<MwFileObjFaceVertex> bufferedVertices;
	// Filled by CreateBuffers(), a set of all primitives, such as to correctly reference the vertices in vertexBuffer
	MwList<MwFileObjBufferedFace*> bufferedFaces;
	
	MwFileObjMesh(void);
	~MwFileObjMesh(void);

	// After data from the file has been filled, this method creates a vertex buffer of vertices with unique combinations of position/texCoords/normal and a respective primitive (index) buffer.
	// Required because although Obj file uses indexing, it can have face vertices referencing the same vertex position, but in combination with different texCoords or normal
	void CreateBuffers();
};

