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

#include "..\FileSystem\PhysicalFileSystem\MwPhysicalFileSystem.h"

#include "..\Media\Scene\Native\MwNativeSceneDispatcher.h"
#include "..\Media\Scene\3ds\Mw3dsSceneDispatcher.h"
#include "..\Media\Scene\Obj\MwObjSceneDispatcher.h"

#include "..\Media\Sound\Wav\MwWavSoundMediaDispatcher.h"

#include "..\Graphics\Soras\MwSorasGraphicsDeviceDispatcher.h"

#include "..\Media\Scene\MwScene.h"

#include "..\Media\Scene\Native\MwNativeScene.h"

#include "Utilities\Serialization\MwHierarchyStreamWriter.h"
#include "Utilities\Serialization\MwHierarchyStreamReader.h"

#include "MwStandardEntityDispatcher.h"

#include "..\Tools\Streams\MwMemoryStream.h"

#include "..\Tools\OS\MwOSUtils.h"

#include "Meshwork.h"

typedef unsigned int (*MwModuleFunctionGetSignature) ();
typedef void *(*MwModuleFunctionCreateDispatcher) (int index);

Meshwork::Meshwork(void *windowHandle)
{
	this->windowHandle = windowHandle;
	this->speed = 1.0;
	this->ambientLighting.Set(0.2f, 0.2f, 0.2f, 1.0f);
	this->clearColor.Set(0.84f, 0.92f, 1.0f, 1.0f);
    this->timer = new MwTimer();
	MwOSUtils::GetWindowClientSize(windowHandle, this->viewportWidth, this->viewportHeight);

	this->renderEvents = new MwRenderEvents(*this);
	this->rayIntersectionEvents = new MwRayIntersectionEvents(*this);
	this->screenPickEvents = new MwScreenPickEvents(*this);

	this->activeLights = &this->activeLights2;
	this->activeLightsCollecting = &this->activeLights1;

	this->bones.SetSize(64);	

	this->sceneMediaDispatchers.Add(new MwNativeSceneDispatcher());
	this->sceneMediaDispatchers.Add(new Mw3dsSceneDispatcher());
	this->sceneMediaDispatchers.Add(new MwObjSceneDispatcher());

	this->soundMediaDispatchers.Add(new MwWavSoundMediaDispatcher());

	this->graphicsDeviceDispatchers.Add(new MwSorasGraphicsDeviceDispatcher());

	this->entityDispatchers.Add(new MwStandardEntityDispatcher());

	this->LoadModules();

	this->fileSystem = new MwPhysicalFileSystem();

	if (this->graphicsDeviceDispatchers.count > 0)
	{
		this->graphicsDevice = (MwGraphicsDevice*)this->graphicsDeviceDispatchers[0]->CreateObject();
		this->graphicsDevice->SetRenderTargetWindow(this->windowHandle);
		//this->SetGraphicsDevice((MwGraphicsDevice*)this->graphicsDeviceDispatchers[0]->CreateObject());
	}
    else
        this->graphicsDevice = 0;

	if (this->audioDeviceDispatchers.count > 0)
	{
		this->audioDevice = (MwAudioDevice*)this->audioDeviceDispatchers[0]->CreateObject();
	}
    else
        this->audioDevice = 0;

	this->scriptBuilder.SetProcessor(&this->scriptProcessor);

	this->CreateDefaultTexture();

	this->Reset();
}

Meshwork::~Meshwork(void)
{
	this->Reset();

	delete this->defaultTexture;
	
	for (int i = 0; i < this->graphicsDeviceDispatchers.count; i++)
		delete this->graphicsDeviceDispatchers[i];

	for (int i = 0; i < this->audioDeviceDispatchers.count; i++)
		delete this->audioDeviceDispatchers[i];

	for (int i = 0; i < this->entityDispatchers.count; i++)
		delete this->entityDispatchers[i];
	
	for (int i = 0; i < this->imageMediaDispatchers.count; i++)
		delete this->imageMediaDispatchers[i];

	for (int i = 0; i < this->soundMediaDispatchers.count; i++)
		delete this->soundMediaDispatchers[i];

	for (int i = 0; i < this->sceneMediaDispatchers.count; i++)
		delete this->sceneMediaDispatchers[i];
	
	if (this->graphicsDevice != 0)
		delete this->graphicsDevice;
	if (this->audioDevice != 0)
		delete this->audioDevice;

	delete this->fileSystem;

	delete this->timer;
	delete this->root;

	delete this->renderEvents;
	delete this->rayIntersectionEvents;
	delete this->screenPickEvents;

	this->UnloadModules();
}
    
