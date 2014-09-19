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

#include "MwBaseResource.h"

MwBaseResource::MwBaseResource(void)
{
}


MwBaseResource::~MwBaseResource(void)
{
    int count = this->properties.count;
    for (int i = 0; i < count; i++)
		delete this->properties[i];
}

MwProperty *MwBaseResource::GetProperty(MwString name)
{
    int count = this->properties.count;
    for (int i = 0; i < count; i++)
        if (this->properties[i]->name.Equals(name))
            return this->properties[i];

    return 0;
}

void MwBaseResource::SerializeParameter(MwParameter &parameter, MwBaseStream &destination)
{
	destination.WriteInt32(parameter.type);

	switch (parameter.type)
	{
		case MwParameterType_Int:
		{
			destination.WriteInt32(*(int*)parameter.value);
			break;
		}

		case MwParameterType_Float:
		{
			destination.WriteFloat(*(float*)parameter.value);
			break;
		}

		case MwParameterType_Bool:
		{
			destination.WriteBool(*(bool*)parameter.value);
			break;
		}

		case MwParameterType_Color:
		{
			destination.WriteFloat(((MwVector4*)parameter.value)->x);
			destination.WriteFloat(((MwVector4*)parameter.value)->y);
			destination.WriteFloat(((MwVector4*)parameter.value)->z);
			destination.WriteFloat(((MwVector4*)parameter.value)->w);
			break;
		}

		case MwParameterType_ReferenceVector3:
		case MwParameterType_ReferenceTexture:
		case MwParameterType_ReferenceCamera:
		case MwParameterType_ReferenceMechanism:
		case MwParameterType_ReferenceTransform:
		case MwParameterType_ReferenceSound:
		{
			MwBaseResource *reference = (MwBaseResource*)parameter.value;
			if (reference != 0)
				destination.WriteInt64(reference->id);
			else
				destination.WriteInt64(-1);
			break;
		}
	}
}

void MwBaseResource::DeserializeParameter(MwParameter &parameter, MwBaseStream &source)
{
	MwParameterType propertyType = (MwParameterType)source.ReadInt32();

	switch (propertyType)
	{
		case MwParameterType_Int:
		{
			parameter.SetInt(source.ReadInt32());
			break;
		}

		case MwParameterType_Float:
		{
			parameter.SetFloat(source.ReadFloat());
			break;
		}

		case MwParameterType_Bool:
		{
			parameter.SetBool(source.ReadBool());
			break;
		}

		case MwParameterType_Color:
		{
			MwVector4 color;
			color.x = source.ReadFloat();
			color.y = source.ReadFloat();
			color.z = source.ReadFloat();
			color.w = source.ReadFloat();
			parameter.SetColor(color);
			break;
		}

		case MwParameterType_ReferenceVector3:
		case MwParameterType_ReferenceTexture:
		case MwParameterType_ReferenceCamera:
		case MwParameterType_ReferenceMechanism:
		case MwParameterType_ReferenceTransform:
		case MwParameterType_ReferenceSound:
		{
			long long linkId = source.ReadInt64();

			MwBaseResource *link = new MwBaseResource();
			link->resourceType = MwResourceType_None;
			link->id = linkId;
			parameter.SetReference(propertyType, link);
			break;
		}
	}
}

void MwBaseResource::Serialize(MwBaseStream &destination)
{
	MwHierarchyStreamWriter writer(destination);

	writer.BeginChunk(MwBaseResource::SerializationId_Resource);
	this->SerializeChunks(writer);
	writer.EndChunk();
}

bool MwBaseResource::Deserialize(MwBaseStream &source)
{
	MwHierarchyStreamReader reader(source);

	long long mainChunkEnd = -1;

	while (reader.ReadChunkHeader())
	{
		switch (reader.chunkId)
		{
			case MwBaseResource::SerializationId_Resource:
			{
				mainChunkEnd = reader.stream->position + reader.chunkSize;
				break;
			}

			default:
			{
				if ((reader.chunkSize < 0) || (reader.stream->position + reader.chunkSize > mainChunkEnd))
					return false;

				if (!this->DeserializeChunk(reader))
					reader.SkipChunk();

				break;
			}
		}

		if (reader.stream->position >= mainChunkEnd)
			return true;
	}

	return true;
}

void MwBaseResource::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	writer.BeginChunk(MwBaseResource::SerializationId_ResourceId);
	writer.stream->WriteInt64(this->id);
	writer.EndChunk();

	writer.BeginChunk(MwBaseResource::SerializationId_ResourceName);
	writer.stream->WriteString(this->name);
	writer.EndChunk();

	writer.BeginChunk(MwBaseResource::SerializationId_Properties);
	
	for (int i = 0; i < this->properties.count; i++)
	{
		writer.BeginChunk(MwBaseResource::SerializationId_Property);

		writer.stream->WriteString(this->properties[i]->name);

		this->SerializeParameter(*(MwParameter*)this->properties[i], *writer.stream);
	
		writer.EndChunk();
		// Property
	}

	writer.EndChunk();
	// Properties
}

bool MwBaseResource::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	switch (reader.chunkId)
	{
		case MwBaseResource::SerializationId_ResourceId:
		{
			this->id = reader.stream->ReadInt64();
			break;
		}

		case MwBaseResource::SerializationId_ResourceName:
		{
			this->name = reader.stream->ReadString();
			break;
		}

		case MwBaseResource::SerializationId_Properties:
		{
			break;
		}

		case MwBaseResource::SerializationId_Property:
		{
			MwString propertyName = reader.stream->ReadString();
			MwProperty *currentProperty = this->GetProperty(propertyName);
			if (currentProperty == 0)
				currentProperty = this->properties.Add(new MwProperty(propertyName, MwParameterType_None, 0));

			this->DeserializeParameter(*(MwParameter*)currentProperty, *reader.stream);

			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}