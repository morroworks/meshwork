#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsBaseObject.h"

#include "MwFile3dsPrimitiveTypes.h"

#include "..\..\..\..\Tools\MwString.h"

class MWDLLCLASS MwFile3dsMesh :
	public MwFile3dsBaseObject
{
public:
    int numVertices, numFaces;
    MwFile3dsMeshVertex *vertices;
    MwFile3dsMeshFace *faces;
    MwFile3dsObjectTransformation localCoordSystem;
    MwString materialName;

	MwFile3dsMesh(void);
	~MwFile3dsMesh(void);

	void InverseTransformation();
};

