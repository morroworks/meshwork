#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

#include "..\..\..\Sound\MwAudioDeviceSoundReceptor.h"

#include "..\..\Primitive\MwVector3.h"

class Meshwork;

class MWDLLCLASS MwSoundReceptor :
	public MwBaseResource
{
private:
	MwVector3 velocity, position, lastPosition;
	int paramAddressWorldMatrix, paramAddressVelocity;

public:
	static const int classId = (MwResourceType_SoundReceptor << 16) | 0;

	Meshwork *context;
	MwAudioDeviceSoundReceptor *deviceSoundReceptor;

	MwSoundReceptor(Meshwork *context);
	~MwSoundReceptor(void);

	void ApplyWorldLocation(MwMatrix *worldMatrix);
};

