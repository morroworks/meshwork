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

#include "MwMesh.h"

#include "..\..\Utilities\MwMaths.h"
#include "..\..\Utilities\Normals\MwGenerateNormals.h"

#include "..\..\..\Tools\MwMath.h"

#include "..\..\Meshwork.h"


MwMesh::MwMesh(Meshwork &context)
	: MwBaseResource()
{
	this->typeId = MwMesh::classId;
	this->resourceType = MwResourceType_Mesh;
    this->active = true;
        
    this->properties.Add(new MwProperty(MwString("Cull"), true));

	this->deviceMesh = context.graphicsDevice->CreateMesh();
}

MwMesh::~MwMesh(void)
{
	delete this->deviceMesh;
}

void MwMesh::ComputeNormals()
{
	MwGenerateNormals(*this->deviceMesh);	

	this->deviceMesh->UpdateVertices(0, -1);
}

void MwMesh::ComputeBounds()
{
	MwVector3 v, min, max;

	min.Set(MwMath::FloatMax);
	max.Set(MwMath::FloatMin);
	int numVertices = this->deviceMesh->GetVertexCount();
	for (int i = 0; i < numVertices; i++)
    {
        this->deviceMesh->GetVertexPosition(i, v);
        MwVector3::Min(min, min, v);
        MwVector3::Max(max, max, v);
    }

    MwVector3::Add(bounds.center, min, max);
    MwVector3::Scale(bounds.center, bounds.center, 1.0f / 2.0f);

    MwVector3::Subtract(bounds.box, max, min);
    MwVector3::Scale(bounds.box, bounds.box, 1.0f / 2.0f);

    bounds.sphere = 0.0f;
    for (int i = 0; i < numVertices; i++)
    {
        this->deviceMesh->GetVertexPosition(i, v);
		bounds.sphere = MwMath::Max(bounds.sphere, MwVector3::Distance(bounds.center, v));
    }
}

    
bool MwMesh::Intersection(MwVector3 &rayPoint, MwVector3 &rayDir, MwIntersectionInfo &intersectionInfo)
{
    intersectionInfo.intersection = false;

    if (!MwMaths::SphereIntersection(rayPoint, rayDir, bounds.center, bounds.sphere))
        return false;

	MwVector3 v0, v1, v2;

	intersectionInfo.distance = MwMath::FloatMax;
	int numIndices = this->deviceMesh->GetIndexCount();
    for (int i = 0; i < numIndices; i += 3)
    {
        int index0 = this->deviceMesh->GetIndex(i + 2);
        int index1 = this->deviceMesh->GetIndex(i + 1);
        int index2 = this->deviceMesh->GetIndex(i);

		this->deviceMesh->GetVertexPosition(index0, v0);
        this->deviceMesh->GetVertexPosition(index1, v1);
        this->deviceMesh->GetVertexPosition(index2, v2);
            
		float d, u, v;
        if (MwMaths::RayTriangleIntersection(rayPoint, rayDir,
											v0, v1, v2,
											d, u, v))
        {
            if ((d > 0) && (d < intersectionInfo.distance))
            {
				MwVertex delta1, delta2;
				MwVector3 n0, n1, n2;
				MwVector2 texCoord0, texCoord1, texCoord2;

                this->deviceMesh->GetVertexNormal(index0, n0);
                this->deviceMesh->GetVertexNormal(index1, n1);
                this->deviceMesh->GetVertexNormal(index2, n2);

                this->deviceMesh->GetVertexTexCoords(index0, texCoord0);
                this->deviceMesh->GetVertexTexCoords(index1, texCoord1);
                this->deviceMesh->GetVertexTexCoords(index2, texCoord2);

				MwVector3::Subtract(delta1.position, v1, v0);
				MwVector3::Subtract(delta1.normal, n1, n0);
				MwVector2::Subtract(delta1.texCoords, texCoord1, texCoord0);

				MwVector3::Subtract(delta2.position, v2, v0);
				MwVector3::Subtract(delta2.normal, n2, n0);
				MwVector2::Subtract(delta2.texCoords, texCoord2, texCoord0);


                intersectionInfo.point.position.x = v0.x + delta1.position.x * u + delta2.position.x * v;
                intersectionInfo.point.position.y = v0.y + delta1.position.y * u + delta2.position.y * v;
                intersectionInfo.point.position.z = v0.z + delta1.position.z * u + delta2.position.z * v;
                intersectionInfo.point.normal.x = n0.x + delta1.normal.x * u + delta2.normal.x * v;
                intersectionInfo.point.normal.y = n0.y + delta1.normal.y * u + delta2.normal.y * v;
                intersectionInfo.point.normal.z = n0.z + delta1.normal.z * u + delta2.normal.x * v;
                intersectionInfo.point.texCoords.x = texCoord0.x + delta1.texCoords.x * u + delta2.texCoords.x * v;
                intersectionInfo.point.texCoords.y = texCoord0.y + delta1.texCoords.y * u + delta2.texCoords.y * v;

                intersectionInfo.distance = d;
                intersectionInfo.primitiveIndex = i;
            }
            intersectionInfo.intersection = true;
        }
    }
    return intersectionInfo.intersection;
}

void MwMesh::CopyFrom(MwMesh &source)
{
	this->deviceMesh->CopyFrom(source.deviceMesh);
}

