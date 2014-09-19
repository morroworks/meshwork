#pragma once

#include "..\MwGlobals.h"

#include "MwTraceParameters.h"

class Meshwork;

class MWDLLCLASS MwTraceEvents
{
public:
    Meshwork *meshwork;

	MwTraceEvents(Meshwork &meshwork);
	virtual ~MwTraceEvents(void);

	virtual void OnMesh(MwTraceParameters &parameters);
	virtual void OnCamera(MwTraceParameters &parameters);
	virtual void OnTransform(MwTraceParameters &parameters);
	virtual void OnRenderTarget(MwTraceParameters &parameters);
	virtual void OnMaterial(MwTraceParameters &parameters);
	virtual void OnMechanism(MwTraceParameters &parameters);
	virtual void OnLight(MwTraceParameters &parameters);
	virtual void OnSoundEmitter(MwTraceParameters &parameters);
	virtual void OnSoundReceptor(MwTraceParameters &parameters);
	virtual void OnTexture2D(MwTraceParameters &parameters);

	virtual void OnExitedBranch(MwTraceParameters &parameters);
};

