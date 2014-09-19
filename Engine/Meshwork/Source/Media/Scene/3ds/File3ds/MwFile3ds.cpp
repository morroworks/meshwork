//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwFile3ds.h"

MwFile3ds::MwFile3ds(void)
{
	this->keyFrames = 0;
	this->hierarchy = 0;
}


MwFile3ds::~MwFile3ds(void)
{
	for (int i = 0; i < this->objects.count; i++)
		delete this->objects[i];

	for (int i = 0; i < this->materials.count; i++)
		delete this->materials[i];

	if (this->keyFrames != 0)
		delete this->keyFrames;

	if (this->hierarchy != 0)
		delete this->hierarchy;
}


bool MwFile3ds::Read(MwBaseStream *dataStream)
{
	this->dataStream = dataStream;
	this->mainChunkEnd = -1;

	if (this->dataStream->length - this->dataStream->position < 6)
		return false;

	if (!this->ReadChunks())
		return false;

	this->InverseAllMeshesTransformation();
	this->ArrangeHierarchy();

	return true;
}

bool MwFile3ds::ReadChunks()
{
    long long chunkStart = this->dataStream->position;
	this->currentHeader.id = this->dataStream->ReadUInt16();
    this->currentHeader.length = this->dataStream->ReadInt32();
	switch (this->currentHeader.id)
    {
        case MwFile3ds::chunk_Main:
			this->mainChunkEnd = chunkStart + this->currentHeader.length;
			break;

        case MwFile3ds::chunk_3dEditor:
            break;

        case MwFile3ds::chunk_ObjectBlock:
            this->ReadChunkObjectBlock();
            break;

        case MwFile3ds::chunk_TriangularMesh:
            this->ReadChunkTriangularMesh();
            break;

        case MwFile3ds::chunk_VerticesList:
            this->ReadChunkVerticesList();
            break;

        case MwFile3ds::chunk_FacesList:
            this->ReadChunkFacesList();
            break;

        case MwFile3ds::chunk_MeshMaterialName:
            this->ReadChunkMeshMaterialName();
            break;

        case MwFile3ds::chunk_MappingCoords:
            this->ReadChunkMappingCoords();
            break;

        case MwFile3ds::chunk_SmoothGroups:
            this->ReadChunkSmoothGroups();
            break;

        case MwFile3ds::chunk_LocalCoordSystem:
            this->ReadChunkLocalCoordSystem();
            break;

        case MwFile3ds::chunk_Light:
            this->ReadChunkLight();
            break;

        case MwFile3ds::chunk_LightColor:
            this->ReadChunkLightColor();
            break;

        case MwFile3ds::chunk_SpotLight:
            this->ReadChunkSpotLight();
            break;

        case MwFile3ds::chunk_LightOff:
            this->ReadChunkLightActive();
            break;

        case MwFile3ds::chunk_Camera:
            this->ReadChunkCamera();
            break;

        case MwFile3ds::chunk_MaterialBlock:
            this->ReadChunkMaterialBlock();
            break;

        case MwFile3ds::chunk_MaterialName:
            this->ReadChunkMaterialName();
            break;

        case MwFile3ds::chunk_AmbientColor:
            this->ReadChunkAmbientColor();
            break;

        case MwFile3ds::chunk_DiffuseColor:
            this->ReadChunkDiffuseColor();
            break;

        case MwFile3ds::chunk_SpecularColor:
            this->ReadChunkSpecularColor();
            break;

        case MwFile3ds::chunk_MaterialColor:
            this->ReadChunkMaterialColor();
            break;

        case MwFile3ds::chunk_SpecularLevel:
            this->ReadChunkSpecularLevel();
            break;

        case MwFile3ds::chunk_Glossiness:
            this->ReadChunkGlossiness();
            break;

        case MwFile3ds::chunk_AmountOf:
            this->ReadChunkAmountOf();
            break;

        case MwFile3ds::chunk_TextureMap:
            this->ReadChunkTextureMap();
            break;

        case MwFile3ds::chunk_SpecularMap:
            this->ReadChunkSpecularMap();
            break;

        case MwFile3ds::chunk_BumpMap:
            this->ReadChunkBumpMap();
            break;

        case MwFile3ds::chunk_ReflectionMap:
            this->ReadChunkReflectionMap();
            break;

        case MwFile3ds::chunk_MappingFileName:
            this->ReadChunkMappingFileName();
            break;

        case MwFile3ds::chunk_KeyFrameData:
            this->keyFrames = new MwFile3dsKeyFrames();
            break;

        case MwFile3ds::chunk_KeyFrameInfo:
            this->ReadChunkKeyframesInfo();
            break;

        case MwFile3ds::chunk_CurrentFrame:
            this->ReadChunkKeyframesCurrentFrame();
            break;

        case MwFile3ds::chunk_KeyFrameObjectNode:
        case MwFile3ds::chunk_KeyFrameCameraNode:
        case MwFile3ds::chunk_KeyFrameLightNode:
            this->currentKeyFrameObject = new MwFile3dsKeyFrameObject();
            this->keyFrames->objects.Add(this->currentKeyFrameObject);
            break;

        case MwFile3ds::chunk_KFObjectNameAndHierarchyLevel:
            this->ReadChunkKFObjectNameAndHieararchyLevel();
            break;

        case MwFile3ds::chunk_KFObjectInstanceName:
            this->ReadChunkKFObjectInstanceName();
            break;

        case MwFile3ds::chunk_KFObjectPivot:
            this->ReadChunkKFObjectPivot();
            break;

        case MwFile3ds::chunk_KFObjectPositionTrack:
            this->ReadChunkKFObjectPositionTrack();
            break;

        case MwFile3ds::chunk_KFObjectRotationTrack:
            this->ReadChunkKFObjectRoatationTrack();
            break;

        case MwFile3ds::chunk_KFObjectScalingTrack:
            this->ReadChunkKFObjectScalingTrack();
            break;

        case MwFile3ds::chunk_KFObjectID:
            this->ReadChunkKFObjectID();
            break;

        default:
			if ((this->currentHeader.length < 0) || (chunkStart + this->currentHeader.length > this->mainChunkEnd))
				return false;

			this->dataStream->Seek(chunkStart + this->currentHeader.length);
            break;
    }

	if (this->mainChunkEnd < 0)
		return false;

	if (this->dataStream->position + 6 < this->mainChunkEnd)
        return this->ReadChunks();

	return true;
}
		
