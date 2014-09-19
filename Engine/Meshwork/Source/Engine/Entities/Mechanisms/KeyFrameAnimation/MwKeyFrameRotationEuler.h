#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwKeyFrame.h"

#include "..\..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwKeyFrameRotationEuler :
	public MwKeyFrame
{
public:
	static const int classId = 0x21111318;

	MwVector3 eulerAngles;
	
	MwKeyFrameRotationEuler(void);
	MwKeyFrameRotationEuler(float time, MwVector3 &eulerAngles);
	~MwKeyFrameRotationEuler(void);

	virtual void Process(MwMatrix &result);
	virtual void Process(MwMatrix &result, MwKeyFrame *next, float blend);

	virtual void Serialize(MwBaseStream &destination);
	virtual bool Deserialize(MwBaseStream &source);
};

