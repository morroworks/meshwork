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

#include "MwObjScene.h"

#include "FileObj\MwFileObj.h"

#include "..\..\..\Engine\Utilities\SmoothGrouping\MwSmoothGrouping.h"

MwObjScene::MwObjScene(void)
{
}


MwObjScene::~MwObjScene(void)
{
}

bool MwObjScene::Load(MwBaseStream &source)
{
	MwFileObj fileObj;

	MwDictionary<MwString, MwBaseResource*> resourceMapping;

	if (!fileObj.Read(&source))
		return false;

	for (int i = 0; i < fileObj.materialFiles.count; i++)
	{
		MwBaseStream *materialFile = this->context->fileSystem->OpenFile(MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, fileObj.materialFiles[i]));
		if (materialFile != 0)
			fileObj.Read(materialFile);
		delete materialFile;
	}

	for (int materialIndex = 0; materialIndex < fileObj.materials.count; materialIndex++)
	{
		MwMaterial *material = this->LoadMaterialResource(fileObj.materials[materialIndex]);
		resourceMapping.Add(fileObj.materials[materialIndex]->name, material);
	}

	if (fileObj.meshes.count > 0)
	{
		MwEntitySet *parentSet = (MwEntitySet*)((MwEntitySet*)this->context->root)->references.Add(this->context->AddResource(*new MwEntitySet()));
		parentSet->name = this->context->AcquireResourceName(this->context->serializationParameters.friendlyName, parentSet->resourceType);

		MwBaseResource *lastMeshMaterial = 0;
		for (int meshIndex = 0; meshIndex < fileObj.meshes.count; meshIndex++)
		{
			MwMesh *mesh = this->LoadMeshResource(fileObj.meshes[meshIndex]);
	
			MwBaseResource *meshMaterial;
			if (resourceMapping.GetValue(fileObj.meshes[meshIndex]->materialName, meshMaterial))
			{
				if (meshMaterial != lastMeshMaterial)
				{
					parentSet->references.Add(meshMaterial);
					lastMeshMaterial = meshMaterial;
				}
			}

			parentSet->references.Add(mesh);
		}
	}

	return true;
}

bool MwObjScene::Save(MwBaseStream &destination, const char *format)
{
	return false;
}

MwMesh *MwObjScene::LoadMeshResource(MwFileObjMesh* meshObj)
{
	MwMesh *mesh = (MwMesh*)this->context->AddResource(*new MwMesh(*this->context));
	mesh->name = this->context->AcquireResourceName(meshObj->name, mesh->resourceType);

	meshObj->CreateBuffers();

	MwSmoothGrouping smoothGrouping(meshObj->bufferedFaces.count, meshObj->bufferedVertices.count);
	for (int faceIndex = 0; faceIndex < meshObj->faces.count; faceIndex++)
	{
		smoothGrouping.SetFaceSmoothingGroups(faceIndex, meshObj->bufferedFaces.Get(faceIndex)->smoothingGroups);
		for (int faceVertexIndex = 0; faceVertexIndex < meshObj->faces[faceIndex]->vertices.count; faceVertexIndex++)
			smoothGrouping.AddFaceVertex(faceIndex, meshObj->bufferedFaces.Get(faceIndex)->bufferedVertexIndices.Get(faceVertexIndex));
	}

	int numVertices = smoothGrouping.vertexIndices.count;
	mesh->deviceMesh->CreateVertexBuffer(numVertices);
	for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++)
	{
		
		MwFileObjFaceVertex *vertexObj = &meshObj->bufferedVertices[smoothGrouping.vertexIndices[vertexIndex].index];

		if (vertexObj->vertexIndex != -1)
			mesh->deviceMesh->SetVertexPosition(vertexIndex, MwVector3(meshObj->vertices[vertexObj->vertexIndex].x, meshObj->vertices[vertexObj->vertexIndex].y, meshObj->vertices[vertexObj->vertexIndex].z));

		if (vertexObj->texCoordIndex != -1)
			mesh->deviceMesh->SetVertexTexCoords(vertexIndex, MwVector2(meshObj->texCoords[vertexObj->texCoordIndex].x, meshObj->texCoords[vertexObj->texCoordIndex].y));

		if (vertexObj->normalIndex != -1)
			mesh->deviceMesh->SetVertexNormal(vertexIndex, MwVector3(meshObj->normals[vertexObj->normalIndex].x, meshObj->normals[vertexObj->normalIndex].y, meshObj->normals[vertexObj->normalIndex].z));
	}


	// Calculate the total number of triangles, given each face consists of (number of face vertices - 2) triangles, that is 1 for triangle, 2 for rectangle, 3 for pentagon and so on
	int numTriangles = 0;
	for (int i = 0; i < smoothGrouping.faces.count; i++)
		numTriangles += smoothGrouping.faces[i].indices.count - 2;

	mesh->deviceMesh->CreateIndexBuffer(numTriangles * 3);
	int index = 0;
	for (int faceIndex = 0; faceIndex < smoothGrouping.faces.count; faceIndex++)
	{
		// In case of convex polygons with any number of sides, use the first vertex to form a triangle fan with the rest vertices
		
		int zeroVertexIndex = smoothGrouping.faces[faceIndex].indices[0];
		for (int faceVertexIndex = 2; faceVertexIndex < smoothGrouping.faces[faceIndex].indices.count; faceVertexIndex++)
		{
			mesh->deviceMesh->SetIndex(index++, zeroVertexIndex);
			mesh->deviceMesh->SetIndex(index++, smoothGrouping.faces[faceIndex].indices[faceVertexIndex]);
			mesh->deviceMesh->SetIndex(index++, smoothGrouping.faces[faceIndex].indices[faceVertexIndex - 1]);
		}
	}

	mesh->ComputeNormals();
	mesh->ComputeBounds();

	mesh->deviceMesh->UpdateVertices(0, numVertices);
	mesh->deviceMesh->UpdateIndices(0, numTriangles * 3);

	return mesh;
}