void Meshwork::LoadModules(MwString modulesDir)
{
	MwList<MwFileInfo> files;

	if (modulesDir.IsEmpty())
		modulesDir = MwPhysicalFileSystem::GetFileDir(MwOSUtils::GetApplicationName());

	MwPhysicalFileSystem fs;
	fs.GetDirectoryContents(modulesDir, files);

	for (int fileIndex = 0; fileIndex < files.count; fileIndex++)
	{
		MwString fn = files[fileIndex].fileName;
		if (MwFileSystem::GetFileExtension(files[fileIndex].fileName).ToLower().Equals("dll"))
		{
			void *module = MwOSUtils::LoadModule(files[fileIndex].fileName);
			if (module != 0)
			{
				MwModuleFunctionGetSignature signatureFunction = (MwModuleFunctionGetSignature)MwOSUtils::GetModuleFunction(module, MwString("MwGetSignature"));
				if (signatureFunction != 0)
				{
					unsigned int signature = signatureFunction();
					if (signature = 0x09000000)
					{
						this->loadedModules.Add(module);

						MwModuleFunctionCreateDispatcher createDispatcherFunction = (MwModuleFunctionCreateDispatcher)MwOSUtils::GetModuleFunction(module, MwString("MwCreateDispatcher"));

						for (int dispatcherIndex = 0; MwDispatcher *dispatcher = (MwDispatcher*)createDispatcherFunction(dispatcherIndex); dispatcherIndex++)
						{
							MwString info;
							if (dispatcher->GetInfo(MwDispatcher::infoId_TypeId, 0, info))
							{
								unsigned int typeId;
								if (info.ToUInt(typeId))
								{
									switch (typeId)
									{
										case MwDispatcher::typeId_Image:
										{
											this->imageMediaDispatchers.Add(dispatcher);
											break;
										}

										case MwDispatcher::typeId_Sound:
										{
											this->soundMediaDispatchers.Add(dispatcher);
											break;
										}

										case MwDispatcher::typeId_Scene:
										{
											this->sceneMediaDispatchers.Add(dispatcher);
											break;
										}

										case MwDispatcher::typeId_GraphicsDevice:
										{
											this->graphicsDeviceDispatchers.Add(dispatcher);
											break;
										}

										case MwDispatcher::typeId_AudioDevice:
										{
											this->audioDeviceDispatchers.Add(dispatcher);
											break;
										}

										case MwDispatcher::typeId_FileSystem:
										{
											this->fileSystemDispatchers.Add(dispatcher);
											break;
										}

										default:
										{
											delete dispatcher;
											break;
										}
									}
								}
								else
									delete dispatcher;
							}
							else 
								delete dispatcher;
						}
					}
				}
				else
					MwOSUtils::UnloadModule(&module);
			}
		}
	}
}

void Meshwork::UnloadModules()
{
	for (int i = 0; i < this->loadedModules.count; i++)
		MwOSUtils::UnloadModule(&this->loadedModules[i]);

	this->loadedModules.Clear();
}

// TODO: remove this method, or implement it properly : resources have to be loaded anew and not from the already loaded ones, so what about textures loaded from streams, changing from lower to higher color depth and etc.
// Should the old graphics device be deleted here? That doesn't seem intuitive. Rename to SetNEWGraphicsDevice?
void Meshwork::SetGraphicsDevice(MwGraphicsDevice *graphicsDevice)
{
	if (this->graphicsDevice == graphicsDevice)
		return;

	MwMemoryStream save;
	this->ExportScene(save);

	this->Reset();
	delete this->defaultTexture;
	
	if (this->graphicsDevice != 0)
		delete this->graphicsDevice;

	this->graphicsDevice = graphicsDevice;
	this->graphicsDevice->SetRenderTargetWindow(this->windowHandle);

	save.Seek(0);
	this->ImportScene(save);

	this->CreateDefaultTexture();
}

