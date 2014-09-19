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

#include "MwNativeFileReader.h"

#include "MwNativeFileId.h"

#include "..\..\..\Engine\Entities\EntitySet\MwEntitySet.h"

#include "..\..\..\Tools\Streams\MwFileStream.h"

#include "..\..\..\Engine\Meshwork.h"


MwNativeFileReader::MwNativeFileReader(Meshwork *context)
{
    this->context = context;
}

MwNativeFileReader::~MwNativeFileReader(void)
{
}

bool MwNativeFileReader::Read(MwBaseStream &source)
{
	MwHierarchyStreamReader reader(source);

	long long mainChunkEnd = -1;

    while (reader.ReadChunkHeader())
	{
		switch (reader.chunkId)
		{
			case MwNativeFileID::Main:
				{
					mainChunkEnd = reader.stream->position + reader.chunkSize;
					break;
				}

			case MwNativeFileID::Resources:
				{
					break;
				}

			case MwNativeFileID::ResourceSerializationWrap:
				{
					MwBaseResource *resource = this->context->DeserializeResource(reader.stream);
					if (resource != 0)
					{
						long long originalId = resource->id;
						this->context->AddResource(*resource);
						this->idMap.Add(originalId, resource->id);
					}

					break;
				}

			case MwNativeFileID::RootBranch:
				{
					long long rootId = reader.stream->ReadInt64();
					MwBaseResource *rootResource = this->context->FindResourceX(this->GetMappedResourceId(rootId));

					if (rootResource != 0)
					{
						if (rootResource->resourceType == MwResourceType_EntitySet)
						{
							MwEntitySet *root = (MwEntitySet*)rootResource;

							if (this->context->root != 0)
							{
								for (int i = 0; i < root->references.count; i++)
									this->context->root->references.Add(root->references[i]);

								this->context->RemoveResource(root);
							}
							else
							{
								this->context->root = root;
							}
						}
					}

					break;
				}

			default:
			{
				if ((reader.chunkSize < 0) || (reader.stream->position + reader.chunkSize > mainChunkEnd))
					return false;

				reader.SkipChunk();

				break;
			}
		}

		if (reader.stream->position >= mainChunkEnd)
			break;
	}

	this->LinkResources();

	return true;
}

void MwNativeFileReader::LinkResources()
{
	int resourceCount = this->context->resources.count;
    for (int resourceIndex = 0; resourceIndex < resourceCount; resourceIndex++)
    {
		MwBaseResource *resource = this->context->resources[resourceIndex];

        int numProps = ((MwBaseResource*)resource)->properties.count;
        for (int prop = 0; prop < numProps; prop++)
        {
            MwProperty *parameter = ((MwBaseResource*)resource)->properties[prop];
			if ((parameter->type > MwParameterType_Color) && (parameter->value != 0)) // TODO this check is not preferred
			{
				MwBaseResource *reference = (MwBaseResource*)parameter->value;
				if (reference->resourceType == MwResourceType_None)
				{
					MwBaseResource * ref = this->context->FindResourceX(this->GetMappedResourceId(reference->id));
					parameter->value = ref;
					delete reference;
				}
			}
        }

		if (resource->resourceType == MwResourceType_EntitySet)
        {
            int numReferences = ((MwEntitySet*)resource)->references.count;
            for (int i = 0; i < numReferences; i++)
            {
				MwBaseResource *reference = (MwBaseResource*)((MwEntitySet*)resource)->references[i];
				if (reference->resourceType == MwResourceType_None)
				{
					MwBaseResource * ref = this->context->FindResourceX(this->GetMappedResourceId(reference->id));
					((MwEntitySet*)resource)->references[i] = ref;
					delete reference;
				}
            }
        }
    }
}

long long MwNativeFileReader::GetMappedResourceId(long long originalId)
{
	long long newId;
	if (this->idMap.GetValue(originalId, newId))
		return newId;
	else
		return -1;
}