MwMaterial *MwObjScene::LoadMaterialResource(MwFileObjMaterial *materialObj)
{
	MwMaterial *material = (MwMaterial*)this->context->AddResource(*new MwMaterial(*this->context));
	material->name = this->context->AcquireResourceName(materialObj->name, material->resourceType);

    material->AddShaderSlot(MwShaderOperation_Material, MwColorOperation_None);

	material->GetProperty("Ambient")->SetColor(MwVector4(materialObj->ambientColor.x,
														 materialObj->ambientColor.y,
														 materialObj->ambientColor.z,
														 1.0f));
    material->GetProperty("Diffuse")->SetColor(MwVector4(materialObj->diffuseColor.x,
														 materialObj->diffuseColor.y,
														 materialObj->diffuseColor.z,
														 1.0f));
	material->GetProperty("Specular")->SetColor(MwVector4(materialObj->specularColor.x,
														  materialObj->specularColor.y,
														  materialObj->specularColor.z,
														  1.0f));
	material->GetProperty("Gloss")->SetFloat(materialObj->specularFactor);


	if (materialObj->bumpMap != 0)
    {
		MwString fileName;
		if (materialObj->bumpMap->fileName.IndexOf(':') != -1)
			fileName = materialObj->bumpMap->fileName;
		else
			fileName = MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, materialObj->bumpMap->fileName);

		MwTexture2D *texture = this->context->AcquireTexture(fileName);

        material->AddShaderSlot(MwShaderOperation_NormalMap, MwColorOperation_Set);

		material->GetProperty("Normal Map")->SetReference(MwParameterType_ReferenceTexture, texture);
    }
    else
        material->AddShaderSlot(MwShaderOperation_VertexLighting, MwColorOperation_Set);


	if (materialObj->diffuseMap != 0)
    {
		MwString fileName;
		if (materialObj->diffuseMap->fileName.IndexOf(':') != -1)
			fileName = materialObj->diffuseMap->fileName;
		else
			fileName = MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, materialObj->diffuseMap->fileName);

		MwTexture2D *texture = this->context->AcquireTexture(fileName);

        material->AddShaderSlot(MwShaderOperation_ColorMap, MwColorOperation_Modulate);

        material->GetProperty("Color Map")->SetReference(MwParameterType_ReferenceTexture, texture);
    }

	if (materialObj->reflectionMap != 0)
    {
		MwString fileName;
		if (materialObj->reflectionMap->fileName.IndexOf(':') != -1)
			fileName = materialObj->reflectionMap->fileName;
		else
			fileName = MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, materialObj->reflectionMap->fileName);

		MwTexture2D *texture = this->context->AcquireTexture(fileName);

        material->AddShaderSlot(MwShaderOperation_EnvMap, MwColorOperation_Add);

        material->GetProperty("Reflection Map")->SetReference(MwParameterType_ReferenceTexture, texture);
    }

	material->UpdateShader();

	return material;
}
