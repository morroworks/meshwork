#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsPrimitiveTypes.h"
#include "MwFile3dsBaseObject.h"
#include "MwFile3dsMesh.h"
#include "MwFile3dsLight.h"
#include "MwFile3dsCamera.h"
#include "MwFile3dsMaterial.h"
#include "MwFile3dsKeyFrames.h"
#include "MwFile3dsHierarchy.h"

#include "..\..\..\..\Tools\Streams\MwBaseStream.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFile3dsBaseObject*>;
MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFile3dsMaterial*>;

enum MwFile3dsMaterialParameter
{
    MwFile3dsMaterialParameter_AmbientColor,
    MwFile3dsMaterialParameter_DiffuseColor,
    MwFile3dsMaterialParameter_SpecularColor,
    MwFile3dsMaterialParameter_TextureMap,
    MwFile3dsMaterialParameter_SpecularMap,
    MwFile3dsMaterialParameter_BumpMap,
    MwFile3dsMaterialParameter_ReflectionMap,
    MwFile3dsMaterialParameter_SpecularLevel,
    MwFile3dsMaterialParameter_Glossiness
};

class MWDLLCLASS MwFile3ds
{
private:
	static const int chunk_Main = 0x4D4D;
	static const int 	chunk_3dEditor = 0x3D3D;
	static const int 		chunk_ObjectBlock = 0x4000;
	static const int 			chunk_TriangularMesh = 0x4100;
	static const int 				chunk_VerticesList = 0x4110;
	static const int 				chunk_FacesList = 0x4120;
	static const int 				chunk_MeshMaterialName = 0x4130;
	static const int 				chunk_MappingCoords = 0x4140;
	static const int 				chunk_SmoothGroups = 0x4150;
	static const int 				chunk_LocalCoordSystem = 0x4160;
	static const int 			chunk_Light = 0x4600;
	static const int 				chunk_LightColor = 0x0010;
	static const int 				chunk_SpotLight = 0x4610;
	static const int 				chunk_LightOff = 0x4620;
	static const int 			chunk_Camera = 0x4700;
	static const int 		chunk_MaterialBlock = 0xAFFF;
	static const int 			chunk_MaterialName = 0xA000;
	static const int 			chunk_AmbientColor = 0xA010;
	static const int 			chunk_DiffuseColor = 0xA020;
	static const int 			chunk_SpecularColor = 0xA030;
	static const int 				chunk_MaterialColor = 0x011;
	static const int 			chunk_Glossiness = 0xA040;
	static const int 			chunk_SpecularLevel = 0xA041;
	static const int 				chunk_AmountOf = 0x0030;
	static const int 			chunk_TextureMap = 0xA200;
	static const int 			chunk_SpecularMap = 0xA204;
	static const int 			chunk_BumpMap = 0xA230;
	static const int 			chunk_ReflectionMap = 0xA220;
	static const int 				chunk_MappingFileName = 0xA300;
	static const int 	chunk_KeyFrameData = 0xB000;
	static const int 		chunk_KeyFrameInfo = 0xB008;
	static const int 		chunk_CurrentFrame = 0xB009;
	static const int 		chunk_KeyFrameObjectNode = 0xB002;
	static const int 		chunk_KeyFrameCameraNode = 0xB003;
	static const int 		chunk_KeyFrameLightNode = 0xB005;
	static const int 			chunk_KFObjectNameAndHierarchyLevel = 0xB010;
	static const int 			chunk_KFObjectInstanceName = 0xB011;
	static const int 			chunk_KFObjectPivot = 0xB013;
	static const int 			chunk_KFObjectPositionTrack = 0xB020;
	static const int 			chunk_KFObjectRotationTrack = 0xB021;
	static const int 			chunk_KFObjectScalingTrack = 0xB022;
	static const int 			chunk_KFObjectID = 0xB030;

	MwBaseStream *dataStream;

	MwFile3dsChunkHeader currentHeader;
	
	MwString currentString;

	MwFile3dsMesh *currentMesh;
	MwFile3dsLight *currentLight;
	MwFile3dsCamera *currentCamera;

	MwFile3dsMaterial *currentMaterial;
	MwFile3dsMaterialParameter currentMaterialParameter;

	MwFile3dsKeyFrameObject *currentKeyFrameObject;

	int hierarchyIndex;

	long long mainChunkEnd;

	bool ReadChunks();

	void ReadChunkObjectBlock();
	void ReadChunkTriangularMesh();
	void ReadChunkVerticesList();
	void ReadChunkFacesList();
	void ReadChunkMeshMaterialName();
	void ReadChunkMappingCoords();
	void ReadChunkSmoothGroups();
	void ReadChunkLocalCoordSystem();
	void ReadChunkLight();
	void ReadChunkLightColor();
	void ReadChunkSpotLight();
	void ReadChunkLightActive();
	void ReadChunkCamera();
	void ReadChunkMaterialBlock();
	void ReadChunkMaterialName();
	void ReadChunkAmbientColor();
	void ReadChunkDiffuseColor();
	void ReadChunkSpecularColor();
	void ReadChunkMaterialColor();
	void ReadChunkSpecularLevel();
	void ReadChunkGlossiness();
	void ReadChunkAmountOf();
	void ReadChunkTextureMap();
	void ReadChunkSpecularMap();
	void ReadChunkBumpMap();
	void ReadChunkReflectionMap();
	void ReadChunkMappingFileName();

	void ReadChunkKeyframesInfo();
	void ReadChunkKeyframesCurrentFrame();
	void ReadChunkKFObjectNameAndHieararchyLevel();
	void ReadChunkKFObjectInstanceName();
	void ReadChunkKFObjectPivot();
	void ReadChunkKFObjectPositionTrack();
	void ReadChunkKFObjectRoatationTrack();
	void ReadChunkKFObjectScalingTrack();
	void ReadChunkKFObjectID();

	MwString ReadString();
	void ReadKeyFrameTrackHeader(MwFile3dsKeyFramesTrack *track);
	void ReadKeyFrameParams(MwFile3dsKeyFrameBase *keyFrame);

	void InverseAllMeshesTransformation();
	MwFile3dsBaseObject *FindObject(MwString name);
	int FindParent(int child);
	void BuildHierarchyFromResources();
	void ArrangeHierarchyObject(int hierarchyLevel, MwFile3dsHierarchy *hierarchy);
	void ArrangeHierarchy();

public:

	//TODO: separate mesh, cameara and light?
	// Contains all the resource objects in the 3ds - meshes, lights, cameras
	MwList<MwFile3dsBaseObject*> objects;
	int numLights;

	// Contains all the material resources in the 3ds
	MwList<MwFile3dsMaterial*> materials;

	// Contains all the keyframe data, where every keyframe node is references a resource object via the object's name.
	MwFile3dsKeyFrames *keyFrames;

	// After ArrangeHierarchy, this holds the hierarchical structure of the 3ds scene, including the references to the resource objects and their keyframes
	MwFile3dsHierarchy *hierarchy;

	MwFile3ds(void);
	~MwFile3ds(void);

	bool Read(MwBaseStream *dataStream);
};

