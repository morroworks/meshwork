#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwList.h"

#include "..\..\Base\MwBaseResource.h"
#include "..\..\Primitive\MwMatrix.h"

#include "MwTransformSlot.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwTransformSlot>;

class MWDLLCLASS MwTransform
	: public MwBaseResource
{
private:
	static const unsigned int SerializationId_Pivot				= 0x21111002;
	static const unsigned int SerializationId_Manual			= 0x21112002;
	static const unsigned int SerializationId_TransformSlots	= 0x21113002;
	static const unsigned int SerializationId_TransformSlot		= 0x21113102;
	static const unsigned int SerializationId_BindInverse		= 0x21114002;

	MwMatrix m;

	void SerializeMatrix(MwBaseStream &stream, MwMatrix &matrix);
	void DeserializeMatrix(MwMatrix &result, MwBaseStream &stream);

public:
	static const int classId = (MwResourceType_Transform << 16) | 0;

	static const int propertyIndex_Bone = 0;
	static const int propertyIndex_BoneIndex = 1;

	MwMatrix boneBindPoseInverse, pivot, manual, keyframe, pivotless, matrix;
	MwList<MwTransformSlot> transformSlots;

	bool _updateState;


	MwTransform(void);
	~MwTransform(void);

	void InsertTransformSlot(MwTransformOperation operation, int index);
	int AddTransformSlot(MwTransformOperation operation);
	void RemoveTransformSlot(int index);
	void ClearTransformSlots();
	void Process();

	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};

