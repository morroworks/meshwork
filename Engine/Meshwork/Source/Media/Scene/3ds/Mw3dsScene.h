#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\MwScene.h"

#include "File3ds\MwFile3ds.h"

#include "..\..\..\Engine\Entities\EntitySet\MwEntitySet.h"
#include "..\..\..\Engine\Entities\Material\MwMaterial.h"
#include "..\..\..\Engine\Entities\Mechanisms\MwLinearMechanism.h"

#include "..\..\..\Tools\MwList.h"

struct Mw3dsSceneNameResourceMapping
{
	MwString *name3ds;
	MwBaseResource *resource;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<Mw3dsSceneNameResourceMapping>;

class MWDLLCLASS Mw3dsScene :
	public MwScene
{
private:
	// Separate resourceMapping and materialMapping, because MwFile3dsMaterial is not a MwFile3dsBase object, which is because the 3ds file structure does not imply it to be. That generally means a 3ds material can have the same name as a 3ds mesh, 3ds light or 3ds camera
	// TODO: If two resou	rces of different types can have the same name, finding a resource by name can be ambiguous
	MwList<Mw3dsSceneNameResourceMapping> resourceMapping, materialMapping;

	MwBaseResource *CreateResourceAndMapping(MwString name3ds, MwBaseResource *resource);
	MwBaseResource *FindResourceMapping(const MwString &name3ds);

	MwBaseResource *CreateMaterialAndMapping(MwString name3ds, MwBaseResource *material);
	MwBaseResource *FindMaterialMapping(const MwString &name3ds);

	void LoadMaterialResource(MwFile3dsMaterial *material3ds);
	void LoadMeshResource(MwFile3dsMesh *mesh3ds);
	void LoadLightResource(MwFile3dsLight *light3ds);
	void LoadCameraResource(MwFile3dsCamera *camera3ds);

	void BuildSceneHierarchyNode(MwEntitySet *branch, MwFile3dsHierarchyNode *hierarchyNode3ds, MwLinearMechanism *animationFrame);
	void BuildSceneHierarchy(MwEntitySet *branch, MwFile3dsHierarchy *hierarchy3ds, MwLinearMechanism *animationFrame = 0);

public:
	Mw3dsScene(void);
	~Mw3dsScene(void);

	bool Load(MwBaseStream &source);
	bool Save(MwBaseStream &destination, const char *format);
};

