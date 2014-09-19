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

#include "Mw3dsScene.h"

#include "..\..\..\Engine\Meshwork.h"

#include "..\..\..\Engine\Utilities\MwMaths.h"
#include "..\..\..\Engine\Utilities\SmoothGrouping\MwSmoothGrouping.h"
#include "..\..\..\Tools\MwMath.h"

#include "..\..\..\Engine\Entities\Mechanisms\MwKeyframeAnimationMechanism.h"
#include "..\..\..\Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameScaling.h"
#include "..\..\..\Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameRotationAxis.h"
#include "..\..\..\Engine\Entities\Mechanisms\KeyFrameAnimation\MwKeyFrameTranslation.h"

Mw3dsScene::Mw3dsScene(void)
{
}


Mw3dsScene::~Mw3dsScene(void)
{
	for (int i = 0; i < this->materialMapping.count; i++)
		delete this->materialMapping[i].name3ds;

	for (int i = 0; i < this->resourceMapping.count; i++)
		delete this->resourceMapping[i].name3ds;
}

bool Mw3dsScene::Load(MwBaseStream &source)
{
	MwFile3ds file3ds;
	if (!file3ds.Read(&source))
		return false;

    for (int materialIndex = 0; materialIndex < file3ds.materials.count; materialIndex++)
    {
		this->LoadMaterialResource(file3ds.materials[materialIndex]);
	}

	for (int objectIndex = 0; objectIndex < file3ds.objects.count; objectIndex++)
	{
		if (file3ds.objects[objectIndex]->objectType == MwFile3dsObjectType_Mesh)
			this->LoadMeshResource((MwFile3dsMesh*)file3ds.objects[objectIndex]);

		if (file3ds.objects[objectIndex]->objectType == MwFile3dsObjectType_Camera)
			this->LoadCameraResource((MwFile3dsCamera*)file3ds.objects[objectIndex]);

		if (file3ds.objects[objectIndex]->objectType == MwFile3dsObjectType_Light)
			this->LoadLightResource((MwFile3dsLight*)file3ds.objects[objectIndex]);
	}

	this->BuildSceneHierarchy(this->context->root, file3ds.hierarchy);

	for (int i = 0; i < this->context->resources.count; i++)
	{
		MwBaseResource *resource = this->context->resources[i];
		if (dynamic_cast<MwMaterial*>(resource) != 0)
        {
            ((MwMaterial*)resource)->CommitRenderStates();
        }
	}


	return true;
}

bool Mw3dsScene::Save(MwBaseStream &destination, const char *format)
{
	return false;
}

MwBaseResource *Mw3dsScene::CreateResourceAndMapping(MwString name3ds, MwBaseResource *resource)
{
	this->context->AddResource(*resource);

	resource->name = this->context->AcquireResourceName(name3ds, resource->resourceType);

	Mw3dsSceneNameResourceMapping mapping;
	mapping.name3ds = new MwString(name3ds);
	mapping.resource = resource;
	this->resourceMapping.Add(mapping);

	return resource;
}

MwBaseResource *Mw3dsScene::FindResourceMapping(const MwString &name3ds)
{
	for (int i = 0; i < this->resourceMapping.count; i++)
		if (this->resourceMapping[i].name3ds->Equals(name3ds))
			return this->resourceMapping[i].resource;

	return 0;
}


MwBaseResource *Mw3dsScene::CreateMaterialAndMapping(MwString name3ds, MwBaseResource *material)
{
	this->context->AddResource(*material);

	material->name = this->context->AcquireResourceName(name3ds, material->resourceType);

	Mw3dsSceneNameResourceMapping mapping;
	mapping.name3ds = new MwString(name3ds);
	mapping.resource = material;
	this->materialMapping.Add(mapping);

	return material;
}

MwBaseResource *Mw3dsScene::FindMaterialMapping(const MwString &name3ds)
{
	for (int i = 0; i < this->materialMapping.count; i++)
		if (this->materialMapping[i].name3ds->Equals(name3ds))
			return this->materialMapping[i].resource;

	return 0;
}