void MwFile3ds::ReadChunkObjectBlock()
{
    this->currentString = this->ReadString();
}

void MwFile3ds::ReadChunkTriangularMesh()
{
    this->currentMesh = new MwFile3dsMesh();
    this->objects.Add(this->currentMesh);
    this->currentMesh->name = currentString;
}

void MwFile3ds::ReadChunkVerticesList()
{
    int numVertices = this->dataStream->ReadUInt16();
    if (this->currentMesh->numVertices == 0)
    {
        this->currentMesh->numVertices = numVertices;
        this->currentMesh->vertices = new MwFile3dsMeshVertex[this->currentMesh->numVertices];
    }

    for (int i = 0; i < this->currentMesh->numVertices; i++)
    {
        this->currentMesh->vertices[i].x = this->dataStream->ReadFloat();
        this->currentMesh->vertices[i].y = this->dataStream->ReadFloat();
        this->currentMesh->vertices[i].z = this->dataStream->ReadFloat();
    }
}

void MwFile3ds::ReadChunkFacesList()
{
    this->currentMesh->numFaces = this->dataStream->ReadUInt16();
    this->currentMesh->faces = new MwFile3dsMeshFace[this->currentMesh->numFaces];

    for (int i = 0; i < this->currentMesh->numFaces; i++)
    {
        this->currentMesh->faces[i].a = this->dataStream->ReadUInt16();
        this->currentMesh->faces[i].b = this->dataStream->ReadUInt16();
        this->currentMesh->faces[i].c = this->dataStream->ReadUInt16();
        this->currentMesh->faces[i].info = this->dataStream->ReadUInt16();
    }
}

