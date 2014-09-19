#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwKeyFrame.h"

#include "..\..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwKeyFrameScaling :
	public MwKeyFrame
{
public:
	static const int classId = 0x21111218;

	MwVector3 scaling;

	MwKeyFrameScaling(void);
	MwKeyFrameScaling(float time, MwVector3 &scaling);
	~MwKeyFrameScaling(void);

	virtual void Process(MwMatrix &result);
	virtual void Process(MwMatrix &result, MwKeyFrame *next, float blend);

	virtual void Serialize(MwBaseStream &destination);
	virtual bool Deserialize(MwBaseStream &source);
};