int Meshwork::SetGraphicsDevice(const MwString &graphicsDeviceName)
{
	for (int i = 0; i < this->graphicsDeviceDispatchers.count; i++)
	{
		MwString name;
		if (this->graphicsDeviceDispatchers[i]->GetInfo(MwDispatcher::infoId_Name, 0, name))
		{
			if(name.Equals(graphicsDeviceName))
			{
				this->SetGraphicsDevice((MwGraphicsDevice*)this->graphicsDeviceDispatchers[i]->CreateObject());
				return i;
			}
		}
	}

	return -1;
}

void Meshwork::SetAudioDevice(MwAudioDevice *audioDevice)
{
	if (this->audioDevice == audioDevice)
		return;

	MwMemoryStream save;
	this->ExportScene(save);

	this->Reset();
	
	if (this->audioDevice != 0)
		delete this->audioDevice;

	this->audioDevice = audioDevice;

	save.Seek(0);
	this->ImportScene(save);
}

int Meshwork::SetAudioDevice(const MwString &audioDeviceName)
{
	for (int i = 0; i < this->audioDeviceDispatchers.count; i++)
	{
		MwString name;
		if (this->audioDeviceDispatchers[i]->GetInfo(MwDispatcher::infoId_Name, 0, name))
		{
			if(name.Equals(audioDeviceName))
			{
				this->SetAudioDevice((MwAudioDevice*)this->audioDeviceDispatchers[i]->CreateObject());
				return i;
			}
		}
	}

	return -1;
}

void Meshwork::Reset()
{
	this->activeLights1.Clear();
	this->activeLights2.Clear();
	this->nearestActiveLights.Clear();

	for (int i = 0; i < this->resources.count; i++)
		delete this->resources[i];
	this->resources.Clear();
	this->resourceID = 0;

    this->root = (MwEntitySet*)this->AddResource(*new MwEntitySet());
	this->root->name = "Default Root";
}

bool Meshwork::ImportScene(MwBaseStream &stream)
{
	long long streamPos = stream.position;

	bool success = false;
	for (int i = 0; i < this->sceneMediaDispatchers.count; i++)
	{
		stream.Seek(streamPos);
		MwScene *scene = (MwScene*)this->sceneMediaDispatchers[i]->CreateObject();
		scene->SetContext(this);
		success = scene->Load(stream);
		delete scene;

		if (success)
			break;
	}

	this->timer->Tick();

	return success;
}

bool Meshwork::ImportScene(MwString fileName)
{
	MwString fullFileName = this->GetFullFileName(fileName);

	this->serializationParameters.fullSourceName = fullFileName;
	this->serializationParameters.rootDir = MwFileSystem::GetFileDir(fullFileName);
	this->serializationParameters.friendlyName = MwFileSystem::GetFileNameWithoutExtension(fullFileName);
	
	MwBaseStream *stream = this->fileSystem->OpenFile(fileName);
	if (stream == 0)
		return false;

	bool success = this->ImportScene(*stream);

	delete stream;

	return success;
}

bool Meshwork::ExportScene(MwBaseStream &stream)
{
	MwNativeScene scene;
	scene.SetContext(this);

	return scene.Save(stream, 0);
}

bool Meshwork::ExportScene(MwString fileName)
{
	MwString fullFileName = this->GetFullFileName(fileName);

	this->serializationParameters.fullSourceName = fileName;
	this->serializationParameters.rootDir = MwFileSystem::GetFileDir(fileName);
	this->serializationParameters.friendlyName = MwFileSystem::GetFileNameWithoutExtension(fileName);

	MwBaseStream *stream = this->fileSystem->CreateNewFile(fileName);
	if (stream == 0)
		return false;

	bool success = this->ExportScene(*stream);

	delete stream;

	return success;
}

void Meshwork::SetViewport(int width, int height)
{
	this->graphicsDevice->SetViewport(0, 0, width, height);
	this->viewportWidth = width;
	this->viewportHeight = height;
}