void MwFile3ds::ReadChunkMeshMaterialName()
{
    this->currentMesh->materialName = this->ReadString();
    int numFaces = this->dataStream->ReadUInt16();
    for (int i = 0; i < numFaces; i++)
        this->dataStream->ReadInt16();
}

void MwFile3ds::ReadChunkMappingCoords()
{
    int numVertices = this->dataStream->ReadUInt16();
    if (this->currentMesh->numVertices == 0)
    {
        this->currentMesh->numVertices = numVertices;
        this->currentMesh->vertices = new MwFile3dsMeshVertex[this->currentMesh->numVertices];
    }

    for (int i = 0; i < this->currentMesh->numVertices; i++)
    {
        this->currentMesh->vertices[i].tu = this->dataStream->ReadFloat();
        this->currentMesh->vertices[i].tv = this->dataStream->ReadFloat();
    }
}

void MwFile3ds::ReadChunkSmoothGroups()
{
	int num = (this->currentHeader.length - 6) / 4;//this->currentMesh->numFaces;
    for (int i = 0; i < num; i++)
        this->currentMesh->faces[i].smoothGroups = this->dataStream->ReadUInt32();
}

void MwFile3ds::ReadChunkLocalCoordSystem()
{
    this->currentMesh->localCoordSystem._11 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._12 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._13 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._14 = 0.0f;
    this->currentMesh->localCoordSystem._21 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._22 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._23 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._24 = 0.0f;
    this->currentMesh->localCoordSystem._31 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._32 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._33 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._34 = 0.0f;
    this->currentMesh->localCoordSystem._41 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._42 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._43 = this->dataStream->ReadFloat();
    this->currentMesh->localCoordSystem._44 = 1.0f;
}

void MwFile3ds::ReadChunkLight()
{
    this->currentLight = new MwFile3dsLight();
    this->objects.Add(this->currentLight);
    this->currentLight->name = this->currentString;

    this->currentLight->position.x = this->dataStream->ReadFloat();
    this->currentLight->position.y = this->dataStream->ReadFloat();
    this->currentLight->position.z = this->dataStream->ReadFloat();

    numLights++;
}

void MwFile3ds::ReadChunkLightColor()
{
    this->currentLight->color.r = this->dataStream->ReadFloat();
    this->currentLight->color.g = this->dataStream->ReadFloat();
    this->currentLight->color.b = this->dataStream->ReadFloat();
}

void MwFile3ds::ReadChunkSpotLight()
{
    this->currentLight->spotlight_Target.x = this->dataStream->ReadFloat();
    this->currentLight->spotlight_Target.y = this->dataStream->ReadFloat();
    this->currentLight->spotlight_Target.z = this->dataStream->ReadFloat();
    this->currentLight->spotlight_Hotspot = this->dataStream->ReadFloat();
    this->currentLight->spotlight_Falloff = this->dataStream->ReadFloat();
    this->currentLight->spotLight = true;
}

void MwFile3ds::ReadChunkLightActive()
{
	this->currentLight->active = this->dataStream->ReadBool();
}

void MwFile3ds::ReadChunkCamera()
{
    this->currentCamera = new MwFile3dsCamera();
    this->objects.Add(this->currentCamera);
    this->currentCamera->name = currentString;

    this->currentCamera->position.x = this->dataStream->ReadFloat();
    this->currentCamera->position.y = this->dataStream->ReadFloat();
    this->currentCamera->position.z = this->dataStream->ReadFloat();
    this->currentCamera->target.x = this->dataStream->ReadFloat();
    this->currentCamera->target.y = this->dataStream->ReadFloat();
    this->currentCamera->target.z = this->dataStream->ReadFloat();
    this->currentCamera->bank = this->dataStream->ReadFloat();
    this->currentCamera->lens = this->dataStream->ReadFloat();
}

void MwFile3ds::ReadChunkMaterialBlock()
{
    this->currentMaterial = new MwFile3dsMaterial();
    this->materials.Add(this->currentMaterial);
}

