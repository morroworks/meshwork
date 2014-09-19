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

#include "SrRenderThread.h"

#include "Soras.h"

#include "Primitive\SrUnit.h"

SrRenderThread::SrRenderThread(Soras *soras)
{
	this->soras = soras;
}


SrRenderThread::~SrRenderThread(void)
{
}

int SrRenderThread::ComputeVertices(void *renderThread)
{
    SrRenderThread *thread = (SrRenderThread*)renderThread;
	Soras *soras = thread->soras;

	int wdiv2 = (soras->renderSurface->width >> 1);
    int hdiv2 = (soras->renderSurface->height >> 1);

	if (soras->skeletalAnimationOn)
	{
		for (int i = thread->vertexStart; i <= thread->vertexEnd; i++)
		{
			SrVertex *v1 = &soras->mesh->vertices[i];
			SrVertex *v2 = &soras->mesh->transformedVertices[i];

			SrVector4Int boneIndices = v1->boneIndices;
			SrVector4 boneWeights = v1->boneWeights;

			SrMatrix transform;
			SrMatrix bone = soras->bones[boneIndices.x];
			transform._11 = bone._11 * boneWeights.x;
			transform._12 = bone._12 * boneWeights.x;
			transform._13 = bone._13 * boneWeights.x;
			transform._21 = bone._21 * boneWeights.x;
			transform._22 = bone._22 * boneWeights.x;
			transform._23 = bone._23 * boneWeights.x;
			transform._31 = bone._31 * boneWeights.x;
			transform._32 = bone._32 * boneWeights.x;
			transform._33 = bone._33 * boneWeights.x;
			transform._41 = bone._41 * boneWeights.x;
			transform._42 = bone._42 * boneWeights.x;
			transform._43 = bone._43 * boneWeights.x;
			if (boneWeights.y != 0.0f)
			{
				bone = soras->bones[boneIndices.y];
				transform._11 += bone._11 * boneWeights.y;
				transform._12 += bone._12 * boneWeights.y;
				transform._13 += bone._13 * boneWeights.y;
				transform._21 += bone._21 * boneWeights.y;
				transform._22 += bone._22 * boneWeights.y;
				transform._23 += bone._23 * boneWeights.y;
				transform._31 += bone._31 * boneWeights.y;
				transform._32 += bone._32 * boneWeights.y;
				transform._33 += bone._33 * boneWeights.y;
				transform._41 += bone._41 * boneWeights.y;
				transform._42 += bone._42 * boneWeights.y;
				transform._43 += bone._43 * boneWeights.y;
				if (boneWeights.z != 0.0f)
				{
					bone = soras->bones[boneIndices.z];
					transform._11 += bone._11 * boneWeights.z;
					transform._12 += bone._12 * boneWeights.z;
					transform._13 += bone._13 * boneWeights.z;
					transform._21 += bone._21 * boneWeights.z;
					transform._22 += bone._22 * boneWeights.z;
					transform._23 += bone._23 * boneWeights.z;
					transform._31 += bone._31 * boneWeights.z;
					transform._32 += bone._32 * boneWeights.z;
					transform._33 += bone._33 * boneWeights.z;
					transform._41 += bone._41 * boneWeights.z;
					transform._42 += bone._42 * boneWeights.z;
					transform._43 += bone._43 * boneWeights.z;
					if (boneWeights.w != 0.0f)
					{
						bone = soras->bones[boneIndices.w];
						transform._11 += bone._11 * boneWeights.w;
						transform._12 += bone._12 * boneWeights.w;
						transform._13 += bone._13 * boneWeights.w;
						transform._21 += bone._21 * boneWeights.w;
						transform._22 += bone._22 * boneWeights.w;
						transform._23 += bone._23 * boneWeights.w;
						transform._31 += bone._31 * boneWeights.w;
						transform._32 += bone._32 * boneWeights.w;
						transform._33 += bone._33 * boneWeights.w;
						transform._41 += bone._41 * boneWeights.w;
						transform._42 += bone._42 * boneWeights.w;
						transform._43 += bone._43 * boneWeights.w;
					}
				}
			}

			v2->position.x = v1->position.x * transform._11 +
							 v1->position.y * transform._21 +
							 v1->position.z * transform._31 +
											  transform._41;
			v2->position.y = v1->position.x * transform._12 +
							 v1->position.y * transform._22 +
							 v1->position.z * transform._32 +
											  transform._42;
			v2->position.z = v1->position.x * transform._13 +
							 v1->position.y * transform._23 +
							 v1->position.z * transform._33 +
											  transform._43;

			// Normals should be calculated with the invert transpose of transform in case of a non-uniform scaling. This is omitted for performance reasons
			v2->normal.x = v1->normal.x * transform._11 +
						   v1->normal.y * transform._21 +
						   v1->normal.z * transform._31;
			v2->normal.y = v1->normal.x * transform._12 +
						   v1->normal.y * transform._22 +
						   v1->normal.z * transform._32;
			v2->normal.z = v1->normal.x * transform._13 +
						   v1->normal.y * transform._23 +
						   v1->normal.z * transform._33;

			if (soras->normalizeNormals)
				SrVector3::Normalize(v2->normal);

			v2->texCoords.x = v1->texCoords.x;
			v2->texCoords.y = v1->texCoords.y;
			v2->color.a = 0;
			v2->color.r = 0;
			v2->color.g = 0;
			v2->color.b = 0;

			thread->shaderReg_Point = v2;

			thread->shaderTextureIndex = 0;
			for (int vop = 0; vop < soras->vertexOps.count; vop++)
				soras->vertexOps[vop](thread);

			SrVector3 screenPos;

			screenPos.x = v2->position.x * soras->viewProjectionMatrix._11 +
						  v2->position.y * soras->viewProjectionMatrix._21 +
						  v2->position.z * soras->viewProjectionMatrix._31 +
										   soras->viewProjectionMatrix._41;
			screenPos.y = v2->position.x * soras->viewProjectionMatrix._12 +
						  v2->position.y * soras->viewProjectionMatrix._22 +
						  v2->position.z * soras->viewProjectionMatrix._32 +
										   soras->viewProjectionMatrix._42;
			screenPos.z = v2->position.x * soras->viewProjectionMatrix._13 +
						  v2->position.y * soras->viewProjectionMatrix._23 +
						  v2->position.z * soras->viewProjectionMatrix._33 +
										   soras->viewProjectionMatrix._43;
			float w = v2->position.x * soras->viewProjectionMatrix._14 +
					  v2->position.y * soras->viewProjectionMatrix._24 +
					  v2->position.z * soras->viewProjectionMatrix._34 +
									   soras->viewProjectionMatrix._44;

			v2->positionIntScreen.x = wdiv2 + (int)(wdiv2 * screenPos.x / w);
			v2->positionIntScreen.y = hdiv2 + (int)(hdiv2 * screenPos.y / w);

			if (screenPos.z < 0)
				v2->positionIntScreen.z = 0;
			else
				v2->positionIntScreen.z = (screenPos.z - (float)(1 << 14)) * (float)(1 << 4);                

		}
	}

	else
	
	{
		for (int i = thread->vertexStart; i <= thread->vertexEnd; i++)
		{
			SrVertex *v1 = &soras->mesh->vertices[i];
			SrVertex *v2 = &soras->mesh->transformedVertices[i];

			v2->position.x = v1->position.x * soras->worldMatrix._11 +
							 v1->position.y * soras->worldMatrix._21 +
							 v1->position.z * soras->worldMatrix._31 +
											 soras->worldMatrix._41;
			v2->position.y = v1->position.x * soras->worldMatrix._12 +
							 v1->position.y * soras->worldMatrix._22 +
							 v1->position.z * soras->worldMatrix._32 +
											 soras->worldMatrix._42;
			v2->position.z = v1->position.x * soras->worldMatrix._13 +
							 v1->position.y * soras->worldMatrix._23 +
							 v1->position.z * soras->worldMatrix._33 +
											 soras->worldMatrix._43;

			v2->normal.x = v1->normal.x * soras->worldMatrixNormals._11 +
						   v1->normal.y * soras->worldMatrixNormals._21 +
						   v1->normal.z * soras->worldMatrixNormals._31;
			v2->normal.y = v1->normal.x * soras->worldMatrixNormals._12 +
						   v1->normal.y * soras->worldMatrixNormals._22 +
						   v1->normal.z * soras->worldMatrixNormals._32;
			v2->normal.z = v1->normal.x * soras->worldMatrixNormals._13 +
						   v1->normal.y * soras->worldMatrixNormals._23 +
						   v1->normal.z * soras->worldMatrixNormals._33;

			if (soras->normalizeNormals)
				SrVector3::Normalize(v2->normal);

			v2->texCoords.x = v1->texCoords.x;
			v2->texCoords.y = v1->texCoords.y;
			v2->color.a = 0;
			v2->color.r = 0;
			v2->color.g = 0;
			v2->color.b = 0;

			thread->shaderReg_Point = v2;

			thread->shaderTextureIndex = 0;
			for (int vop = 0; vop < soras->vertexOps.count; vop++)
				soras->vertexOps[vop](thread);

			SrVector3 screenPos;

			screenPos.x = v2->position.x * soras->viewProjectionMatrix._11 +
						  v2->position.y * soras->viewProjectionMatrix._21 +
						  v2->position.z * soras->viewProjectionMatrix._31 +
										   soras->viewProjectionMatrix._41;
			screenPos.y = v2->position.x * soras->viewProjectionMatrix._12 +
						  v2->position.y * soras->viewProjectionMatrix._22 +
						  v2->position.z * soras->viewProjectionMatrix._32 +
										   soras->viewProjectionMatrix._42;
			screenPos.z = v2->position.x * soras->viewProjectionMatrix._13 +
						  v2->position.y * soras->viewProjectionMatrix._23 +
						  v2->position.z * soras->viewProjectionMatrix._33 +
										   soras->viewProjectionMatrix._43;
			float w = v2->position.x * soras->viewProjectionMatrix._14 +
					  v2->position.y * soras->viewProjectionMatrix._24 +
					  v2->position.z * soras->viewProjectionMatrix._34 +
									   soras->viewProjectionMatrix._44;

			v2->positionIntScreen.x = wdiv2 + (int)(wdiv2 * screenPos.x / w);
			v2->positionIntScreen.y = hdiv2 + (int)(hdiv2 * screenPos.y / w);

			if (screenPos.z < 0)
				v2->positionIntScreen.z = 0;
			else
				v2->positionIntScreen.z = (screenPos.z - (float)(1 << 14)) * (float)(1 << 4);                

		}
	}

	return 0;
}