void Meshwork::TraceBranch(int startIndex, MwEntitySet &entitySet, MwTraceParameters &parameters, bool singleItem)
{
    if (!*(bool*)entitySet.properties[MwEntitySet::propertyIndex_Active]->value)
        return;

	MwMatrix parentTransform;
		
    MwMatrix::Copy(parentTransform, parameters.parentTransform); // copy parameters.parentTransform into parentTransform, so that wneh MwTransform occurs, we change parameters.parentTransform, but parentTransform, which we actually use as parent, stays the same

    int endIndex;
    if (singleItem)
        endIndex = startIndex + 1;
    else
		endIndex = entitySet.references.count;

    for (int i = startIndex; i < endIndex; i++)
    {
        MwBaseResource *res = entitySet.references[i];
		switch (res->resourceType)
        {
			case MwResourceType_Texture:
				{
					parameters.textureRef = (MwTexture2D*)res;

					this->traceEvents->OnTexture2D(parameters);
					break;
				}

            case MwResourceType_Camera:
				{
					parameters.cameraBranch = &entitySet;
					parameters.cameraIndex = i;
					parameters.cameraRef = (MwCamera*)res;

					parameters.cameraRef->BuildMatrix(parameters.parentTransform);
                    
					this->traceEvents->OnCamera(parameters);
					break;
				}
                
            case MwResourceType_Material:
				{
					MwMaterial *materialRes = (MwMaterial*)res;

					if (parameters.materialRef != 0)
						if ((*(bool*)parameters.materialRef->properties[MwMaterial::propertyIndex_OverrideMaterials]->GetEffectiveParameter()->value))
							if (!(*(bool*)materialRes->properties[MwMaterial::propertyIndex_OverrideMaterials]->GetEffectiveParameter()->value))
								break;

					parameters.materialBranch = &entitySet;
					parameters.materialIndex = i;
					parameters.materialRef = materialRes;

					this->traceEvents->OnMaterial(parameters);
					break;
				}

            case MwResourceType_Transform:
				{
					parameters.transformBranch = &entitySet;
					parameters.transformIndex = i;
					parameters.transformRef = (MwTransform*)res;

                    this->traceEvents->OnTransform(parameters);

                    MwMatrix::Multiply(parameters.transformRef->matrix, parameters.transformRef->matrix, parentTransform);
					MwMatrix::Multiply(parameters.parentTransform, parameters.transformRef->pivotless, parentTransform);

					if (parameters.transformRef->properties[MwTransform::propertyIndex_Bone]->GetBool())
					{
						int boneIndex = parameters.transformRef->properties[MwTransform::propertyIndex_BoneIndex]->GetInt();
						if (boneIndex < this->bones.count)
						{
							MwMatrix::Multiply(this->bones[boneIndex], parameters.transformRef->boneBindPoseInverse, parameters.transformRef->matrix);
						}
					}
					break;
				}

            case MwResourceType_Mesh:
				{
					parameters.meshBranch = &entitySet;
					parameters.meshIndex = i;
					parameters.meshRef = (MwMesh*)res;

					if (!parameters.meshRef->active)
						break;

					if (parameters.materialRef == 0)
						break;

					if (parameters.cameraRef == 0)
						break;

					this->traceEvents->OnMesh(parameters);
					break;
				}

			case MwResourceType_EntitySet:
				{
					MwEntitySet *subSet = (MwEntitySet*)res;
					bool multiPass = *(bool*)subSet->properties[MwEntitySet::propertyIndex_MultiPass]->GetEffectiveParameter()->value;
					bool branch = *(bool*)subSet->properties[MwEntitySet::propertyIndex_Branch]->GetEffectiveParameter()->value;

					MwTraceParameters *traceParams = branch ? new MwTraceParameters(parameters) : &parameters;

					if (multiPass)
					{
						for (int ii = 0; ii < subSet->references.count; ii++)
						{
							TraceBranch(ii, *subSet, *traceParams, true);
							TraceBranch(i + 1, entitySet, *traceParams, false);
						}
					}
					else
					{
						TraceBranch(0, *(MwEntitySet*)res, *traceParams, false);
					}

					if (branch)
					{
						delete traceParams;
						this->traceEvents->OnExitedBranch(parameters);
					}
                	
					break;
				}

            case MwResourceType_Mechanism:
				{
					parameters.mechanismRef = (MwBaseMechanism*)res;

					this->traceEvents->OnMechanism(parameters);
					break;
				}

			case MwResourceType_Light:
				{
					parameters.lightBranch = &entitySet;
					parameters.lightIndex = i;
					parameters.lightRef = (MwLight*)res;

					this->traceEvents->OnLight(parameters);
					break;
				}

			case MwResourceType_SoundEmitter:
				{
					parameters.soundEmitterBranch = &entitySet;
					parameters.soundEmitterIndex = i;
					parameters.soundEmitterRef = (MwSoundEmitter*)res;

					this->traceEvents->OnSoundEmitter(parameters);
					break;
				}
			case MwResourceType_SoundReceptor:
				{
					parameters.soundReceptorBranch = &entitySet;
					parameters.soundReceptorIndex = i;
					parameters.soundReceptorRef = (MwSoundReceptor*)res;

					this->traceEvents->OnSoundReceptor(parameters);
					break;
				}
        }
    }
}