void MwFile3ds::ReadChunkMaterialName()
{
    this->currentMaterial->name = this->ReadString();
}

void MwFile3ds::ReadChunkAmbientColor()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_AmbientColor;
    this->currentMaterial->hasAmbient = true;
}

void MwFile3ds::ReadChunkDiffuseColor()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_DiffuseColor;
    this->currentMaterial->hasDiffuse = true;
}

void MwFile3ds::ReadChunkSpecularColor()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_SpecularColor;
    this->currentMaterial->hasSpecular = true;
}

void MwFile3ds::ReadChunkMaterialColor()
{
    MwFile3dsColorByte color;
    color.r = this->dataStream->ReadUInt8();
    color.g = this->dataStream->ReadUInt8();
    color.b = this->dataStream->ReadUInt8();

    switch (this->currentMaterialParameter)
    {
        case MwFile3dsMaterialParameter_AmbientColor:
            this->currentMaterial->ambient = color;
            break;

        case MwFile3dsMaterialParameter_DiffuseColor:
            this->currentMaterial->diffuse = color;
            break;

        case MwFile3dsMaterialParameter_SpecularColor:
            this->currentMaterial->specular = color;
            break;
    }
}

void MwFile3ds::ReadChunkSpecularLevel()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_SpecularLevel;
}

void MwFile3ds::ReadChunkGlossiness()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_Glossiness;
}

void MwFile3ds::ReadChunkAmountOf()
{
    int amountOf;
    amountOf = this->dataStream->ReadInt16();

    switch (this->currentMaterialParameter)
    {
        case MwFile3dsMaterialParameter_SpecularLevel:
            this->currentMaterial->specularLevel = amountOf / 100.0f;
            break;

        case MwFile3dsMaterialParameter_Glossiness:
            this->currentMaterial->glossiness = (float)amountOf;
            break;
    }
}

void MwFile3ds::ReadChunkTextureMap()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_TextureMap;
}

void MwFile3ds::ReadChunkSpecularMap()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_SpecularMap;
}

void MwFile3ds::ReadChunkBumpMap()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_BumpMap;
}

void MwFile3ds::ReadChunkReflectionMap()
{
    this->currentMaterialParameter = MwFile3dsMaterialParameter_ReflectionMap;
}

void MwFile3ds::ReadChunkMappingFileName()
{
    switch (this->currentMaterialParameter)
    {
        case MwFile3dsMaterialParameter_TextureMap:
            this->currentMaterial->colorMap = this->ReadString();
            break;

        case MwFile3dsMaterialParameter_SpecularMap:
            this->currentMaterial->specularMap = this->ReadString();
            break;

        case MwFile3dsMaterialParameter_BumpMap:
            this->currentMaterial->bumpMap = this->ReadString();
            break;

        case MwFile3dsMaterialParameter_ReflectionMap:
            this->currentMaterial->reflectionMap = this->ReadString();
            break;

        default:
            this->ReadString();
            break;
    }
}



void MwFile3ds::ReadChunkKeyframesInfo()
{
    this->keyFrames->start = this->dataStream->ReadInt32();
    this->keyFrames->end = this->dataStream->ReadInt32();
}

void MwFile3ds::ReadChunkKeyframesCurrentFrame()
{
    this->keyFrames->current = this->dataStream->ReadInt32() / 160;
}

void MwFile3ds::ReadChunkKFObjectNameAndHieararchyLevel()
{
    this->currentKeyFrameObject->name = ReadString();
    this->currentKeyFrameObject->instanceName = this->currentKeyFrameObject->name;
	this->dataStream->Seek(2 * 2,  StreamSeekMode_Relative);
    this->currentKeyFrameObject->hierarchyLevel = this->dataStream->ReadInt16();
}

void MwFile3ds::ReadChunkKFObjectInstanceName()
{
    this->currentKeyFrameObject->instanceName = ReadString();
}

