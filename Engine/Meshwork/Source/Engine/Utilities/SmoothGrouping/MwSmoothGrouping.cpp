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

#include "MwSmoothGrouping.h"

MwSmoothGrouping::MwSmoothGrouping(int originalFacesCount, int originalVertexCount)
{
	this->originalVerticesInfo.SetSize(originalVertexCount);
	for (int i = 0; i < this->originalVerticesInfo.count; i++)
	{
		this->originalVerticesInfo[i].accumulatedSmoothingGroups = 0;
		this->originalVerticesInfo[i].indices.EnsureCapacity(4);
	}

	this->vertexIndices.EnsureCapacity(originalVertexCount);

	this->faces.SetSize(originalFacesCount);
	for (int i = 0; i < this->faces.count; i++)
	{
		this->faces[i].smoothingGroups = 0;
	}
}


MwSmoothGrouping::~MwSmoothGrouping(void)
{
}

void MwSmoothGrouping::SetFaceSmoothingGroups(int faceIndex, unsigned long long smoothingGroupFlags)
{
	this->faces[faceIndex].smoothingGroups = smoothingGroupFlags;
}

int MwSmoothGrouping::AddFaceVertex(int faceIndex, int originalVertexIndex)
{
	MwSmoothGroupingFace *face = &this->faces[faceIndex];

	MwSmoothGroupingVertex vertex;
	vertex.accumulatedSmoothingGroups = face->smoothingGroups;

	if ((vertex.accumulatedSmoothingGroups & this->originalVerticesInfo[originalVertexIndex].accumulatedSmoothingGroups) == 0)
	{
		int newVertexIndex = this->vertexIndices.count;
		vertex.index = originalVertexIndex;
		face->indices.Add(newVertexIndex);
		this->vertexIndices.Add(vertex);
		this->originalVerticesInfo[originalVertexIndex].indices.Add(newVertexIndex);
	}
	else
	{
		int indicesCount = this->originalVerticesInfo[originalVertexIndex].indices.count;
		for (int i = 0; i < indicesCount; i++)
		{
			vertex.index = this->originalVerticesInfo[originalVertexIndex].indices[i];
			if ((vertex.accumulatedSmoothingGroups & this->vertexIndices[vertex.index].accumulatedSmoothingGroups) != 0)
			{
				this->vertexIndices[vertex.index].accumulatedSmoothingGroups |= vertex.accumulatedSmoothingGroups;
				face->indices.Add(vertex.index);
				break;
			}
		}
	}

	this->originalVerticesInfo[originalVertexIndex].accumulatedSmoothingGroups |= vertex.accumulatedSmoothingGroups;

	return vertex.index;
}