void Mw3dsScene::LoadMaterialResource(MwFile3dsMaterial *material3ds)
{
	MwMaterial *material = (MwMaterial*)this->CreateMaterialAndMapping(material3ds->name, new MwMaterial(*this->context));

    material->AddShaderSlot(MwShaderOperation_Material, MwColorOperation_None);

	material->GetProperty("Ambient")->SetColor(MwVector4((float)material3ds->ambient.r / (float)0xff,
														 (float)material3ds->ambient.g / (float)0xff,
														 (float)material3ds->ambient.b / (float)0xff,
														 1.0f));
    material->GetProperty("Diffuse")->SetColor(MwVector4((float)material3ds->diffuse.r / (float)0xff,
														 (float)material3ds->diffuse.g / (float)0xff,
														 (float)material3ds->diffuse.b / (float)0xff,
														 1.0f));
	material->GetProperty("Specular")->SetColor(MwVector4((float)material3ds->specular.r / (float)0xff,
														  (float)material3ds->specular.g / (float)0xff,
														  (float)material3ds->specular.b / (float)0xff,
														  1.0f));
	material->GetProperty("Gloss")->SetFloat(material3ds->glossiness);

    //for (ii = 0; ii < objectsCount; ii++)
    //    if (file3ds.objects[ii] is FileTypes.file3ds.Light)
    //        material->AddShaderSlot(MwShaderOperation.LightSource, MwColorOperation.None);

	material->AddShaderSlot(MwShaderOperation_LightSource, MwColorOperation_None);
	material->AddShaderSlot(MwShaderOperation_LightSource, MwColorOperation_None);

	if (material3ds->bumpMap.length != 0)
    {
		MwTexture2D *texture = this->context->AcquireTexture(MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, material3ds->bumpMap));

		material->AddShaderSlot(MwShaderOperation_NormalMap, MwColorOperation_None);
		material->AddShaderSlot(MwShaderOperation_PixelLighting, MwColorOperation_Set);

		material->GetProperty("Normal Map")->SetReference(MwParameterType_ReferenceTexture, texture);
    }
    else
        material->AddShaderSlot(MwShaderOperation_VertexLighting, MwColorOperation_Set);


    if (material3ds->colorMap.length != 0)
    {
		MwTexture2D *texture = this->context->AcquireTexture(MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, material3ds->colorMap));

        material->AddShaderSlot(MwShaderOperation_ColorMap, MwColorOperation_Modulate);

        material->GetProperty("Color Map")->SetReference(MwParameterType_ReferenceTexture, texture);
    }

	if (material3ds->reflectionMap.length != 0)
    {
		MwTexture2D *texture = this->context->AcquireTexture(MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, material3ds->reflectionMap));

        material->AddShaderSlot(MwShaderOperation_EnvMap, MwColorOperation_Add);

        material->GetProperty("Reflection Map")->SetReference(MwParameterType_ReferenceTexture, texture);
    }

    if (material3ds->specularMap.length != 0)
    {
        /*
        MwTexture texture = AddTextureResource(filePath + file3ds.materials[i].specularMap);
        texture.name = file3ds.materials[i].specularMap;

        material->parametersList.Add(new MwMaterialParameter("Normal Map", "normalMap", MwMaterialParameterType.Texture, texture));

        dShader.AddShaderSlot(MwShaderOperation.ColorMap, MwColorOperation.Modulate);
        */
    }

	material->UpdateShader();
}

void Mw3dsScene::LoadMeshResource(MwFile3dsMesh *mesh3ds)
{
	MwMesh *mesh = (MwMesh*)this->CreateResourceAndMapping(mesh3ds->name, new MwMesh(*this->context));

	MwSmoothGrouping smoothGrouping(mesh3ds->numFaces, mesh3ds->numVertices);
	for (int i = 0; i < mesh3ds->numFaces; i++)
	{
		smoothGrouping.SetFaceSmoothingGroups(i, mesh3ds->faces[i].smoothGroups);
		smoothGrouping.AddFaceVertex(i, mesh3ds->faces[i].a);
		smoothGrouping.AddFaceVertex(i, mesh3ds->faces[i].b);
		smoothGrouping.AddFaceVertex(i, mesh3ds->faces[i].c);
	}


	int numVertices = smoothGrouping.vertexIndices.count;
	mesh->deviceMesh->CreateVertexBuffer(numVertices);
	for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++)
	{
		int index = smoothGrouping.vertexIndices[vertexIndex].index;

		mesh->deviceMesh->SetVertexPosition(vertexIndex, MwVector3(-mesh3ds->vertices[index].x, mesh3ds->vertices[index].z, mesh3ds->vertices[index].y));
		mesh->deviceMesh->SetVertexTexCoords(vertexIndex, MwVector2(mesh3ds->vertices[index].tu, mesh3ds->vertices[index].tv));
	}

	int numTriangles = smoothGrouping.faces.count;
	mesh->deviceMesh->CreateIndexBuffer(numTriangles * 3);
	int index = 0;
	for (int faceIndex = 0; faceIndex < numTriangles; faceIndex++)
	{
		mesh->deviceMesh->SetIndex(index++, smoothGrouping.faces[faceIndex].indices[1]);
		mesh->deviceMesh->SetIndex(index++, smoothGrouping.faces[faceIndex].indices[0]);
		mesh->deviceMesh->SetIndex(index++, smoothGrouping.faces[faceIndex].indices[2]);
	}

	mesh->ComputeNormals();
	mesh->ComputeBounds();

	mesh->deviceMesh->UpdateVertices(0, numVertices);
	mesh->deviceMesh->UpdateIndices(0, numTriangles * 3);
}

