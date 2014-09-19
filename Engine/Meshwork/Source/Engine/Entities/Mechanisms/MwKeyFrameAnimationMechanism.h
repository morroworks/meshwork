#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwBaseMechanism.h"

#include "..\..\Entities\Transform\MwTransform.h"

#include "KeyFrameAnimation\MwKeyFramesTrack.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwKeyFramesTrack*>;

class Meshwork;

class MWDLLCLASS MwKeyframeAnimationMechanism
	: public MwBaseMechanism
{
private:
	static const unsigned int SerializationId_KeyFrameTracks		= 0x21111018;
	static const unsigned int SerializationId_KeyFrameTrack			= 0x21111118;
	static const unsigned int SerializationId_KeyFrameTrackFrames	= 0x21111128;

	MwKeyFramesTrack *currentDeserializationTrack;

public:
	static const int classId = MwBaseMechanism::classId | 7;

	static const int propertyIndex_Frame = 0;
	static const int propertyIndex_Transform = 1;

	Meshwork *context;
	MwList<MwKeyFramesTrack*> keyFramesTracks;

    MwKeyframeAnimationMechanism(Meshwork *context);
	~MwKeyframeAnimationMechanism(void);

    bool Process(float deltaTime);

	// Precalculates data, which is needed for a MwKeyFramesTrack composed out of MwKeyFrameRotationAxis to work properly. This is needed for optimization, because the result of each MwKeyFrameRotationAxis keyframe is affected by all previous ones
	void BuildRotationAxisTrack(MwKeyFramesTrack *rotationAxisTrack);
    
	// Serialize key frame data. See base class method for more info
	virtual void SerializeChunks(MwHierarchyStreamWriter &writer);
	// Deserialize key frame data. See base class method for more info
	virtual bool DeserializeChunk(MwHierarchyStreamReader &reader);
};
