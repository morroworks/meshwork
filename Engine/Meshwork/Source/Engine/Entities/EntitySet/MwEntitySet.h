#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\Base\MwBaseResource.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwBaseResource*>;

class MWDLLCLASS MwEntitySet
	: public MwBaseResource
{
private:
	static const unsigned int SerializationId_References = 0x21111005;

public:
	static const int classId = (MwResourceType_EntitySet << 16) | 0;

	static const int propertyIndex_Active = 0;
	static const int propertyIndex_MultiPass = 1;
	static const int propertyIndex_Branch = 2;

	MwList<MwBaseResource*> references;

	MwEntitySet(void);
	virtual ~MwEntitySet(void);

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

