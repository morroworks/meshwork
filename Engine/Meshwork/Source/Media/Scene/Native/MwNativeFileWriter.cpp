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

#include "MwNativeFileWriter.h"

#include "..\..\..\Engine\Meshwork.h"

#include "MwNativeFileId.h"

#include "..\..\..\Engine\Utilities\Serialization\MwHierarchyStreamWriter.h"

MwNativeFileWriter::MwNativeFileWriter(Meshwork *context)
{
    this->context = context;
}


MwNativeFileWriter::~MwNativeFileWriter(void)
{
}

void MwNativeFileWriter::Write(MwBaseStream &destination)
{
    MwHierarchyStreamWriter writer(destination);
	
	writer.BeginChunk(MwNativeFileID::Main);

	writer.BeginChunk(MwNativeFileID::Header);

	writer.BeginChunk(MwNativeFileID::Header_String);
	writer.stream->WriteString(MwString("Meshwork"));
	writer.EndChunk();

	writer.BeginChunk(MwNativeFileID::Header_Ver);
	writer.stream->WriteUInt32(0x09000000);
	writer.EndChunk();

	writer.EndChunk();
	// Header

	writer.BeginChunk(MwNativeFileID::Resources);

	for (int i = 0; i < this->context->resources.count; i++)
	{
		writer.BeginChunk(MwNativeFileID::ResourceSerializationWrap);
		this->context->SerializeResource(&destination, this->context->resources[i]);
		writer.EndChunk();
	}

	writer.EndChunk();
	// Resources

	writer.BeginChunk(MwNativeFileID::RootBranch);
	writer.stream->WriteInt64(this->context->root->id);
	writer.EndChunk();


	writer.EndChunk();
	// Main
}
