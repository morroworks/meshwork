#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwKeyFrame.h"

#include "..\..\..\Primitive\MwVector3.h"
#include "..\..\..\Primitive\MwMatrix.h"

class MWDLLCLASS MwKeyFrameRotationAxis :
	public MwKeyFrame
{
public:
	static const int classId = 0x21111418;

	MwMatrix previousTransform;
    MwVector3 axis;
    float angle;

	MwKeyFrameRotationAxis(void);
	MwKeyFrameRotationAxis(float time, float angle, MwVector3 &axis);
	~MwKeyFrameRotationAxis(void);

	virtual void Process(MwMatrix &result);
	virtual void Process(MwMatrix &result, MwKeyFrame *next, float blend);

	virtual void Serialize(MwBaseStream &destination);
	virtual bool Deserialize(MwBaseStream &source);
};

