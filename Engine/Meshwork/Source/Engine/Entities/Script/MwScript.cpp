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

#include "MwScript.h"

#include "..\..\Meshwork.h"

MwScript::MwScript(Meshwork *context)
{
	this->typeId = MwMesh::classId;
	this->resourceType = MwResourceType_Script;

	this->context = context;
        
	this->successfullyCompiled = false;
}


MwScript::~MwScript(void)
{
}

bool MwScript::CompileCode()
{
	this->successfullyCompiled = this->context->scriptBuilder.Build(&this->compiledCode, this->sourceCode);
	
	if (this->successfullyCompiled)
		this->entryPoint = this->compiledCode.position;
	else
		this->errorCode = this->context->scriptBuilder.tokens[this->context->scriptBuilder.tokenIndex].name;

	return this->successfullyCompiled;
}

bool MwScript::RunCode()
{
	if (!this->successfullyCompiled)
		return false;
	
	this->compiledCode.Seek(this->entryPoint);
	this->context->scriptProcessor.SetMemory(&this->compiledCode);
	this->context->scriptProcessor.Process();

	return true;
}

void MwScript::SerializeChunks(MwHierarchyStreamWriter &writer)
{
	MwBaseResource::SerializeChunks(writer);

	writer.BeginChunk(MwScript::SerializationId_SourceCode);
	writer.stream->WriteString(this->sourceCode);
	writer.EndChunk();

	if (this->successfullyCompiled)
	{
		writer.BeginChunk(MwScript::SerializationId_CompiledCode);
		writer.stream->WriteInt64(this->compiledCode.length);
		long long compiledCodePos = this->compiledCode.position;
		this->compiledCode.Seek(0);
		writer.stream->WriteStreamData(this->compiledCode);
		this->compiledCode.Seek(compiledCodePos);
		writer.stream->WriteInt64(this->entryPoint);
		writer.EndChunk();
	}
}

bool MwScript::DeserializeChunk(MwHierarchyStreamReader &reader)
{
	if (MwBaseResource::DeserializeChunk(reader))
		return true;

	switch (reader.chunkId)
	{
		case MwScript::SerializationId_SourceCode:
		{
			this->sourceCode = reader.stream->ReadString();
			
			if (!this->successfullyCompiled)
				this->CompileCode();

			break;
		}

		case MwScript::SerializationId_CompiledCode:
		{
			long long compiledCodeLength = reader.stream->ReadInt64();
			this->compiledCode.Resize(0);
			this->compiledCode.WriteStreamData(*reader.stream, compiledCodeLength);
			this->entryPoint = reader.stream->ReadInt64();
			this->successfullyCompiled = true;
			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}
