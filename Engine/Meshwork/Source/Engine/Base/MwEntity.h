#pragma once

#include "..\..\Tools\Streams\MwBaseStream.h"

class MWDLLCLASS MwEntity
{
public:
	// typeId can be assigned to a static member of a MwClassId class, which in its constructor can assign a unique MwClassId.id. This way we could have, for example MwMesh.typeId = MwMesh::classId.id. However it would be a bit obscure, because even if this will ensure the uniqueness of the ids, it wont ensure that the same class will always have the same id assigned, which is vital for serialization.
	int typeId;

	MwEntity(void);
	~MwEntity(void);

	// Serializes the object into the stream
	virtual void Serialize(MwBaseStream &destination) = 0;
	// Deserializes the object from the stream
	virtual bool Deserialize(MwBaseStream &source) = 0;
};

