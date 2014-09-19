#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwKeyFrame.h"

#include "..\..\..\..\Tools\MwList.h"

class MWDLLCLASS MwKeyFramesTrack :
	public MwList<MwKeyFrame*>
{
public:
	MwKeyFramesTrack(void);
	virtual ~MwKeyFramesTrack(void);

	virtual void GetTransform(MwMatrix &result, float time);
};