void MwFile3ds::ReadChunkKFObjectPivot()
{
    this->currentKeyFrameObject->pivot.x = this->dataStream->ReadFloat();
    this->currentKeyFrameObject->pivot.y = this->dataStream->ReadFloat();
    this->currentKeyFrameObject->pivot.z = this->dataStream->ReadFloat();
}

void MwFile3ds::ReadChunkKFObjectPositionTrack()
{
    this->currentKeyFrameObject->position = new MwFile3dsKeyFramesTrack();

    ReadKeyFrameTrackHeader(this->currentKeyFrameObject->position);

	for (int i = 0; i < this->currentKeyFrameObject->position->keys; i++)
    {
        MwFile3dsKeyFramePosition *keyFrame = new MwFile3dsKeyFramePosition();
        ReadKeyFrameParams(keyFrame);

        keyFrame->position.x = this->dataStream->ReadFloat();
        keyFrame->position.y = this->dataStream->ReadFloat();
        keyFrame->position.z = this->dataStream->ReadFloat();

        this->currentKeyFrameObject->position->data.Add(keyFrame);
    }
}

void MwFile3ds::ReadChunkKFObjectRoatationTrack()
{
    this->currentKeyFrameObject->rotation = new MwFile3dsKeyFramesTrack();

    ReadKeyFrameTrackHeader(this->currentKeyFrameObject->rotation);

    for (int i = 0; i < this->currentKeyFrameObject->rotation->keys; i++)
    {
        MwFile3dsKeyFrameRotation *keyFrame = new MwFile3dsKeyFrameRotation();
        ReadKeyFrameParams(keyFrame);

        keyFrame->angle = this->dataStream->ReadFloat();
        keyFrame->axis.x = this->dataStream->ReadFloat();
        keyFrame->axis.y = this->dataStream->ReadFloat();
        keyFrame->axis.z = this->dataStream->ReadFloat();

        this->currentKeyFrameObject->rotation->data.Add(keyFrame);
    }
}

void MwFile3ds::ReadChunkKFObjectScalingTrack()
{
    this->currentKeyFrameObject->scaling = new MwFile3dsKeyFramesTrack();

    ReadKeyFrameTrackHeader(this->currentKeyFrameObject->scaling);

    for (int i = 0; i < this->currentKeyFrameObject->scaling->keys; i++)
    {
        MwFile3dsKeyFrameScaling *keyFrame = new MwFile3dsKeyFrameScaling();
        ReadKeyFrameParams(keyFrame);

        keyFrame->scaling.x = this->dataStream->ReadFloat();
        keyFrame->scaling.y = this->dataStream->ReadFloat();
        keyFrame->scaling.z = this->dataStream->ReadFloat();

		this->currentKeyFrameObject->scaling->data.Add(keyFrame);
    }
}

void MwFile3ds::ReadChunkKFObjectID()
{
    this->currentKeyFrameObject->id = this->dataStream->ReadUInt16();
}


// Helper methods

MwString MwFile3ds::ReadString()
{
    MwString result;
    char c;
	for (;;)
	{
		c = this->dataStream->ReadUInt8();

        if (c != 0)
			result += c;
		else
			break;
    }

    return MwString(result);
}

void MwFile3ds::ReadKeyFrameTrackHeader(MwFile3dsKeyFramesTrack *track)
{
	track->flags = this->dataStream->ReadUInt16();
	this->dataStream->Seek(2 * 4, StreamSeekMode_Relative);
    track->keys = this->dataStream->ReadInt32();
}

void MwFile3ds::ReadKeyFrameParams(MwFile3dsKeyFrameBase *keyFrame)
{
    keyFrame->frameNumber = this->dataStream->ReadInt32();

    keyFrame->flags = this->dataStream->ReadUInt16();

    if ((keyFrame->flags & 0x00000001) != 0)
        keyFrame->tension = this->dataStream->ReadFloat();
    if ((keyFrame->flags & 0x00000002) != 0)
        keyFrame->continuity = this->dataStream->ReadFloat();
    if ((keyFrame->flags & 0x00000004) != 0)
        keyFrame->bias = this->dataStream->ReadFloat();
    if ((keyFrame->flags & 0x00000008) != 0)
        keyFrame->easeTo = this->dataStream->ReadFloat();
    if ((keyFrame->flags & 0x00000010) != 0)
        keyFrame->easeFrom = this->dataStream->ReadFloat();
}