void Meshwork::TraceWorld(MwTraceEvents &traceEvents)
{
    this->traceEvents = &traceEvents;
    TraceBranch(0, *this->root, MwTraceParameters(), false);
}

void Meshwork::RenderWorld()
{
	this->timer->Tick();

	this->graphicsDevice->Clear(this->clearColor);

	this->renderEvents->SetupNewFrame();
	this->TraceWorld(*this->renderEvents);

	this->graphicsDevice->Present();

	this->SwapLightsLists();
}
    
bool Meshwork::GetRayIntersection(MwVector3 &rayPoint1, MwVector3 &rayPoint2, MwIntersectionInfo intersectionInfo, MwTraceParameters entityInfo)
{
    this->rayIntersectionEvents->SetupRay(rayPoint1, rayPoint2);
    this->TraceWorld(*this->rayIntersectionEvents);
      
    if (this->rayIntersectionEvents->intersected)
    {
        intersectionInfo = this->rayIntersectionEvents->intersectionInfo;
        entityInfo = this->rayIntersectionEvents->traceResult;
        return true;
    }
    else
        return false;
}
    
bool Meshwork::Pick(int x, int y, int screenWidth, int screenHeight, MwIntersectionInfo &intersectionInfo, MwTraceParameters &entityInfo)
{
    this->screenPickEvents->SetupScreenPick(x, y, screenWidth, screenHeight);
    this->TraceWorld(*this->screenPickEvents);

    intersectionInfo = this->screenPickEvents->intersectionInfo;
    entityInfo = this->screenPickEvents->entityInfo;
	return this->screenPickEvents->intersected;
}

    
void Meshwork::CalculateNearestActiveLights(int maxCount, MwVector3 &position)
{
	this->nearestActiveLights.SetSize(this->activeLights->count);
	for (int i = 0; i < this->activeLights->count; i++)
	{
		MwActiveLightInfo *lightInfo = &this->activeLights->Get(i);
		lightInfo->distance = MwVector3::Distance(position, lightInfo->lightPos);
		this->nearestActiveLights.Set(i, lightInfo);
	}

	int nearestCount = MwMath::Min(this->activeLights->count, maxCount);

	for (int i = 0; i < nearestCount; i++)
	{
		int nearestIndex = i;
		for (int j = i + 1; j < this->nearestActiveLights.count; j++)
		{
			if (this->nearestActiveLights[j]->distance < this->nearestActiveLights[nearestIndex]->distance)
				nearestIndex = j;
		}

		if (nearestIndex != i)
		{
			MwActiveLightInfo *lightInfo = this->nearestActiveLights[i];
			this->nearestActiveLights[i] = this->nearestActiveLights[nearestIndex];
			this->nearestActiveLights[nearestIndex] = lightInfo;
		}
	}

	this->nearestActiveLights.SetSize(nearestCount);
}

MwBaseResource *Meshwork::AddResource(MwBaseResource &resource)
{
    this->resourceID++;

    resource.id = resourceID;
	
	this->resources.Add(&resource);

    return &resource;
}

