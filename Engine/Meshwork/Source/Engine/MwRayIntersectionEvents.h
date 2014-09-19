#pragma once

#include "..\MwGlobals.h"

#include "MwTraceEvents.h"

class MWDLLCLASS MwRayIntersectionEvents :
	public MwTraceEvents
{
private:
	MwVector3 rayPoint, rayVector;
    float intersectionDistance;

public:
    MwTraceParameters traceResult;
    MwIntersectionInfo intersectionInfo;
    bool intersected;
	
	MwRayIntersectionEvents(Meshwork &meshwork);
	~MwRayIntersectionEvents(void);

	void SetupRay(MwVector3 &rayPoint1, MwVector3 &rayPoint2);

	void OnMesh(MwTraceParameters &parameters);
};