void MwFile3ds::InverseAllMeshesTransformation()
{
    int count = this->objects.count;
    for (int i = 0; i < count; i++)
		if (this->objects[i]->objectType == MwFile3dsObjectType_Mesh)
			((MwFile3dsMesh*)this->objects[i])->InverseTransformation();
}

MwFile3dsBaseObject *MwFile3ds::FindObject(MwString name)
{
	int count = this->objects.count;
    for (int i = 0; i < count; i++)
		if (this->objects[i]->name.Equals(name))
            return objects[i];

    return 0;
}

int MwFile3ds::FindParent(int child)
{
    for (int i = child; i >= 0; i--)
		if (this->keyFrames->objects[i]->hierarchyLevel < this->keyFrames->objects[child]->hierarchyLevel)
            return i;
    return -1;
}

void MwFile3ds::BuildHierarchyFromResources()
{
    for (int i = 0; i < this->objects.count; i++)
	{
		MwFile3dsBaseObject *fileObject = this->objects[i];
		if (fileObject->objectType == MwFile3dsObjectType_Mesh)
		{
			MwFile3dsKeyFrameObject *keyFrame = new MwFile3dsKeyFrameObject();
			keyFrame->name = fileObject->name;
			keyFrame->id = 0;
			keyFrame->hierarchyLevel = -1;
			keyFrame->position = new MwFile3dsKeyFramesTrack();
			keyFrame->rotation = new MwFile3dsKeyFramesTrack();
			keyFrame->scaling = new MwFile3dsKeyFramesTrack();
			this->hierarchy->Add(new MwFile3dsHierarchyNode(fileObject, keyFrame));
		}
	}
}

void MwFile3ds::ArrangeHierarchyObject(int hierarchyLevel, MwFile3dsHierarchy *hierarchy)
{
    if (this->hierarchyIndex < this->keyFrames->objects.count)
        if (this->keyFrames->objects[this->hierarchyIndex]->hierarchyLevel < hierarchyLevel)
            return;

    if (this->hierarchyIndex < this->keyFrames->objects.count)
        if (this->keyFrames->objects[this->hierarchyIndex]->hierarchyLevel > hierarchyLevel)
        {
            MwFile3dsHierarchyNode *child = new MwFile3dsHierarchyNode(this->FindObject(this->keyFrames->objects[this->hierarchyIndex]->name), this->keyFrames->objects[this->hierarchyIndex]);
            (*hierarchy)[hierarchy->count - 1]->children->Add(child);

            this->hierarchyIndex++;
            this->ArrangeHierarchyObject(this->keyFrames->objects[this->hierarchyIndex - 1]->hierarchyLevel, (*hierarchy)[hierarchy->count - 1]->children);
        }

    if (this->hierarchyIndex < this->keyFrames->objects.count)
        if (this->keyFrames->objects[this->hierarchyIndex]->hierarchyLevel == hierarchyLevel)
        {
            MwFile3dsHierarchyNode *child = new MwFile3dsHierarchyNode(this->FindObject(this->keyFrames->objects[this->hierarchyIndex]->name), this->keyFrames->objects[this->hierarchyIndex]);
            hierarchy->Add(child);

            this->hierarchyIndex++;
            this->ArrangeHierarchyObject(this->keyFrames->objects[this->hierarchyIndex - 1]->hierarchyLevel, hierarchy);
        }
}

void MwFile3ds::ArrangeHierarchy()
{
    this->hierarchy = new MwFile3dsHierarchy(0);

    if (this->keyFrames == 0)
        this->BuildHierarchyFromResources();
    else
        if (this->keyFrames->objects.count == 0)
            this->BuildHierarchyFromResources();
        else
        {
            this->hierarchyIndex = 0;
            this->ArrangeHierarchyObject(-1, this->hierarchy);
        }
}