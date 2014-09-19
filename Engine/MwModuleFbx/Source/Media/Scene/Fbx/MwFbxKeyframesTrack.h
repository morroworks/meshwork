#pragma once

#include "..\..\..\MeshworkEngine.h"

#include "MwFbxPrimitiveTypes.h"

#include <fbxsdk.h>

class MwFbxKeyframesTrack
{
public:
	bool valid;
	MwList<MwFbxKeyframe> keyframes;

	MwFbxKeyframesTrack(void);
	~MwFbxKeyframesTrack(void);

	bool FindFrameKey(int &index, float time);
	void ProcessFbxCurve(FbxAnimCurve* curve, MwFbxKeyFrameValueComponent valueComponent, float defaultValue = 0.0f);
};

