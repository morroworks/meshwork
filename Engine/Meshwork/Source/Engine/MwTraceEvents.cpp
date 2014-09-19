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

#include "MwTraceEvents.h"


MwTraceEvents::MwTraceEvents(Meshwork &meshwork)
{
	this->meshwork = &meshwork;
}

MwTraceEvents::~MwTraceEvents(void)
{
}

// Virtual Methods
void MwTraceEvents::OnMesh(MwTraceParameters &parameters) { }
void MwTraceEvents::OnCamera(MwTraceParameters &parameters) { }
void MwTraceEvents::OnTransform(MwTraceParameters &parameters) { }
void MwTraceEvents::OnRenderTarget(MwTraceParameters &parameters) { }
void MwTraceEvents::OnMaterial(MwTraceParameters &parameters) { }
void MwTraceEvents::OnMechanism(MwTraceParameters &parameters) { }
void MwTraceEvents::OnLight(MwTraceParameters &parameters) { }
void MwTraceEvents::OnSoundEmitter(MwTraceParameters &parameters) { }
void MwTraceEvents::OnSoundReceptor(MwTraceParameters &parameters) { }
void MwTraceEvents::OnTexture2D(MwTraceParameters &parameters) { }

void MwTraceEvents::OnExitedBranch(MwTraceParameters &parameters) { }
