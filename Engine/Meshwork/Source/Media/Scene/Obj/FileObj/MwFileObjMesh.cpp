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

#include "MwFileObjMesh.h"


MwFileObjMesh::MwFileObjMesh(void)
{
}


MwFileObjMesh::~MwFileObjMesh(void)
{
	for (int i = 0; i < this->faces.count; i++)
		delete this->faces[i];

	for (int i = 0; i < this->bufferedFaces.count; i++)
		delete this->bufferedFaces[i];
}

void MwFileObjMesh::CreateBuffers()
{
	for (int i = 0; i < this->bufferedFaces.count; i++)
		delete this->bufferedFaces[i];

	this->bufferedFaces.SetSize(this->faces.count);
	this->bufferedVertices.SetSize(0);

	for (int faceIndex = 0; faceIndex < this->faces.count; faceIndex++)
	{
		int numFaceVertices = this->faces[faceIndex]->vertices.count;

		this->bufferedFaces[faceIndex] = new MwFileObjBufferedFace();
		this->bufferedFaces[faceIndex]->bufferedVertexIndices.SetSize(numFaceVertices);

		for (int faceVertexIndex = 0; faceVertexIndex < numFaceVertices; faceVertexIndex++)
		{
			MwFileObjFaceVertex *faceVertex = &(*this->faces[faceIndex]).vertices[faceVertexIndex];

			int bufferedVertexIndex = this->FindEquivalentBufferedVertexIndex(faceVertex);
			if (bufferedVertexIndex == -1)
			{
				this->bufferedVertices.Add(*faceVertex);

				bufferedVertexIndex = this->bufferedVertices.count - 1;
			}

			this->bufferedFaces[faceIndex]->smoothingGroups = this->faces[faceIndex]->smoothingGroups;
			this->bufferedFaces[faceIndex]->bufferedVertexIndices[faceVertexIndex] = bufferedVertexIndex;
		}
	}
}

int MwFileObjMesh::FindEquivalentBufferedVertexIndex(MwFileObjFaceVertex *faceVertex)
{
	for (int i = 0; i < this->bufferedVertices.count; i++)
	{
		MwFileObjFaceVertex *bufferedVertex = &this->bufferedVertices[i];
		if ((faceVertex->vertexIndex == bufferedVertex->vertexIndex) && (faceVertex->texCoordIndex == bufferedVertex->texCoordIndex) && (faceVertex->normalIndex == bufferedVertex->normalIndex))
			return i;
	}
	
	return -1;
}
