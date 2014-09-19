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

#include "MwTransform.h"


MwTransform::MwTransform(void)
	: MwBaseResource()
{
	this->typeId = MwTransform::classId;
    this->resourceType = MwResourceType_Transform;

    this->properties.Add(new MwProperty(MwString("Bone"), false));
    this->properties.Add(new MwProperty(MwString("Bone Index"), 0));
}


MwTransform::~MwTransform(void)
{
}


void MwTransform::InsertTransformSlot(MwTransformOperation operation, int index)
{
    int numProperties = this->properties.count;

    int propertyIndex;
	if (index < transformSlots.count)
        propertyIndex = transformSlots[index].propertyFirst;
    else
        propertyIndex = numProperties;

    int propertyFirst = propertyIndex;

    switch (operation)
    {
        case MwTransformOperation_Translate:
            this->properties.Insert(propertyIndex++, new MwProperty("Translate X", 0.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Translate Y", 0.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Translate Z", 0.0f));
            break;

        case MwTransformOperation_RotateX:
            this->properties.Insert(propertyIndex++, new MwProperty("Rotate X", 0.0f));
            break;

        case MwTransformOperation_RotateY:
            this->properties.Insert(propertyIndex++, new MwProperty("Rotate Y", 0.0f));
            break;

        case MwTransformOperation_RotateZ:
            this->properties.Insert(propertyIndex++, new MwProperty("Rotate Z", 0.0f));
            break;

        case MwTransformOperation_Scale:
            this->properties.Insert(propertyIndex++, new MwProperty("Scale X", 1.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Scale Y", 1.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Scale Z", 1.0f));
            break;

        case MwTransformOperation_TranslateAbsolute:
            this->properties.Insert(propertyIndex++, new MwProperty("Translate AbsoluteX", 0.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Translate AbsoluteY", 0.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Translate AbsoluteZ", 0.0f));
            break;

        case MwTransformOperation_RotateAbsoluteX:
            this->properties.Insert(propertyIndex++, new MwProperty("Rotate AbsoluteX", 0.0f));
            break;

        case MwTransformOperation_RotateAbsoluteY:
            this->properties.Insert(propertyIndex++, new MwProperty("Rotate AbsoluteY", 0.0f));
            break;

        case MwTransformOperation_RotateAbsoluteZ:
            this->properties.Insert(propertyIndex++, new MwProperty("Rotate AbsoluteZ", 0.0f));
            break;

        case MwTransformOperation_ScaleAbsolute:
            this->properties.Insert(propertyIndex++, new MwProperty("Scale AbsoluteX", 1.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Scale AbsoluteY", 1.0f));
            this->properties.Insert(propertyIndex++, new MwProperty("Scale AbsoluteZ", 1.0f));
            break;
    }

    int numNewProperties = properties.count - numProperties;
    transformSlots.Insert(index, MwTransformSlot(operation, propertyFirst, numNewProperties));

    int count = transformSlots.count;
    for (int i = index + 1; i < count; i++)
        transformSlots[i].propertyFirst += numNewProperties;
}

int MwTransform::AddTransformSlot(MwTransformOperation operation)
{
    this->InsertTransformSlot(operation, transformSlots.count);
    return transformSlots.count - 1;
}

void MwTransform::RemoveTransformSlot(int index)
{
    int count = this->transformSlots.count;
    for (int i = index + 1; i < count; i++)
        this->transformSlots[i].propertyFirst -= this->transformSlots[i].propertyCount;

    this->properties.RemoveRange(this->transformSlots[index].propertyFirst, this->transformSlots[index].propertyCount);
	this->transformSlots.RemoveAt(index);
}

void MwTransform::ClearTransformSlots()
{
    this->transformSlots.Clear();
    this->properties.Clear();
}

void MwTransform::Process()
{
    MwMatrix::Copy(this->pivotless, this->manual);

    int transformsCount = transformSlots.count;
    if (transformsCount != 0)
    {
		int propertyIndex = this->transformSlots[0].propertyFirst;
        for (int i = 0; i < transformsCount; i++)
		{
            switch (transformSlots[i].operation)
            {
                case MwTransformOperation_Translate:
                    MwMatrix::CreateTranslation(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value),
												   *(float*)(this->properties[propertyIndex + 1]->GetEffectiveParameter()->value),
												   *(float*)(this->properties[propertyIndex + 2]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, m, pivotless);

                    propertyIndex += 3;
                    break;

                case MwTransformOperation_RotateX:
                    MwMatrix::CreateRotationX(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, m, pivotless);

                    propertyIndex++;
                    break;

                case MwTransformOperation_RotateY:
                    MwMatrix::CreateRotationY(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, m, pivotless);

                    propertyIndex++;
                    break;

                case MwTransformOperation_RotateZ:
                    MwMatrix::CreateRotationZ(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, m, pivotless);

                    propertyIndex++;
                    break;

                case MwTransformOperation_Scale:
                    MwMatrix::CreateScale(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value),
                                             *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value),
                                             *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, m, pivotless);

                    propertyIndex += 3;
                    break;

                case MwTransformOperation_TranslateAbsolute:
                    MwMatrix::CreateTranslation(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value),
                                            	   *(float*)(this->properties[propertyIndex + 1]->GetEffectiveParameter()->value),
                                            	   *(float*)(this->properties[propertyIndex + 2]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, pivotless, m);

                    propertyIndex += 3;
                    break;

                case MwTransformOperation_RotateAbsoluteX:
                    MwMatrix::CreateRotationX(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, pivotless, m);

                    propertyIndex++;
                    break;

                case MwTransformOperation_RotateAbsoluteY:
                    MwMatrix::CreateRotationY(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, pivotless, m);

                    propertyIndex++;
                    break;

                case MwTransformOperation_RotateAbsoluteZ:
                    MwMatrix::CreateRotationZ(m, *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, pivotless, m);

                    propertyIndex++;
                    break;

                case MwTransformOperation_ScaleAbsolute:
                    MwMatrix::CreateScale(m,  *(float*)(this->properties[propertyIndex]->GetEffectiveParameter()->value),
                                      		  *(float*)(this->properties[propertyIndex + 1]->GetEffectiveParameter()->value),
                                      		  *(float*)(this->properties[propertyIndex + 2]->GetEffectiveParameter()->value));
                    MwMatrix::Multiply(pivotless, pivotless, m);

                    propertyIndex += 3;
                    break;
            }
		}
    }

    MwMatrix::Multiply(pivotless, pivotless, keyframe);
    MwMatrix::Multiply(matrix, pivot, pivotless);
}

