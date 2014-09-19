#pragma once

#include "..\..\MwGlobals.h"

enum MwResourceType
{
	MwResourceType_None = 0,
	MwResourceType_Camera = 1,
    MwResourceType_Transform = 2,
    MwResourceType_Material = 3,
    MwResourceType_Mesh = 4,
    MwResourceType_EntitySet = 5,
    MwResourceType_Texture = 6, 
    MwResourceType_RenderTarget = 7,
    MwResourceType_Mechanism = 8,
    MwResourceType_Light = 9,
	MwResourceType_Sound = 10,
	MwResourceType_SoundEmitter = 11,
	MwResourceType_SoundReceptor = 12,
	MwResourceType_Script = 13
};
