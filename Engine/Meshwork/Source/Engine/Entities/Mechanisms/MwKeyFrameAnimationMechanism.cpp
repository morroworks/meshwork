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

#include "MwKeyframeAnimationMechanism.h"

#include "..\..\Meshwork.h"

#include "..\..\..\Media\Scene\Native\MwNativeFileReader.h"

#include "KeyFrameAnimation\MwKeyFrameRotationAxis.h"

MwKeyframeAnimationMechanism::MwKeyframeAnimationMechanism(Meshwork *context)
	: MwBaseMechanism()
{
	this->typeId = MwKeyframeAnimationMechanism::classId;

	this->context = context;

	this->parameter.SetType(MwParameterType_None);

	this->properties.Add(new MwProperty("Frame", 0.0f));
    this->properties.Add(new MwProperty("Transform", MwParameterType_ReferenceTransform, 0));
}


MwKeyframeAnimationMechanism::~MwKeyframeAnimationMechanism(void)
{
	for (int i = 0; i < this->keyFramesTracks.count; i++)
		delete this->keyFramesTracks[i];
}

bool MwKeyframeAnimationMechanism::Process(float deltaTime)
{
	float time = *(float*)this->properties[0]->GetEffectiveParameter()->value;
    MwTransform *transform = (MwTransform*)this->properties[1]->GetEffectiveParameter()->value;

	if (this->keyFramesTracks.count == 0)
	{
		MwMatrix::CreateIdentity(transform->keyframe);
		return true;
	}

	this->keyFramesTracks[0]->GetTransform(transform->keyframe, time);
	
	MwMatrix m;
	for (int i = 1; i < this->keyFramesTracks.count; i++)
	{
		this->keyFramesTracks[i]->GetTransform(m, time);
		MwMatrix::Multiply(transform->keyframe, transform->keyframe, m);
	}

    return true;
}

void MwKeyframeAnimationMechanism::BuildRotationAxisTrack(MwKeyFramesTrack *rotationAxisTrack)
{
	MwMatrix transform, rotationMatrix;

	MwMatrix::CreateIdentity(transform);
	int count = rotationAxisTrack->count;
    for (int i = 0; i < count; i++)
    {
		MwMatrix::CreateRotationAxis(rotationMatrix, ((MwKeyFrameRotationAxis*)rotationAxisTrack->Get(i))->axis, ((MwKeyFrameRotationAxis*)rotationAxisTrack->Get(i))->angle);
        MwMatrix::Multiply(transform, transform, rotationMatrix);
        MwMatrix::Copy(((MwKeyFrameRotationAxis*)rotationAxisTrack->Get(i))->previousTransform, transform);
    }
}

void MwKeyframeAnimationMechanism::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	MwBaseMechanism::SerializeChunks(writer);

	writer.BeginChunk(MwKeyframeAnimationMechanism::SerializationId_KeyFrameTracks);

	for (int trackIndex = 0; trackIndex < this->keyFramesTracks.count; trackIndex++)
	{
		writer.BeginChunk(MwKeyframeAnimationMechanism::SerializationId_KeyFrameTrack);

		int keyFramesCount = this->keyFramesTracks[trackIndex]->count;
		if (keyFramesCount > 0)
		{
			int typeId = this->keyFramesTracks[trackIndex]->Get(0)->typeId;
			writer.BeginChunk(MwKeyframeAnimationMechanism::SerializationId_KeyFrameTrackFrames);
			writer.stream->WriteInt32(typeId);

			for (int keyFrameIndex = 0; keyFrameIndex < keyFramesCount; keyFrameIndex++)
			{
				if (this->keyFramesTracks[trackIndex]->Get(keyFrameIndex)->typeId != typeId)
				{
					writer.EndChunk();
					writer.BeginChunk(MwKeyframeAnimationMechanism::SerializationId_KeyFrameTrackFrames);
					writer.stream->WriteInt32(typeId);

					typeId = this->keyFramesTracks[trackIndex]->Get(keyFrameIndex)->typeId;
				}

				this->keyFramesTracks[trackIndex]->Get(keyFrameIndex)->Serialize(*writer.stream);
			}

			writer.EndChunk();
			// SerializationId_KeyFrameTrackFrames
		}

		writer.EndChunk();
		// SerializationId_KeyFrameTrack
	}

	writer.EndChunk();
	// SerializationId_KeyFrameTracks
}

bool MwKeyframeAnimationMechanism::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseMechanism::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwKeyframeAnimationMechanism::SerializationId_KeyFrameTracks:
		{
			break;
		}

		case MwKeyframeAnimationMechanism::SerializationId_KeyFrameTrack:
		{
			this->currentDeserializationTrack = this->keyFramesTracks.Add(new MwKeyFramesTrack());
			break;
		}

		case MwKeyframeAnimationMechanism::SerializationId_KeyFrameTrackFrames:
		{
			long long chunkEnd = reader.stream->position + reader.chunkSize;

			int typeId = reader.stream->ReadInt32();
		
			while (reader.stream->position < chunkEnd)
			{
				MwKeyFrame *keyFrame = (MwKeyFrame*)this->context->CreateEntity(typeId);
				if (keyFrame == 0)
				{
					reader.SkipChunk();
					break;
				}

				keyFrame->Deserialize(*reader.stream);
				this->currentDeserializationTrack->Add(keyFrame);
			}

			if (typeId == MwKeyFrameRotationAxis::classId)
				this->BuildRotationAxisTrack(this->currentDeserializationTrack);

			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}
