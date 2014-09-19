#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwKeyFrame.h"

#include "..\..\..\Primitive\MwVector3.h"

class MWDLLCLASS MwKeyFrameTranslation :
	public MwKeyFrame
{
public:
	static const int classId = 0x21111518;

	MwVector3 position;

	MwKeyFrameTranslation(void);
	MwKeyFrameTranslation(float time, MwVector3 &position);
	~MwKeyFrameTranslation(void);

	virtual void Process(MwMatrix &result);
	virtual void Process(MwMatrix &result, MwKeyFrame *next, float blend);

	virtual void Serialize(MwBaseStream &destination);
	virtual bool Deserialize(MwBaseStream &source);
};