void Mw3dsScene::LoadLightResource(MwFile3dsLight *light3ds)
{
	MwLight *light = (MwLight*)this->CreateResourceAndMapping(light3ds->name, new MwLight());
	light->name = this->context->AcquireResourceName(light3ds->name, MwResourceType_Light);
	light->properties[MwLight::propertyIndex_Active]->SetBool(light3ds->active);
	light->properties[MwLight::propertyIndex_Color]->SetColor(MwVector4(light3ds->color.r, light3ds->color.g, light3ds->color.b, 1.0f));
	light->properties[MwLight::propertyIndex_Intensity]->SetFloat(500.0f);
}

void Mw3dsScene::LoadCameraResource(MwFile3dsCamera *camera3ds)
{
	MwCamera *camera = (MwCamera*)this->CreateResourceAndMapping(camera3ds->name, new MwCamera(this->context));

	camera->name = this->context->AcquireResourceName(camera3ds->name, MwResourceType_Camera);
	camera->properties[MwCamera::propertyIndex_FOV]->SetFloat(MwMaths::LensToFOV(camera3ds->lens));
	//camera->orthoZoom = (float)this->context->
}

void Mw3dsScene::BuildSceneHierarchyNode(MwEntitySet *branch, MwFile3dsHierarchyNode *hierarchyNode3ds, MwLinearMechanism *animationFrame)
{
	branch->name = this->context->AcquireResourceName(hierarchyNode3ds->keyFrames->instanceName, MwResourceType_EntitySet);

	MwTransform *transformation = (MwTransform*)this->context->AddResource(*new MwTransform());
	transformation->name = this->context->AcquireResourceName(hierarchyNode3ds->keyFrames->instanceName, MwResourceType_Transform);
    branch->references.Add(transformation);

	if (!hierarchyNode3ds->isDummy)
    {
		if (hierarchyNode3ds->obj->objectType == MwFile3dsObjectType_Mesh)
        {
			MwFile3dsMesh *mesh3ds = (MwFile3dsMesh*)hierarchyNode3ds->obj;

			MwBaseResource *material = this->FindMaterialMapping(mesh3ds->materialName);
            if (material != 0)
                branch->references.Add(material);

			MwBaseResource *mesh = this->FindResourceMapping(mesh3ds->name);
            if (mesh != 0)
                branch->references.Add(mesh);
        }

		if (hierarchyNode3ds->obj->objectType == MwFile3dsObjectType_Light)
		{
			MwFile3dsLight *light3ds = (MwFile3dsLight*)hierarchyNode3ds->obj;

			MwBaseResource *light = this->FindResourceMapping(light3ds->name);
            if (light != 0)
                branch->references.Add(light);
		}

		if (hierarchyNode3ds->obj->objectType == MwFile3dsObjectType_Camera)
        {
			MwFile3dsCamera *camera3ds = (MwFile3dsCamera*)hierarchyNode3ds->obj;
			MwBaseResource *camera = this->FindResourceMapping(camera3ds->name);
			if (camera != 0)
			{
				// Use position and target coordinates to set up camera's orientation, and if there are no keyframes - its position. MwCamera looks towards its local positive Z direction (its orientation origin)
				MwVector3 position(-camera3ds->position.x, camera3ds->position.z, camera3ds->position.y);
				MwVector3 target(-camera3ds->target.x, camera3ds->target.z, camera3ds->target.y);
				if ((hierarchyNode3ds->keyFrames != 0) && (hierarchyNode3ds->keyFrames->position != 0))
				{
					MwVector3 orientationVector;
					MwVector3::Subtract(orientationVector, target, position);
					MwMatrix::CreateOrientation(transformation->manual, orientationVector, MwVector3(0.0f, 0.0f, 1.0f)); // Get only orientation from position and target
				}
				else
					MwMatrix::CreateOrientedPosition(transformation->manual, position, target, MwVector3(0.0f, 0.0f, 1.0f)); // Get both position and orientation
				
				MwTransform *identityTransform = (MwTransform*)this->context->FindResourceX("Identity Transform", MwResourceType_Transform);
				if (identityTransform == 0)
				{
					identityTransform = (MwTransform*)this->context->AddResource(*new MwTransform());
					identityTransform->name = "Identity Transform";
				}

				branch->references.Add(camera);

				branch->references.Add(identityTransform);
			}
        }
    }


    if (hierarchyNode3ds->keyFrames != 0)
    {
        transformation->pivot._41 = hierarchyNode3ds->keyFrames->pivot.x;
        transformation->pivot._42 = -hierarchyNode3ds->keyFrames->pivot.z;
        transformation->pivot._43 = -hierarchyNode3ds->keyFrames->pivot.y;

        bool useKeyframes = false;
        if (hierarchyNode3ds->keyFrames->scaling != 0)
            if (hierarchyNode3ds->keyFrames->scaling->keys > 1)
                useKeyframes = true;

        if (hierarchyNode3ds->keyFrames->rotation != 0)
            if (hierarchyNode3ds->keyFrames->rotation->keys > 1)
                useKeyframes = true;

        if (hierarchyNode3ds->keyFrames->position != 0)
            if (hierarchyNode3ds->keyFrames->position->keys > 1)
                useKeyframes = true;

        if (!useKeyframes)
        {
            if (hierarchyNode3ds->keyFrames->scaling != 0)
			{
				MwMatrix scaling;
				MwMatrix::CreateScale(scaling, ((MwFile3dsKeyFrameScaling*)hierarchyNode3ds->keyFrames->scaling->data[0])->scaling.x,
												((MwFile3dsKeyFrameScaling*)hierarchyNode3ds->keyFrames->scaling->data[0])->scaling.z,
												((MwFile3dsKeyFrameScaling*)hierarchyNode3ds->keyFrames->scaling->data[0])->scaling.y);
				MwMatrix::Multiply(transformation->manual, transformation->manual, scaling);
			}
            if (hierarchyNode3ds->keyFrames->rotation != 0)
			{
                MwMatrix rotation;
				MwMatrix::CreateRotationAxis(rotation, -((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[0])->axis.x,
														((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[0])->axis.z,
														((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[0])->axis.y,
														((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[0])->angle);
				MwMatrix::Multiply(transformation->manual, transformation->manual, rotation);
			}
            if (hierarchyNode3ds->keyFrames->position != 0)
			{
				MwMatrix translation;
				MwMatrix::CreateTranslation(translation, -((MwFile3dsKeyFramePosition*)hierarchyNode3ds->keyFrames->position->data[0])->position.x,
                                                          ((MwFile3dsKeyFramePosition*)hierarchyNode3ds->keyFrames->position->data[0])->position.z,
                                                          ((MwFile3dsKeyFramePosition*)hierarchyNode3ds->keyFrames->position->data[0])->position.y);
				MwMatrix::Multiply(transformation->manual, transformation->manual, translation);
			}
        }

        else
        {
			MwKeyframeAnimationMechanism *keyFrames = (MwKeyframeAnimationMechanism*)this->context->AddResource(*new MwKeyframeAnimationMechanism(this->context));
			keyFrames->name = this->context->AcquireResourceName(hierarchyNode3ds->keyFrames->instanceName + " animation", MwResourceType_Mechanism);
            branch->references.Add(keyFrames);
			keyFrames->properties[0]->SetReference(MwParameterType_ReferenceMechanism, animationFrame);
            keyFrames->properties[1]->SetReference(MwParameterType_ReferenceTransform, transformation);

            if (hierarchyNode3ds->keyFrames->scaling != 0)
            {
				MwKeyFramesTrack *scalingTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());

                *(float*)animationFrame->properties[0]->value = MwMath::Min(*(float*)animationFrame->properties[0]->value, (float)hierarchyNode3ds->keyFrames->scaling->data[0]->frameNumber);
                *(float*)animationFrame->properties[1]->value = MwMath::Max(*(float*)animationFrame->properties[1]->value, (float)hierarchyNode3ds->keyFrames->scaling->data[hierarchyNode3ds->keyFrames->scaling->keys - 1]->frameNumber);

                for (int ii = 0; ii < hierarchyNode3ds->keyFrames->scaling->keys; ii++)
                    scalingTrack->Add(new MwKeyFrameScaling(
						(float)hierarchyNode3ds->keyFrames->scaling->data[ii]->frameNumber, MwVector3(						
							((MwFile3dsKeyFrameScaling*)hierarchyNode3ds->keyFrames->scaling->data[ii])->scaling.x,
                            ((MwFile3dsKeyFrameScaling*)hierarchyNode3ds->keyFrames->scaling->data[ii])->scaling.z,
                            ((MwFile3dsKeyFrameScaling*)hierarchyNode3ds->keyFrames->scaling->data[ii])->scaling.y)));
            }

            if (hierarchyNode3ds->keyFrames->rotation != 0)
            {
				MwKeyFramesTrack *rotationTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());

				*(float*)animationFrame->properties[0]->value = MwMath::Min(*(float*)animationFrame->properties[0]->value, (float)hierarchyNode3ds->keyFrames->rotation->data[0]->frameNumber);
                *(float*)animationFrame->properties[1]->value = MwMath::Max(*(float*)animationFrame->properties[1]->value, (float)hierarchyNode3ds->keyFrames->rotation->data[hierarchyNode3ds->keyFrames->rotation->keys - 1]->frameNumber);

                for (int ii = 0; ii < hierarchyNode3ds->keyFrames->rotation->keys; ii++)
                    rotationTrack->Add(new MwKeyFrameRotationAxis(
						(float)hierarchyNode3ds->keyFrames->rotation->data[ii]->frameNumber,
						((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[ii])->angle, MwVector3(
							-((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[ii])->axis.x,
							((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[ii])->axis.z,
							((MwFile3dsKeyFrameRotation*)hierarchyNode3ds->keyFrames->rotation->data[ii])->axis.y)));

				keyFrames->BuildRotationAxisTrack(rotationTrack);
            }

            if (hierarchyNode3ds->keyFrames->position != 0)
            {
				MwKeyFramesTrack *translationTrack = keyFrames->keyFramesTracks.Add(new MwKeyFramesTrack());

				*(float*)animationFrame->properties[0]->value = MwMath::Min(*(float*)animationFrame->properties[0]->value, (float)hierarchyNode3ds->keyFrames->position->data[0]->frameNumber);
                *(float*)animationFrame->properties[1]->value = MwMath::Max(*(float*)animationFrame->properties[1]->value, (float)hierarchyNode3ds->keyFrames->position->data[hierarchyNode3ds->keyFrames->position->keys - 1]->frameNumber);

                for (int ii = 0; ii < hierarchyNode3ds->keyFrames->position->keys; ii++)
                    translationTrack->Add(new MwKeyFrameTranslation(
						(float)hierarchyNode3ds->keyFrames->position->data[ii]->frameNumber, MwVector3(
							-((MwFile3dsKeyFramePosition*)hierarchyNode3ds->keyFrames->position->data[ii])->position.x,
							((MwFile3dsKeyFramePosition*)hierarchyNode3ds->keyFrames->position->data[ii])->position.z,
							((MwFile3dsKeyFramePosition*)hierarchyNode3ds->keyFrames->position->data[ii])->position.y)));
            }
        }
    }
}

void Mw3dsScene::BuildSceneHierarchy(MwEntitySet *branch, MwFile3dsHierarchy *hierarchy3ds, MwLinearMechanism *animationFrame)
{
	// First cameras in the given branch
	for (int i = 0; i < hierarchy3ds->count; i++)
    {
		MwFile3dsHierarchyNode *hierarchyNode3ds = (*hierarchy3ds)[i];

		if (animationFrame == 0)
		{
			animationFrame = (MwLinearMechanism*)this->context->AddResource(*new MwLinearMechanism(0, 100, 30, false));
			animationFrame->name = this->context->AcquireResourceName(hierarchyNode3ds->keyFrames->instanceName + " frame", MwResourceType_Mechanism);
			branch->references.Add(animationFrame);
		}

		bool isCamera = (hierarchyNode3ds->obj != 0) && (hierarchyNode3ds->obj->objectType == MwFile3dsObjectType_Camera);
		if (isCamera)
		{
			this->BuildSceneHierarchyNode(branch, hierarchyNode3ds, animationFrame);
		}
    }

	// Next, other objects, each in its sub-branch
	for (int i = 0; i < hierarchy3ds->count; i++)
    {
		MwFile3dsHierarchyNode *hierarchyNode3ds = (*hierarchy3ds)[i];

		bool isCamera = (hierarchyNode3ds->obj != 0) && (hierarchyNode3ds->obj->objectType == MwFile3dsObjectType_Camera);
		if (!isCamera)
		{
			MwEntitySet *subBranch = (MwEntitySet*)this->context->AddResource(*new MwEntitySet());

			this->BuildSceneHierarchyNode(subBranch, hierarchyNode3ds, animationFrame);

			if (hierarchyNode3ds->children->count > 0)
				this->BuildSceneHierarchy(subBranch, hierarchyNode3ds->children, animationFrame);

			branch->references.Add(subBranch);
		}

    }
}