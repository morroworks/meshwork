#pragma once

#include "..\MwGlobals.h"

#include "MwTraceEvents.h"

class MWDLLCLASS MwRenderEvents :
	public MwTraceEvents
{
public:
	int numRenderedObjects;
	bool updateState;

	
	MwRenderEvents(Meshwork &meshwork);
	~MwRenderEvents(void);

	void SetupNewFrame();

	void OnMaterial(MwTraceParameters &parameters);
    void OnMesh(MwTraceParameters &parameters);
    void OnMechanism(MwTraceParameters &parameters);
    void OnTransform(MwTraceParameters &parameters);
    void OnLight(MwTraceParameters &parameters);
	void OnSoundEmitter(MwTraceParameters &parameters);
	void OnSoundReceptor(MwTraceParameters &parameters);
	void OnTexture2D(MwTraceParameters &parameters);
	void OnExitedBranch(MwTraceParameters &parameters);
};