void MwTransform::SerializeMatrix(MwBaseStream &stream, MwMatrix &matrix)
{
	stream.WriteFloat(matrix._11);
	stream.WriteFloat(matrix._12);
	stream.WriteFloat(matrix._13);
	stream.WriteFloat(matrix._14);
	stream.WriteFloat(matrix._21);
	stream.WriteFloat(matrix._22);
	stream.WriteFloat(matrix._23);
	stream.WriteFloat(matrix._24);
	stream.WriteFloat(matrix._31);
	stream.WriteFloat(matrix._32);
	stream.WriteFloat(matrix._33);
	stream.WriteFloat(matrix._34);
	stream.WriteFloat(matrix._41);
	stream.WriteFloat(matrix._42);
	stream.WriteFloat(matrix._43);
	stream.WriteFloat(matrix._44);
}

void MwTransform::DeserializeMatrix(MwMatrix &result, MwBaseStream &stream)
{
	result._11 = stream.ReadFloat();
	result._12 = stream.ReadFloat();
	result._13 = stream.ReadFloat();
	result._14 = stream.ReadFloat();
	result._21 = stream.ReadFloat();
	result._22 = stream.ReadFloat();
	result._23 = stream.ReadFloat();
	result._24 = stream.ReadFloat();
	result._31 = stream.ReadFloat();
	result._32 = stream.ReadFloat();
	result._33 = stream.ReadFloat();
	result._34 = stream.ReadFloat();
	result._41 = stream.ReadFloat();
	result._42 = stream.ReadFloat();
	result._43 = stream.ReadFloat();
	result._44 = stream.ReadFloat();
}

void MwTransform::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	writer.BeginChunk(MwTransform::SerializationId_Pivot);
	this->SerializeMatrix(*writer.stream, this->pivot);
	writer.EndChunk();

	writer.BeginChunk(MwTransform::SerializationId_Manual);
	this->SerializeMatrix(*writer.stream, this->manual);
	writer.EndChunk();

	writer.BeginChunk(MwTransform::SerializationId_BindInverse);
	this->SerializeMatrix(*writer.stream, this->boneBindPoseInverse);
	writer.EndChunk();

	writer.BeginChunk(MwTransform::SerializationId_TransformSlots);
	for (int i = 0; i < this->transformSlots.count; i++)
	{
		writer.BeginChunk(MwTransform::SerializationId_TransformSlot);
		writer.stream->WriteInt16(this->transformSlots[i].operation);
		writer.EndChunk();
	}
	writer.EndChunk();

	// Make base serialization at and, because transformation slots create properties, which need to be filled afterwards
	MwBaseResource::SerializeChunks(writer);
}

bool MwTransform::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwTransform::SerializationId_Pivot:
		{
			this->DeserializeMatrix(this->pivot, *reader.stream);
			break;
		}

		case MwTransform::SerializationId_Manual:
		{
			this->DeserializeMatrix(this->manual, *reader.stream);
			break;
		}

		case MwTransform::SerializationId_BindInverse:
		{
			this->DeserializeMatrix(this->boneBindPoseInverse, *reader.stream);
			break;
		}

		case MwTransform::SerializationId_TransformSlots:
		{
			break;
		}

		case MwTransform::SerializationId_TransformSlot:
		{
			this->AddTransformSlot((MwTransformOperation)reader.stream->ReadInt16());
			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}