void Meshwork::RemoveResourceFromSet(MwEntitySet *resourceSet, MwBaseResource *resource)
{
	for (int i = 0; i < resourceSet->references.count; i++)
	{
		MwBaseResource *entitySetResource = resourceSet->references[i];

		if (entitySetResource == resource)
		{
			resourceSet->references.RemoveAt(i);
			i--;
		}

		else if (entitySetResource->resourceType == MwResourceType_EntitySet)
			this->RemoveResourceFromSet((MwEntitySet*)entitySetResource, resource);
	}

}

void Meshwork::RemoveResource(MwBaseResource *resource)
{
	this->RemoveResourceFromSet(this->root, resource);
	
	for (int i = 0; i < this->resources.count; i++)
	{
		if (this->resources[i] == resource)
		{
			delete this->resources[i];
			this->resources.RemoveAt(i);
			i--;
		}
	}
}

int Meshwork::GetResourceIndex(MwBaseResource &resource)
{
    int count = this->resources.count;
    for (int i = 0; i < count; i++)
        if (this->resources[i] == &resource)
            return i;
    return -1;
}

MwBaseResource *Meshwork::FindResourceX(const MwString &resourceName, MwResourceType resourceType)
{
    int count = this->resources.count;
    for (int i = 0; i < count; i++)
    {
    	MwBaseResource *resource = this->resources[i];
        if (resource->resourceType == resourceType)
			if (resource->name.Equals(resourceName))
                return resource;
    }

    return 0;
}

MwBaseResource *Meshwork::FindResourceX(long long id)
{
    int left = 0;
    int right = this->resources.count - 1;

    while (left <= right)
    {
        int index = left + (right - left) / 2;
        MwBaseResource *resource = this->resources[index];

        if (resource->id == id)
            return resource;

        if (resource->id < id)
            left = index + 1;
        else
            right = index - 1;
    }

    return 0;
}
    
MwString Meshwork::AcquireResourceName(MwString &resourceName, MwResourceType resourceType)
{
    int nameIndex = 0;
    MwString result = resourceName;

    while (FindResourceX(result, resourceType) != 0)
    {
        nameIndex++;
        result = resourceName + MwString(nameIndex);
    }

    return MwString(result);
}

MwBaseResource *Meshwork::FindEntity(MwResourceType resourceType, MwEntitySet *entitySet)
{
	if (entitySet == 0)
		entitySet = this->root;

	for (int i = 0; i < entitySet->references.count; i++)
	{
		MwBaseResource *reference = entitySet->references[i];
		
		if (reference->resourceType == resourceType)
			return reference;
		
		if (reference->resourceType == MwResourceType_EntitySet)
			return this->FindEntity(resourceType, (MwEntitySet*)reference);
	}
}

MwBaseResource *Meshwork::FindEntity(const MwString &entityName, MwResourceType resourceType, MwEntitySet *entitySet)
{
	if (entitySet == 0)
		entitySet = this->root;

	for (int i = 0; i < entitySet->references.count; i++)
	{
		MwBaseResource *reference = entitySet->references[i];
		
		if ((reference->resourceType == resourceType) && (reference->name.Equals(entityName)))
			return reference;
		
		if (reference->resourceType == MwResourceType_EntitySet)
			return this->FindEntity(entityName, resourceType, (MwEntitySet*)reference);
	}
}

MwImage *Meshwork::CreateImage(MwBaseStream &stream)
{
	long long streamInitialPos = stream.position;

	for (int i = 0; i < this->imageMediaDispatchers.count; i++)
	{
		MwImage *image = (MwImage*)this->imageMediaDispatchers[i]->CreateObject();
		if (image->Load(stream))
			return image;

		delete image;

		stream.Seek(streamInitialPos);
	}

	return 0;
}

MwImage *Meshwork::CreateImage(MwString fileName)
{
	MwBaseStream *stream = this->fileSystem->OpenFile(this->GetFullFileName(fileName));
	if (stream == 0)
		return 0;

	MwImage *result = this->CreateImage(*stream);

	delete stream;

	return result;
}

MwTexture2D *Meshwork::AcquireTexture(MwString fileName)
{
	for (int i = 0; i < this->resources.count; i++)
		if (this->resources[i]->resourceType == MwResourceType_Texture)
			if (((MwTexture2D*)this->resources[i])->fileName.Equals(fileName))
				return (MwTexture2D*)this->resources[i];
	
	MwTexture2D *result = new MwTexture2D(*this);
	
	if (!result->Load(fileName))
	{
		delete result;
		return 0;
	}

	result->name = MwFileSystem::GetFileNameWithoutExtension(fileName);
	this->AddResource(*result);

	return result;
}