bool MwMesh::Deserialize(MwBaseStream &source)
{
	if (!MwBaseResource::Deserialize(source))
		return false;

	this->deviceMesh->UpdateIndices(0, -1);
	this->deviceMesh->UpdateVertices(0, -1);
	this->ComputeBounds();

	return true;
}

void MwMesh::SerializeVector2(MwBaseStream &stream, MwVector2 &vector)
{
	stream.WriteFloat(vector.x);
	stream.WriteFloat(vector.y);
}

MwVector2 MwMesh::DeserializeVector2(MwBaseStream &stream)
{
	MwVector2 result;
	result.x = stream.ReadFloat();
	result.y = stream.ReadFloat();
	return result;
}

void MwMesh::SerializeVector3(MwBaseStream &stream, MwVector3 &vector)
{
	stream.WriteFloat(vector.x);
	stream.WriteFloat(vector.y);
	stream.WriteFloat(vector.z);
}

MwVector3 MwMesh::DeserializeVector3(MwBaseStream &stream)
{
	MwVector3 result;
	result.x = stream.ReadFloat();
	result.y = stream.ReadFloat();
	result.z = stream.ReadFloat();
	return result;
}

void MwMesh::SerializeVector4(MwBaseStream &stream, MwVector4 &vector)
{
	stream.WriteFloat(vector.x);
	stream.WriteFloat(vector.y);
	stream.WriteFloat(vector.z);
	stream.WriteFloat(vector.w);
}

MwVector4 MwMesh::DeserializeVector4(MwBaseStream &stream)
{
	MwVector4 result;
	result.x = stream.ReadFloat();
	result.y = stream.ReadFloat();
	result.z = stream.ReadFloat();
	result.w = stream.ReadFloat();
	return result;
}

void MwMesh::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	MwBaseResource::SerializeChunks(writer);

	int numVertices = this->deviceMesh->GetVertexCount();
	int numIndices = this->deviceMesh->GetIndexCount();
	MwVector3 v3;
	MwVector2 v2;
	MwVector4 v41, v42;

	writer.BeginChunk(MwMesh::SerializationId_Vertices);
	writer.stream->WriteInt32(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		this->deviceMesh->GetVertexPosition(i, v3);
		this->SerializeVector3(*writer.stream, v3);
	}
	writer.EndChunk();

	writer.BeginChunk(MwMesh::SerializationId_Normals);
	writer.stream->WriteInt32(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		this->deviceMesh->GetVertexNormal(i, v3);
		this->SerializeVector3(*writer.stream, v3);
	}
	writer.EndChunk();

	writer.BeginChunk(MwMesh::SerializationId_TexCoords);
	writer.stream->WriteInt32(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		this->deviceMesh->GetVertexTexCoords(i, v2);
		this->SerializeVector2(*writer.stream, v2);
	}
	writer.EndChunk();

	writer.BeginChunk(MwMesh::SerializationId_Triangles);
	writer.stream->WriteInt32(numIndices);
	for (int i = 0; i < numIndices; i++)
	{
		writer.stream->WriteUInt32(this->deviceMesh->GetIndex(i));
	}
	writer.EndChunk();

	writer.BeginChunk(MwMesh::SerializationId_Bones);
	writer.stream->WriteInt32(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		this->deviceMesh->GetVertexBones(i, v41, v42);
		this->SerializeVector4(*writer.stream, v41);
		this->SerializeVector4(*writer.stream, v42);
	}
	writer.EndChunk();
}

bool MwMesh::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwMesh::SerializationId_Vertices:
		{
			int numVertices = reader.stream->ReadInt32();
			if (numVertices != this->deviceMesh->GetVertexCount())
				this->deviceMesh->CreateVertexBuffer(numVertices);

			for (int i = 0; i < numVertices; i++)
				this->deviceMesh->SetVertexPosition(i, this->DeserializeVector3(*reader.stream));

			break;
		}

		case MwMesh::SerializationId_Normals:
		{
			int numVertices = reader.stream->ReadInt32();
			if (numVertices != this->deviceMesh->GetVertexCount())
				this->deviceMesh->CreateVertexBuffer(numVertices);

			for (int i = 0; i < numVertices; i++)
				this->deviceMesh->SetVertexNormal(i, this->DeserializeVector3(*reader.stream));

			break;
		}

		case MwMesh::SerializationId_TexCoords:
		{
			int numVertices = reader.stream->ReadInt32();
			if (numVertices != this->deviceMesh->GetVertexCount())
				this->deviceMesh->CreateVertexBuffer(numVertices);

			for (int i = 0; i < numVertices; i++)
				this->deviceMesh->SetVertexTexCoords(i, this->DeserializeVector2(*reader.stream));

			break;
		}

		case MwMesh::SerializationId_Triangles:
		{
			int numIndices = reader.stream->ReadInt32();
			this->deviceMesh->CreateIndexBuffer(numIndices);

			for (int i = 0; i < numIndices; i++)
				this->deviceMesh->SetIndex(i, reader.stream->ReadUInt32());

			break;
		}

		case MwMesh::SerializationId_Bones:
		{
			int numVertices = reader.stream->ReadInt32();
			if (numVertices != this->deviceMesh->GetVertexCount())
				this->deviceMesh->CreateVertexBuffer(numVertices);

			MwVector4 boneIndices, boneWeights;
			for (int i = 0; i < numVertices; i++)
			{
				boneIndices = this->DeserializeVector4(*reader.stream);
				boneWeights = this->DeserializeVector4(*reader.stream);
				this->deviceMesh->SetVertexBones(i, boneIndices, boneWeights);
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