int SrRenderThread::RenderPrimitives(void *renderThread)
{
    SrRenderThread *thread = (SrRenderThread*)renderThread;
	Soras *soras = thread->soras;

    for (int i = thread->primitiveStart; i <= thread->primitiveEnd; i++)
    {
        int index = soras->mesh->visiblePrimitives[i];

        SrVertex *v1 = &soras->mesh->transformedVertices[soras->mesh->indices[index]];
        SrVertex *v2 = &soras->mesh->transformedVertices[soras->mesh->indices[index + 1]];
        SrVertex *v3 = &soras->mesh->transformedVertices[soras->mesh->indices[index + 2]];

        int width = soras->renderSurface->width,
			height = soras->renderSurface->height;

		bool render =
            !(((v1->positionIntScreen.x < 0) &&
               (v2->positionIntScreen.x < 0) &&
               (v3->positionIntScreen.x < 0)) ||
			  ((v1->positionIntScreen.x >= width) &&
               (v2->positionIntScreen.x >= width) &&
               (v3->positionIntScreen.x >= width)) ||
              ((v1->positionIntScreen.y < 0) &&
               (v2->positionIntScreen.y < 0) &&
               (v3->positionIntScreen.y < 0)) ||
              ((v1->positionIntScreen.y >= height) &&
               (v2->positionIntScreen.y >= height) &&
               (v3->positionIntScreen.y >= height)) ||
              ((v1->positionIntScreen.z == 0) ||
               (v2->positionIntScreen.z == 0) ||
               (v3->positionIntScreen.z == 0)));

        if (render)
            thread->RenderPrimitive(v1, v2, v3);
    }
			
	return 0;
}

