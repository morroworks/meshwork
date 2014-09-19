#pragma once

#include "..\..\MwGlobals.h"

#include "MwResourceType.h"

#include "MwEntity.h"

#include "..\Properties\MwProperty.h"

#include "..\..\Tools\MwString.h"
#include "..\..\Tools\MwList.h"

#include "..\Utilities\Serialization\MwHierarchyStreamWriter.h"
#include "..\Utilities\Serialization\MwHierarchyStreamReader.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwProperty*>;

class MWDLLCLASS MwBaseResource :
	public MwEntity
{
private:
	static const unsigned int SerializationId_Resource		= 0x21110000;
	static const unsigned int SerializationId_ResourceId	= 0x21111000;
	static const unsigned int SerializationId_ResourceName	= 0x21112000;
	static const unsigned int SerializationId_Properties	= 0x21113000;
	static const unsigned int SerializationId_Property		= 0x21113100;


public:
	MwResourceType resourceType;
    long long id;
    MwString name;

	MwList<MwProperty*> properties;

	MwBaseResource();
	virtual ~MwBaseResource(void);

	MwProperty *GetProperty(MwString name);


	// Writes a parameter's type and value into a stream
	void SerializeParameter(MwParameter &parameter, MwBaseStream &destination);
	// Readss a parameter's type and value from a stream
	void DeserializeParameter(MwParameter &parameter, MwBaseStream &source);

	// Calls SerializeChunks() method, wrapping its whole output in a SerializationId_Resource
	virtual void Serialize(MwBaseStream &destination);
	// Reads the contents wrapped in a SerializationId_Resource and calls DeserializeChunk() method for each chunk of these chunks. Override to perform pre or post serialization routines
	virtual bool Deserialize(MwBaseStream &source);
	
	// Writes chunks for all the data which is needed to serialize the resource. Override to write chunks of resource-specific data
	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	// Reads chunks of all the data which is needed to deserialize the resource. Override to read chunks of resource-specific data
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

