#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsPrimitiveTypes.h"

#include "..\..\..\..\Tools\MwString.h"
#include "..\..\..\..\Tools\MwList.h"


class MWDLLCLASS MwFile3dsKeyFrameBase
{
public:
    int frameNumber;
    int flags;
    float tension, continuity, bias, easeTo, easeFrom;

	MwFile3dsKeyFrameBase::MwFile3dsKeyFrameBase(void);
	virtual MwFile3dsKeyFrameBase::~MwFile3dsKeyFrameBase(void);
};

class MWDLLCLASS MwFile3dsKeyFramePosition : 
	public MwFile3dsKeyFrameBase
{
public:
    MwFile3dsVector position;
};

class MWDLLCLASS MwFile3dsKeyFrameRotation : 
	public MwFile3dsKeyFrameBase
{
public:
    float angle;
    MwFile3dsVector axis;
};

class MWDLLCLASS MwFile3dsKeyFrameScaling : 
	public MwFile3dsKeyFrameBase
{
public:
    MwFile3dsVector scaling;
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFile3dsKeyFrameBase*>;

class MWDLLCLASS MwFile3dsKeyFramesTrack
{
public:
    int flags, keys;
    MwList<MwFile3dsKeyFrameBase*> data;

	MwFile3dsKeyFramesTrack(void);
	~MwFile3dsKeyFramesTrack(void);
};
	
class MWDLLCLASS MwFile3dsKeyFrameObject
{
public:
    MwString name, instanceName;
    int hierarchyLevel, id;
    MwFile3dsVector pivot;
    MwFile3dsKeyFramesTrack *position, *rotation, *scaling;

	MwFile3dsKeyFrameObject(void);
	~MwFile3dsKeyFrameObject(void);
};

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwFile3dsKeyFrameObject*>;

class MWDLLCLASS MwFile3dsKeyFrames
{
public:
	int start, end, current;
	MwList<MwFile3dsKeyFrameObject*> objects;

	MwFile3dsKeyFrames(void);
	~MwFile3dsKeyFrames(void);
};