MwSoundMedia *Meshwork::CreateSoundMedia(MwBaseStream &stream)
{
	long long streamInitialPos = stream.position;

	for (int i = 0; i < this->soundMediaDispatchers.count; i++)
	{
		MwSoundMedia *soundMedia = (MwSoundMedia*)this->soundMediaDispatchers[i]->CreateObject();
		if (soundMedia->Load(stream))
			return soundMedia;

		delete soundMedia;

		stream.Seek(streamInitialPos);
	}

	return 0;
}

MwSoundMedia *Meshwork::CreateSoundMedia(MwString fileName, MwBaseStream **sourceStream)
{
	*sourceStream = this->fileSystem->OpenFile(this->GetFullFileName(fileName));
	if (sourceStream == 0)
		return 0;

	MwSoundMedia *result = this->CreateSoundMedia(**sourceStream);

	if (result == 0)
	{
		delete *sourceStream;
		*sourceStream = 0;
	}

	return result;
}

MwSound *Meshwork::AcquireSound(MwString fileName)
{
	for (int i = 0; i < this->resources.count; i++)
		if (this->resources[i]->resourceType == MwResourceType_Sound)
			if (((MwSound*)this->resources[i])->fileName.Equals(fileName))
				return (MwSound*)this->resources[i];
	
	MwSound *result = new MwSound(this);
	if (!result->Load(fileName))
	{
		delete result;
		return 0;
	}

	result->name = MwFileSystem::GetFileName(fileName);
	this->AddResource(*result);

	return result;
}

MwEntity *Meshwork::CreateEntity(int typeId)
{
	for (int i = 0; i < this->entityDispatchers.count; i++)
	{
		MwEntity *result = this->entityDispatchers[i]->CreateEntity(this, typeId);
		if (result != 0)
			return result;
	}

	return 0;
}

void Meshwork::SerializeResource(MwBaseStream *destination, MwBaseResource *resource)
{
	MwHierarchyStreamWriter writer(*destination);

	writer.BeginChunk(Meshwork::SerializationId_ResourceSerialization);
	writer.stream->WriteInt32(resource->typeId);
	resource->Serialize(*destination);
	writer.EndChunk();
}

MwBaseResource *Meshwork::DeserializeResource(MwBaseStream *source)
{
	MwHierarchyStreamReader reader(*source);

	if (reader.ReadChunkHeader())
	{
		if (reader.chunkId == Meshwork::SerializationId_ResourceSerialization)
		{
			int typeId = reader.stream->ReadInt32();

			MwBaseResource *result = (MwBaseResource*)this->CreateEntity(typeId);
			if (result != 0)
			{
				if (result->Deserialize(*source))
					return result;
				else
					delete result;
			}
		}
	}

	return 0;
}


void Meshwork::SwapLightsLists()
{
	MwList<MwActiveLightInfo> *temp = this->activeLights;
	this->activeLights = this->activeLightsCollecting;
	this->activeLightsCollecting = temp;

	this->activeLightsCollecting->SetSize(0);
}

void Meshwork::CreateDefaultTexture()
{
	int width = 128;
	int height = 128;
	int patternSize = 8;
	int index = 0;
	unsigned int *data = new unsigned int[width * height];
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			unsigned char checkerColor = ((x / patternSize) % 2) == ((y / patternSize) % 2) ? 0xff : 0xa0;
			data[index] = 0xff000000 | (checkerColor << 16) | (checkerColor << 8) | checkerColor;
			index++;
		}
	}
	this->defaultTexture = new MwTexture2D(*this);
	this->defaultTexture->deviceTexture->Update(data, width, height);
	delete[] data;
}

MwString Meshwork::GetFullFileName(MwString fileName)
{
	if (MwFileSystem::IsAbsolutePath(fileName))
		return MwString(fileName);
	else
		return MwString(MwFileSystem::MergePaths(MwOSUtils::GetApplicationPath(), fileName));
}