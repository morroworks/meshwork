#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\Base\MwEntity.h"

#include "..\..\..\Primitive\MwMatrix.h"

#include "..\..\..\..\Tools\Streams\MwBaseStream.h"

class MWDLLCLASS MwKeyFrame :
	public MwEntity
{
public:
	float time;

	MwKeyFrame(void);
	MwKeyFrame(float time);
	virtual ~MwKeyFrame(void);

	// Gets the resulting transform of the key frame
	virtual void Process(MwMatrix &result) = 0;
	// Gets a transform, which is the result of the keyframe, blended with another one, with blending factor given by blend. Normally the another key frame is of the same object and blend is in the range between 0 and 1
	virtual void Process(MwMatrix &result, MwKeyFrame *next, float blend) = 0;

	// Serializes the keyframe data to a stream. See base class for more info.
	virtual void Serialize(MwBaseStream &destination);
	// Deserializes the keyframe from a stream. See base class for more info.
	virtual bool Deserialize(MwBaseStream &source);
};

