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

#include "MwSound.h"

#include "..\..\Meshwork.h"

MwSound::MwSound(Meshwork *context)
{
	this->context = context;

	this->typeId = MwSound::classId;
	this->resourceType = MwResourceType_Sound;

	this->deviceSound = this->context->audioDevice->CreateSound();

	this->mediaSource = 0;
	this->mediaSourceStream = 0;
}


MwSound::~MwSound(void)
{
	if (this->mediaSourceStream != 0)
		delete this->mediaSourceStream;
	if (this->mediaSource != 0)
		delete this->mediaSource;

	delete this->deviceSound;
}

void MwSound::Load(MwSoundMedia *sourceMedia)
{
	this->deviceSound->SetMediaSource(sourceMedia);

	if (this->deviceSound->IsStreaming())
	{
		this->mediaSourceStream = sourceMedia->sourceStream;
		this->mediaSource = sourceMedia;
	}
	else
	{
		delete sourceMedia->sourceStream;
		delete sourceMedia;

		this->mediaSourceStream = 0;
		this->mediaSource = 0;
	}
}

bool MwSound::Load(MwBaseStream *source)
{
	MwSoundMedia *sourceMedia = this->context->CreateSoundMedia(*source);

	if (sourceMedia == 0)
		return false;

	this->Load(sourceMedia);

	return true;
}

bool MwSound::Load(MwString &fileName)
{
	MwBaseStream *sourceStream = this->context->fileSystem->OpenFile(fileName);
	if (sourceStream == 0)
		return false;

	if (this->Load(sourceStream))
	{
		this->fileName = fileName;
		return true;
	}

	return false;
}

void MwSound::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	MwBaseResource::SerializeChunks(writer);

	writer.BeginChunk(MwSound::SerializationId_FileName);
	writer.stream->WriteString(MwFileSystem::GetRelativeFilePath(this->context->serializationParameters.rootDir, this->fileName));
	writer.EndChunk();
}

bool MwSound::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwSound::SerializationId_FileName:
		{
			MwString fileName = reader.stream->ReadString();
			this->Load(MwFileSystem::MergePaths(this->context->serializationParameters.rootDir, fileName));
			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}
