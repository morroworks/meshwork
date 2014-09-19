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

#include "MwCamera.h"

#include "..\..\Meshwork.h"

MwCamera::MwCamera(Meshwork *context)
	: MwBaseResource()
{
	this->context = context;

	this->typeId = MwCamera::classId;
	this->resourceType = MwResourceType_Camera;
    view = MwMatrix();
    projection = MwMatrix();
    viewProjection = MwMatrix();
        
    this->properties.Add(new MwProperty(MwString("Aspect"), 1.0f));
    this->properties.Add(new MwProperty(MwString("FOV"), MwMath::Pi / 4.0f));
    this->properties.Add(new MwProperty(MwString("Ortho Zoom"), 1.0f));
    this->properties.Add(new MwProperty(MwString("Orthographic"), false));
}


MwCamera::~MwCamera(void)
{
}

void MwCamera::BuildMatrix(MwMatrix &transform)
{
	MwMatrix::GetAxisX(this->xAxis, transform);
	MwMatrix::GetAxisY(this->yAxis, transform);
	MwMatrix::GetAxisZ(this->zAxis, transform);
	MwMatrix::GetTranslation(this->position, transform);
	MwVector3::Add(this->lookAt, this->position, this->zAxis);

	float aspect = *(float*)this->properties[MwCamera::propertyIndex_Aspect]->GetEffectiveParameter()->value;
	float fov = *(float*)this->properties[MwCamera::propertyIndex_FOV]->GetEffectiveParameter()->value;
	float orthoZoom = *(float*)this->properties[MwCamera::propertyIndex_OrthoZoom]->GetEffectiveParameter()->value;
	bool orthographic = *(bool*)this->properties[MwCamera::propertyIndex_Orthographic]->GetEffectiveParameter()->value;

	MwMatrix::CreateLookAt(this->view, this->position, this->lookAt, this->yAxis);
	// Because Meshwork uses the horizontal of the viewport as the field of view standard, that means that the aspect should change the viewport vertical - both in perspective and orthogonal projection
	if (orthographic)
		MwMatrix::CreateOrthographic(this->projection, orthoZoom * (float)this->context->viewportWidth, orthoZoom * (float)this->context->viewportHeight / aspect, 1.0f, 10000.0f);
    else
		MwMatrix::CreatePerspectiveFieldOfView(this->projection, fov, aspect * (float)this->context->viewportWidth / (float)this->context->viewportHeight, 1.0f, 10000.0f);
        
    MwMatrix::Multiply(this->viewProjection, this->view, this->projection);
}
