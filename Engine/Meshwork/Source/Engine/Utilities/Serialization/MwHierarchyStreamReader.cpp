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

#include "MwHierarchyStreamReader.h"


MwHierarchyStreamReader::MwHierarchyStreamReader(MwBaseStream &stream)
{
    this->stream = &stream;
}


MwHierarchyStreamReader::~MwHierarchyStreamReader(void)
{
}

bool MwHierarchyStreamReader::ReadChunkHeader()
{
    while (this->chunkStack.count > 0)
        if (this->chunkStack.Peek() <= this->stream->position)
			this->stream->Seek(chunkStack.Pop());
        else
            break;

    if (this->stream->length - this->stream->position < 4 + 8)
        return false;

	this->chunkId = this->stream->ReadUInt32();
	this->chunkSize = this->stream->ReadUInt64();
    this->chunkStack.Push(this->stream->position + this->chunkSize);

    return true;
}

void MwHierarchyStreamReader::SkipChunk()
{
	while (this->chunkStack.count > 0)
        if (this->chunkStack.Peek() < this->stream->position)
            this->stream->Seek(this->chunkStack.Pop());
        else
            break;

	if (this->chunkStack.count > 0)
        this->stream->Seek(this->chunkStack.Pop());
}
