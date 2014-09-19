#pragma once

#include "..\..\..\MeshworkEngine.h"

struct MwFbxKeyframe
{
	float time	;
	MwVector3 value;
};

enum MwFbxKeyFrameValueComponent
{
	MwFbxKeyFrameValueComponentX,
	MwFbxKeyFrameValueComponentY,
	MwFbxKeyFrameValueComponentZ
};