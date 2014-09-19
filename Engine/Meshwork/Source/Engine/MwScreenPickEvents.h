#pragma once

#include "..\MwGlobals.h"

#include "MwTraceEvents.h"


class MWDLLCLASS MwScreenPickEvents :
	public MwTraceEvents
{
private:
	MwVector3 rayPoint1, rayPoint2;
    float intersectionDistance;

public:
    MwIntersectionInfo intersectionInfo;
    MwTraceParameters entityInfo;
	bool intersected;

	MwScreenPickEvents(Meshwork &meshwork);
	~MwScreenPickEvents(void);

    void SetupScreenPick(int x, int y, int screenWidth, int screenHeight);
	
	void OnMesh(MwTraceParameters &parameters);
    void OnTransform(MwTraceParameters &parameters);
};