void SrRenderThread::RenderPrimitive(SrVertex *V1, SrVertex *V2, SrVertex *V3)
{
	this->soras->numVisiblePrimitives++;

    SrVertex *v1, *v2, *v3;

    if (V1->positionIntScreen.y < V2->positionIntScreen.y)
        if (V1->positionIntScreen.y < V3->positionIntScreen.y)
        {
            v1 = V1;
            if (V2->positionIntScreen.y < V3->positionIntScreen.y)
            {
                v2 = V2;
                v3 = V3;
            }
            else
            {
                v2 = V3;
                v3 = V2;
            }
        }
        else
        {
            v1 = V3;
            if (V1->positionIntScreen.y < V2->positionIntScreen.y)
            {
                v2 = V1;
                v3 = V2;
            }
            else
            {
                v2 = V2;
                v3 = V1;
            }
        }
    else
        if (V2->positionIntScreen.y < V3->positionIntScreen.y)
        {
            v1 = V2;
            if (V1->positionIntScreen.y < V3->positionIntScreen.y)
            {
                v2 = V1;
                v3 = V3;
            }
            else
            {
                v2 = V3;
                v3 = V1;
            }
        }
        else
        {
            v1 = V3;
            if (V1->positionIntScreen.y < V2->positionIntScreen.y)
            {
                v2 = V1;
                v3 = V2;
            }
            else
            {
                v2 = V2;
                v3 = V1;
            }
        }

    int l2DeltaY = v3->positionIntScreen.y - v1->positionIntScreen.y;
    int l2UDeltaY = MwMath::Abs(l2DeltaY);
    if (l2UDeltaY == 0)
        return;
    int l2UDiv = SrUnit::high / l2UDeltaY;
    int l2UMod = SrUnit::high % l2UDeltaY;
    int l2UError = l2UDeltaY >> 1;
    int l2U = 0;

    SrVertex l1deltaVertex, l2deltaVertex,
			 l1scanVertex, l2scanVertex;

	l2deltaVertex.positionIntScreen.x = v3->positionIntScreen.x - v1->positionIntScreen.x;
    l2deltaVertex.positionIntScreen.z = (v3->positionIntScreen.z - v1->positionIntScreen.z) / l2UDeltaY;
    l2deltaVertex.texCoords.x = v3->texCoords.x - v1->texCoords.x;
    l2deltaVertex.texCoords.y = v3->texCoords.y - v1->texCoords.y;
    l2deltaVertex.color.a = v3->color.a - v1->color.a;
    l2deltaVertex.color.r = v3->color.r - v1->color.r;
    l2deltaVertex.color.g = v3->color.g - v1->color.g;
    l2deltaVertex.color.b = v3->color.b - v1->color.b;
    l2deltaVertex.position.x = (v3->position.x - v1->position.x) / l2UDeltaY;
    l2deltaVertex.position.y = (v3->position.y - v1->position.y) / l2UDeltaY;
    l2deltaVertex.position.z = (v3->position.z - v1->position.z) / l2UDeltaY;
    l2deltaVertex.normal.x = (v3->normal.x - v1->normal.x) / l2UDeltaY;
    l2deltaVertex.normal.y = (v3->normal.y - v1->normal.y) / l2UDeltaY;
    l2deltaVertex.normal.z = (v3->normal.z - v1->normal.z) / l2UDeltaY;

    l2scanVertex.position = v1->position;
    l2scanVertex.normal = v1->normal;
    l2scanVertex.positionIntScreen.z = v1->positionIntScreen.z;

    int Y = v1->positionIntScreen.y;

    int l1DeltaY, l1UDeltaY, l1UDiv, l1UMod, l1UError, l1U;

    l1DeltaY = v2->positionIntScreen.y - v1->positionIntScreen.y;
    l1UDeltaY = MwMath::Abs(l1DeltaY);
    if (l1UDeltaY != 0)
    {
        l1UDiv = SrUnit::high / l1UDeltaY;
        l1UMod = SrUnit::high % l1UDeltaY;
        l1UError = l1UDeltaY >> 1;
        l1U = 0;

        l1deltaVertex.positionIntScreen.x = v2->positionIntScreen.x - v1->positionIntScreen.x;
        l1deltaVertex.positionIntScreen.z = (v2->positionIntScreen.z - v1->positionIntScreen.z) / l1UDeltaY;
        l1deltaVertex.texCoords.x = v2->texCoords.x - v1->texCoords.x;
        l1deltaVertex.texCoords.y = v2->texCoords.y - v1->texCoords.y;
        l1deltaVertex.color.a = v2->color.a - v1->color.a;
        l1deltaVertex.color.r = v2->color.r - v1->color.r;
        l1deltaVertex.color.g = v2->color.g - v1->color.g;
        l1deltaVertex.color.b = v2->color.b - v1->color.b;
        l1deltaVertex.position.x = (v2->position.x - v1->position.x) / l1UDeltaY;
        l1deltaVertex.position.y = (v2->position.y - v1->position.y) / l1UDeltaY;
        l1deltaVertex.position.z = (v2->position.z - v1->position.z) / l1UDeltaY;
        l1deltaVertex.normal.x = (v2->normal.x - v1->normal.x) / l1UDeltaY;
        l1deltaVertex.normal.y = (v2->normal.y - v1->normal.y) / l1UDeltaY;
        l1deltaVertex.normal.z = (v2->normal.z - v1->normal.z) / l1UDeltaY;

        l1scanVertex.position = v1->position;
        l1scanVertex.normal = v1->normal;
        l1scanVertex.positionIntScreen.z = v1->positionIntScreen.z;

        while (Y < v2->positionIntScreen.y)
        {
            if ((Y >= 0) && (Y < soras->renderSurface->height))
            {
                l1scanVertex.positionIntScreen.x = v1->positionIntScreen.x + ((l1deltaVertex.positionIntScreen.x * l1U) >> SrUnit::bitCount);
                l1scanVertex.positionIntScreen.y = Y;
                l1scanVertex.texCoords.x = v1->texCoords.x + ((l1deltaVertex.texCoords.x * l1U) >> SrUnit::bitCount);
                l1scanVertex.texCoords.y = v1->texCoords.y + ((l1deltaVertex.texCoords.y * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.a = v1->color.a + ((l1deltaVertex.color.a * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.r = v1->color.r + ((l1deltaVertex.color.r * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.g = v1->color.g + ((l1deltaVertex.color.g * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.b = v1->color.b + ((l1deltaVertex.color.b * l1U) >> SrUnit::bitCount);

                l2scanVertex.positionIntScreen.x = v1->positionIntScreen.x + ((l2deltaVertex.positionIntScreen.x * l2U) >> SrUnit::bitCount);
                l2scanVertex.positionIntScreen.y = Y;
                l2scanVertex.texCoords.x = v1->texCoords.x + ((l2deltaVertex.texCoords.x * l2U) >> SrUnit::bitCount);
                l2scanVertex.texCoords.y = v1->texCoords.y + ((l2deltaVertex.texCoords.y * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.a = v1->color.a + ((l2deltaVertex.color.a * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.r = v1->color.r + ((l2deltaVertex.color.r * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.g = v1->color.g + ((l2deltaVertex.color.g * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.b = v1->color.b + ((l2deltaVertex.color.b * l2U) >> SrUnit::bitCount);

                if (l1scanVertex.positionIntScreen.x < l2scanVertex.positionIntScreen.x)
                    this->RenderScanLine(&l1scanVertex, &l2scanVertex);
                else
                    this->RenderScanLine(&l2scanVertex, &l1scanVertex);
            }

            l1scanVertex.position.x += l1deltaVertex.position.x;
            l1scanVertex.position.y += l1deltaVertex.position.y;
            l1scanVertex.position.z += l1deltaVertex.position.z;
            l1scanVertex.positionIntScreen.z += l1deltaVertex.positionIntScreen.z;

            l2scanVertex.position.x += l2deltaVertex.position.x;
            l2scanVertex.position.y += l2deltaVertex.position.y;
            l2scanVertex.position.z += l2deltaVertex.position.z;
            l2scanVertex.positionIntScreen.z += l2deltaVertex.positionIntScreen.z;

            l1scanVertex.normal.x += l1deltaVertex.normal.x;
            l1scanVertex.normal.y += l1deltaVertex.normal.y;
            l1scanVertex.normal.z += l1deltaVertex.normal.z;

            l2scanVertex.normal.x += l2deltaVertex.normal.x;
            l2scanVertex.normal.y += l2deltaVertex.normal.y;
            l2scanVertex.normal.z += l2deltaVertex.normal.z;

            l1U += l1UDiv;
            l1UError -= l1UMod;
            if (l1UError <= 0)
            {
                l1U++;
                l1UError += l1UDeltaY;
            }

            l2U += l2UDiv;
            l2UError -= l2UMod;
            if (l2UError <= 0)
            {
                l2U++;
                l2UError += l2UDeltaY;
            }

            Y++;
        }
    }

    l1DeltaY = v3->positionIntScreen.y - v2->positionIntScreen.y;
    l1UDeltaY = MwMath::Abs(l1DeltaY);
    if (l1UDeltaY != 0)
    {
        l1UDiv = SrUnit::high / l1UDeltaY;
        l1UMod = SrUnit::high % l1UDeltaY;
        l1UError = l1UDeltaY >> 1;
        l1U = 0;

        l1deltaVertex.positionIntScreen.x = v3->positionIntScreen.x - v2->positionIntScreen.x;
        l1deltaVertex.positionIntScreen.z = (v3->positionIntScreen.z - v2->positionIntScreen.z) / l1UDeltaY;
        l1deltaVertex.texCoords.x = v3->texCoords.x - v2->texCoords.x;
        l1deltaVertex.texCoords.y = v3->texCoords.y - v2->texCoords.y;
        l1deltaVertex.color.a = v3->color.a - v2->color.a;
        l1deltaVertex.color.r = v3->color.r - v2->color.r;
        l1deltaVertex.color.g = v3->color.g - v2->color.g;
        l1deltaVertex.color.b = v3->color.b - v2->color.b;
        l1deltaVertex.position.x = (v3->position.x - v2->position.x) / l1UDeltaY;
        l1deltaVertex.position.y = (v3->position.y - v2->position.y) / l1UDeltaY;
        l1deltaVertex.position.z = (v3->position.z - v2->position.z) / l1UDeltaY;
        l1deltaVertex.normal.x = (v3->normal.x - v2->normal.x) / l1UDeltaY;
        l1deltaVertex.normal.y = (v3->normal.y - v2->normal.y) / l1UDeltaY;
        l1deltaVertex.normal.z = (v3->normal.z - v2->normal.z) / l1UDeltaY;

        l1scanVertex.position = v2->position;
        l1scanVertex.normal = v2->normal;
        l1scanVertex.positionIntScreen.z = v2->positionIntScreen.z;

        while (Y < v3->positionIntScreen.y)
        {
            if ((Y >= 0) && (Y < soras->renderSurface->height))
            {
				l1scanVertex.positionIntScreen.x = v2->positionIntScreen.x + ((l1deltaVertex.positionIntScreen.x * l1U) >> SrUnit::bitCount);
                l1scanVertex.positionIntScreen.y = Y;
                l1scanVertex.texCoords.x = v2->texCoords.x + ((l1deltaVertex.texCoords.x * l1U) >> SrUnit::bitCount);
                l1scanVertex.texCoords.y = v2->texCoords.y + ((l1deltaVertex.texCoords.y * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.a = v2->color.a + ((l1deltaVertex.color.a * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.r = v2->color.r + ((l1deltaVertex.color.r * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.g = v2->color.g + ((l1deltaVertex.color.g * l1U) >> SrUnit::bitCount);
                l1scanVertex.color.b = v2->color.b + ((l1deltaVertex.color.b * l1U) >> SrUnit::bitCount);

                l2scanVertex.positionIntScreen.x = v1->positionIntScreen.x + ((l2deltaVertex.positionIntScreen.x * l2U) >> SrUnit::bitCount);
                l2scanVertex.positionIntScreen.y = Y;
                l2scanVertex.texCoords.x = v1->texCoords.x + ((l2deltaVertex.texCoords.x * l2U) >> SrUnit::bitCount);
                l2scanVertex.texCoords.y = v1->texCoords.y + ((l2deltaVertex.texCoords.y * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.a = v1->color.a + ((l2deltaVertex.color.a * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.r = v1->color.r + ((l2deltaVertex.color.r * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.g = v1->color.g + ((l2deltaVertex.color.g * l2U) >> SrUnit::bitCount);
                l2scanVertex.color.b = v1->color.b + ((l2deltaVertex.color.b * l2U) >> SrUnit::bitCount);

                if (l1scanVertex.positionIntScreen.x < l2scanVertex.positionIntScreen.x)
                    this->RenderScanLine(&l1scanVertex, &l2scanVertex);
                else
                    this->RenderScanLine(&l2scanVertex, &l1scanVertex);
            }

            l1scanVertex.position.x += l1deltaVertex.position.x;
            l1scanVertex.position.y += l1deltaVertex.position.y;
            l1scanVertex.position.z += l1deltaVertex.position.z;
            l1scanVertex.positionIntScreen.z += l1deltaVertex.positionIntScreen.z;

            l2scanVertex.position.x += l2deltaVertex.position.x;
            l2scanVertex.position.y += l2deltaVertex.position.y;
            l2scanVertex.position.z += l2deltaVertex.position.z;
            l2scanVertex.positionIntScreen.z += l2deltaVertex.positionIntScreen.z;

            l1scanVertex.normal.x += l1deltaVertex.normal.x;
            l1scanVertex.normal.y += l1deltaVertex.normal.y;
            l1scanVertex.normal.z += l1deltaVertex.normal.z;

            l2scanVertex.normal.x += l2deltaVertex.normal.x;
            l2scanVertex.normal.y += l2deltaVertex.normal.y;
            l2scanVertex.normal.z += l2deltaVertex.normal.z;

            l1U += l1UDiv;
            l1UError -= l1UMod;
            if (l1UError <= 0)
            {
                l1U++;
                l1UError += l1UDeltaY;
            }

            l2U += l2UDiv;
            l2UError -= l2UMod;
            if (l2UError <= 0)
            {
                l2U++;
                l2UError += l2UDeltaY;
            }

            Y++;
        }
    }
}

void SrRenderThread::RenderScanLine(SrVertex *p1, SrVertex *p2)
{
	Soras *soras = this->soras;

	SrVertex deltaPixel, scanPixel;

	this->shaderReg_Point = &scanPixel;
	
	deltaPixel.positionIntScreen.x = p2->positionIntScreen.x - p1->positionIntScreen.x;
    if (deltaPixel.positionIntScreen.x == 0)
        return;

    float deltaX = (float)deltaPixel.positionIntScreen.x;
    deltaPixel.positionIntScreen.z = (p2->positionIntScreen.z - p1->positionIntScreen.z) / deltaX;
    deltaPixel.texCoords.x = p2->texCoords.x - p1->texCoords.x;
    deltaPixel.texCoords.y = p2->texCoords.y - p1->texCoords.y;
    deltaPixel.color.a = p2->color.a - p1->color.a;
    deltaPixel.color.r = p2->color.r - p1->color.r;
    deltaPixel.color.g = p2->color.g - p1->color.g;
    deltaPixel.color.b = p2->color.b - p1->color.b;
    deltaPixel.position.x = (p2->position.x - p1->position.x) / deltaX;
    deltaPixel.position.y = (p2->position.y - p1->position.y) / deltaX;
    deltaPixel.position.z = (p2->position.z - p1->position.z) / deltaX;
    deltaPixel.normal.x = (p2->normal.x - p1->normal.x) / deltaX;
    deltaPixel.normal.y = (p2->normal.y - p1->normal.y) / deltaX;
    deltaPixel.normal.z = (p2->normal.z - p1->normal.z) / deltaX;

    int uDiv = SrUnit::high / deltaPixel.positionIntScreen.x;
    int uMod = SrUnit::high % deltaPixel.positionIntScreen.x;
    int uError = deltaPixel.positionIntScreen.x >> 1;
    int u = 0;

    SrVector3 scanNormal = p1->normal;

    scanPixel.position = p1->position;
    scanPixel.positionIntScreen.y = p1->positionIntScreen.y;
    scanPixel.positionIntScreen.z = p1->positionIntScreen.z;
	int ZIndex = scanPixel.positionIntScreen.y * soras->renderSurface->width + p1->positionIntScreen.x;
    int renderPixel = ZIndex << 2;

    for (scanPixel.positionIntScreen.x = p1->positionIntScreen.x; scanPixel.positionIntScreen.x < p2->positionIntScreen.x; scanPixel.positionIntScreen.x++)
    {
        if ((scanPixel.positionIntScreen.x >= 0) && (scanPixel.positionIntScreen.x < soras->renderSurface->width))
        {
            if (scanPixel.positionIntScreen.z < soras->zBuffer[ZIndex])
            {
				soras->zBuffer[ZIndex] = scanPixel.positionIntScreen.z;
                scanPixel.texCoords.x = p1->texCoords.x + ((deltaPixel.texCoords.x * u) >> SrUnit::bitCount);
                scanPixel.texCoords.y = p1->texCoords.y + ((deltaPixel.texCoords.y * u) >> SrUnit::bitCount);
                scanPixel.color.a = p1->color.a + ((deltaPixel.color.a * u) >> SrUnit::bitCount);
                scanPixel.color.r = p1->color.r + ((deltaPixel.color.r * u) >> SrUnit::bitCount);
                scanPixel.color.g = p1->color.g + ((deltaPixel.color.g * u) >> SrUnit::bitCount);
                scanPixel.color.b = p1->color.b + ((deltaPixel.color.b * u) >> SrUnit::bitCount);
                scanPixel.normal = scanNormal;
                //scanPixel.normal.Normalize();
				
			
				this->shaderTextureIndex = 0;
				for (int pop = 0; pop < soras->pixelOps.count; pop++)
					soras->pixelOps[pop](this);

                if (soras->blending != 0)
                {

                    this->shaderReg_ColorArg = scanPixel.color;
					unsigned char *component = &soras->renderSurface->data[renderPixel];
                    this->shaderReg_Point->color.b = *component++;
                    this->shaderReg_Point->color.g = *component++;
                    this->shaderReg_Point->color.r = *component++;
                    this->shaderReg_Point->color.a = *component;
                    soras->blending(this);
                    scanPixel.color = this->shaderReg_Point->color;
                }

				// Desaturate final color and output it to the render surface in 32bit ARGB format, low-to-high order
				unsigned char *component = &soras->renderSurface->data[renderPixel];
                if (scanPixel.color.b > 0xff)
                    *component = 0xff;
                else
                    if (scanPixel.color.b < 0)
                        *component = 0x00;
                    else
                        *component = (char)(scanPixel.color.b);
                component++;

                if (scanPixel.color.g > 0xff)
                    *component = 0xff;
                else
                    if (scanPixel.color.g < 0)
                        *component = 0x00;
                    else
                        *component = (char)(scanPixel.color.g);
                component++;

                if (scanPixel.color.r > 0xff)
                    *component = 0xff;
                else
                    if (scanPixel.color.r < 0)
                        *component = 0x00;
                    else
                        *component = (char)(scanPixel.color.r);
                component++;

                if (scanPixel.color.a > 0xff)
                    *component = 0xff;
                else
                    if (scanPixel.color.a < 0)
                        *component = 0x00;
                    else
                        *component = (char)(scanPixel.color.a);
            }
        }
		else
		{
			int a = 0;
		}

        scanPixel.position.x += deltaPixel.position.x;
        scanPixel.position.y += deltaPixel.position.y;
        scanPixel.position.z += deltaPixel.position.z;
        scanPixel.positionIntScreen.z += deltaPixel.positionIntScreen.z;
        scanNormal.x += deltaPixel.normal.x;
        scanNormal.y += deltaPixel.normal.y;
        scanNormal.z += deltaPixel.normal.z;

        u += uDiv;
        uError -= uMod;
        if (uError <= 0)
        {
            u++;
            uError = uError + deltaPixel.positionIntScreen.x;
        }

        ZIndex++;
        renderPixel += 4;
    }
}