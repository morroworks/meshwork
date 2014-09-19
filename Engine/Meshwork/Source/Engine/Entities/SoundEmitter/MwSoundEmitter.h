#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\..\Sound\MwAudioDeviceSoundEmitter.h"

#include "..\..\Primitive\MwVector3.h"

#include "..\..\Properties\MwBoundProperty.h"

class Meshwork;

class MWDLLCLASS MwSoundEmitter :
	public MwBaseResource
{
private:
	MwVector3 velocity, position, lastPosition;
	int paramAddressWorldMatrix, paramAddressVelocity;

public:
	static const int classId = (MwResourceType_SoundEmitter << 16) | 0;

	static const int propertyIndex_Sound = 0;
	static const int propertyIndex_Ambient = 1;
	static const int propertyIndex_Play = 2;
	static const int propertyIndex_Loop = 3;
	static const int propertyIndex_Volume = 4;
	static const int propertyIndex_Rate = 5;

	Meshwork *context;
	MwAudioDeviceSoundEmitter *deviceSoundEmitter;

	MwSoundEmitter(Meshwork *context);
	~MwSoundEmitter(void);
	
	void ApplyWorldLocation(MwMatrix *worldMatrix);
	void ApplyProperty(MwBoundProperty *emitterProperty);
	void ApplyProperties();
};

