#pragma once

#include "..\..\..\MeshworkEngine.h"

#include <fbxsdk.h>

// Important notice about the MwFbxScene is that it CAN ONLY LOAD FILES FROM THE PHYSICAL FILE SYSTEM.
// The reason for this restriction is that it uses the Autodesk FBX SDK, which on the other hand does not support loading from memory.
// As consequence, MwFbxScene uses the serialization parameters of the context to get the name of the file to load. The source stream is, in fact, not used.

class MwFbxScene :
	public MwScene
{
private:
	FbxManager *fbxManager;
	FbxScene *fbxScene;

	MwLinearMechanism *animationFrame;
	
	MwDictionary<void*, MwBaseResource*> resourceMap;

	MwVector2 FbxToMwVector2(FbxDouble2 fbxVector);
	MwVector3 FbxToMwVector3(FbxDouble3 fbxVector);
	MwVector3 FbxToMwVector3(FbxDouble4 fbxVector);
	void FbxToMwMatrix(MwMatrix &result, FbxAMatrix *fbxMatrix);
	void FbxCreateRotationMatrix(MwMatrix &result, MwVector3 eulerAngles, EFbxRotationOrder rotationOrder);

	void GetNodeGeometryTransform(MwMatrix &transform, FbxNode *fbxNode);

	void LoadNodeDefaultTransform(MwTransform *transform, FbxNode *fbxNode);
	bool LoadNodeKeyframeAnimation(MwEntitySet *entitySet, FbxNode* fbxNode, MwTransform *transformToAnimate);

	bool GetMaterialPropertyTextureName(const FbxProperty &fbxProperty, MwString &fileName);
	MwVector4 GetMaterialPropertyColor(const FbxProperty &fbxProperty);
	float GetMaterialPropertyColorFactor(const FbxProperty &fbxProperty);
	MwMaterial *AcquireNodeMaterial(FbxSurfaceMaterial *fbxMaterial);


	void LoadMesh_Vertices(MwDeviceMesh *deviceMesh, FbxMesh *fbxMesh, MwMatrix &geometryTransform);
	void LoadMesh_TextureCoords(MwDeviceMesh *deviceMesh, FbxMesh *fbxMesh);
	bool LoadMesh_Animation(MwDeviceMesh *deviceMesh, FbxMesh *fbxMesh);
	MwSmoothGrouping* LoadMesh_CreateSmoothGrouping(FbxMesh *fbxMesh);
	void LoadMesh(MwEntitySet *entitySet, FbxMesh *fbxMesh, MwMatrix &geometryTransform);

	void LoadNode(MwEntitySet *entitySet, FbxNode* fbxNode, FbxNodeAttribute::EType loadType);

public:
	MwFbxScene(void);
	~MwFbxScene(void);

	bool Load(MwBaseStream &source);
	bool Save(MwBaseStream &destination, const char *format);
};

