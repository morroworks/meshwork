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

#include "MwTexture2D.h"

#include "..\..\..\Tools\MwMem.h"

#include "..\..\Meshwork.h"

MwTexture2D::MwTexture2D(Meshwork &context)
	: MwBaseResource()
{
	this->context = &context;

	this->typeId = MwTexture2D::classId;

	this->resourceType = MwResourceType_Texture;

	this->deviceTexture = this->context->graphicsDevice->CreateTexture();

	this->width = 0;
	this->height = 0;

	this->properties.Add(new MwProperty(MwString("Width"), this->width));
	this->properties.Add(new MwProperty(MwString("Height"), this->height));
}

MwTexture2D::~MwTexture2D(void)
{
	delete this->deviceTexture;
}

void MwTexture2D::Load(void *data, int width, int height)
{
	this->width = width;
	this->height = height;

	this->properties[MwTexture2D::propertyIndex_Width]->GetEffectiveParameter()->SetInt(width);
	this->properties[MwTexture2D::propertyIndex_Height]->GetEffectiveParameter()->SetInt(height);

	this->deviceTexture->Update(data, width, height);
}
	
void MwTexture2D::Load(MwImage &sourceImage)
{
	this->Load(sourceImage.pixelData, sourceImage.width, sourceImage.height);
}

bool MwTexture2D::Load(MwBaseStream &source)
{
	MwImage *image = this->context->CreateImage(source);
	if (image != 0)
	{
		image->SetPixelFormat(this->context->graphicsDevice->GetPixelFormat());
		this->Load(*image);
		delete image;

		return true;
	}

	return false;
}

bool MwTexture2D::Load(MwString &fileName)
{
	MwBaseStream *file = this->context->fileSystem->OpenFile(fileName);

	if (file != 0)
	{
		bool result = this->Load(*file);
		delete file;

		if (result)
		{
			this->fileName = fileName;
			return true;
		}
	}

	return false;
}

MwImage *MwTexture2D::Read()
{
	MwImage *result = new MwImage();
	result->pixelFormat = this->context->graphicsDevice->GetPixelFormat();
	result->SetSize(this->properties[MwTexture2D::propertyIndex_Width]->GetEffectiveParameter()->GetInt(), this->properties[MwTexture2D::propertyIndex_Height]->GetEffectiveParameter()->GetInt(), 1);
	this->deviceTexture->GetData(result->pixelData);

	return result;
}

void MwTexture2D::UpdateToProperties()
{
	int propertyWidth = this->properties[MwTexture2D::propertyIndex_Width]->GetEffectiveParameter()->GetInt();
	int propertyHeight = this->properties[MwTexture2D::propertyIndex_Height]->GetEffectiveParameter()->GetInt();
	if ((this->width != propertyWidth) || (this->height != propertyHeight))
	{
		this->width = propertyWidth;
		this->height = propertyHeight;

		this->deviceTexture->Update(0, this->width, this->height);
	}
}

void MwTexture2D::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	MwBaseResource::SerializeChunks(writer);

	writer.BeginChunk(MwTexture2D::SerializationId_FileName);
	writer.stream->WriteString(MwFileSystem::GetRelativeFilePath(this->context->serializationParameters.rootDir, this->fileName));
	writer.EndChunk();
}

bool MwTexture2D::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwTexture2D::SerializationId_FileName:
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
