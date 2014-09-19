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

#include "SrCullModes.h"

#include "..\Soras.h"

bool SrCullModes::None(Soras *soras)
{
    return true;
}
		
bool SrCullModes::CounterClockWise(Soras *soras)
{
    int *index = &soras->mesh->indices[soras->cull_PrimitiveIndex];

	SrVertex *v0 = &soras->mesh->transformedVertices[*index++];
	SrVertex *v1 = &soras->mesh->transformedVertices[*index++];
	SrVertex *v2 = &soras->mesh->transformedVertices[*index];

    return ((v1->positionIntScreen.x - v0->positionIntScreen.x) *
            (v2->positionIntScreen.y - v0->positionIntScreen.y) -
            (v2->positionIntScreen.x - v0->positionIntScreen.x) *
            (v1->positionIntScreen.y - v0->positionIntScreen.y)) < 0;
}

bool SrCullModes::ClockWise(Soras *soras)
{
    int *index = &soras->mesh->indices[soras->cull_PrimitiveIndex];

	SrVertex *v0 = &soras->mesh->transformedVertices[*index++];
	SrVertex *v1 = &soras->mesh->transformedVertices[*index++];
	SrVertex *v2 = &soras->mesh->transformedVertices[*index];

    return ((v1->positionIntScreen.x - v0->positionIntScreen.x) *
            (v2->positionIntScreen.y - v0->positionIntScreen.y) -
            (v2->positionIntScreen.x - v0->positionIntScreen.x) *
            (v1->positionIntScreen.y - v0->positionIntScreen.y)) > 0;
}
