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

#include "MwTraceParameters.h"


MwTraceParameters::MwTraceParameters(void)
{
	this->meshRef = 0;
	this->cameraRef = 0;
	this->transformRef = 0;
	this->renderTargetRef = 0;
	this->materialRef = 0;
	this->mechanismRef = 0;
	this->lightRef = 0;
	this->soundEmitterRef = 0;
	this->soundReceptorRef = 0;
	this->textureRef = 0;

	this->meshBranch = 0;
	this->cameraBranch = 0;
	this->transformBranch = 0;
	this->materialBranch = 0;
	this->lightBranch = 0;
	this->soundEmitterBranch = 0;
	this->soundReceptorBranch = 0;

	this->meshIndex = -1;
	this->cameraIndex = -1;
	this->transformIndex = -1;
	this->materialIndex = -1;
	this->lightIndex = -1;
	this->soundEmitterIndex = -1;
	this->soundReceptorIndex = -1;

	MwMatrix::CreateIdentity(this->parentTransform);
}

MwTraceParameters::MwTraceParameters(MwTraceParameters &parent)
{
	this->meshRef = parent.meshRef;
	this->cameraRef = parent.cameraRef;
	this->transformRef = parent.transformRef;
	this->renderTargetRef = parent.renderTargetRef;
	this->materialRef = parent.materialRef;
	this->mechanismRef = parent.mechanismRef;
	this->lightRef = parent.lightRef;
	this->soundEmitterRef = parent.soundEmitterRef;
	this->soundReceptorRef = parent.soundReceptorRef;
	this->textureRef = parent.textureRef;

	this->meshBranch = parent.meshBranch;
	this->cameraBranch = parent.cameraBranch;
	this->transformBranch = parent.transformBranch;
	this->materialBranch = parent.materialBranch;
	this->lightBranch = parent.lightBranch;
	this->soundEmitterBranch = parent.soundEmitterBranch;
	this->soundReceptorBranch = parent.soundReceptorBranch;

	this->meshIndex = parent.meshIndex;
	this->cameraIndex = parent.cameraIndex;
	this->transformIndex = parent.transformIndex;
	this->materialIndex = parent.materialIndex;
	this->lightIndex = parent.lightIndex;
	this->soundEmitterIndex = parent.soundEmitterIndex;
	this->soundReceptorIndex = parent.soundReceptorIndex;

	MwMatrix::Copy(this->parentTransform, parent.parentTransform);
}

MwTraceParameters::~MwTraceParameters(void)
{
}

