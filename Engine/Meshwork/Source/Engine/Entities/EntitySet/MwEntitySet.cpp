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

#include "MwEntitySet.h"

MwEntitySet::MwEntitySet(void)
	: MwBaseResource()
{
	this->typeId = MwEntitySet::classId;
    this->resourceType = MwResourceType_EntitySet;

	this->properties.Add(new MwProperty(MwString("Active"), true));
    this->properties.Add(new MwProperty(MwString("Multi Pass"), false));
    this->properties.Add(new MwProperty(MwString("Branch"), true));
}


MwEntitySet::~MwEntitySet(void)
{
}

void MwEntitySet::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	MwBaseResource::SerializeChunks(writer);

	writer.BeginChunk(MwEntitySet::SerializationId_References);
	writer.stream->WriteInt32(this->references.count);
	for (int i = 0; i < this->references.count; i++)
		writer.stream->WriteInt64(this->references[i]->id);
	writer.EndChunk();
}

bool MwEntitySet::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwEntitySet::SerializationId_References:
		{
			int numReferences = reader.stream->ReadInt32();
			for (int i = 0; i < numReferences; i++)
			{
				long long id = reader.stream->ReadInt64();

				MwBaseResource *link = new MwBaseResource();
				link->resourceType = MwResourceType_None;
				link->id = id;
				this->references.Add(link);
			}
			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}
