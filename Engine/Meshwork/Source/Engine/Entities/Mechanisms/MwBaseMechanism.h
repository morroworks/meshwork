#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

class MWDLLCLASS MwBaseMechanism
	: public MwBaseResource
{
private:
	static const unsigned int SerializationId_Parameter	= 0x21111008;

public:
	static const int classId = (MwResourceType_Mechanism << 16) | 0;

	MwParameter parameter;

    bool _updateState;

	MwBaseMechanism(void);
	virtual ~MwBaseMechanism(void);

	virtual bool Process(float deltaTime);

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

