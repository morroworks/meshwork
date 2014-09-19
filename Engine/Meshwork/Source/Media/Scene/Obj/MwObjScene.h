#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\MwScene.h"

#include "..\..\..\Engine\Meshwork.h"

#include "FileObj\MwFileObjMesh.h"
#include "FileObj\MwFileObjMaterial.h"

class MWDLLCLASS MwObjScene :
	public MwScene
{
private:
	MwMesh* LoadMeshResource(MwFileObjMesh* meshObj);
	MwMaterial* LoadMaterialResource(MwFileObjMaterial *materialObj);

public:
	MwObjScene(void);
	~MwObjScene(void);

	bool Load(MwBaseStream &source);
	bool Save(MwBaseStream &destination, const char *format);
};

