#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "MwFile3dsPrimitiveTypes.h"

#include "MwFile3dsBaseObject.h"
#include "MwFile3dsKeyFrames.h"

class MwFile3dsHierarchyNode;

class MWDLLCLASS MwFile3dsHierarchy : 
	public MwList<MwFile3dsHierarchyNode*>
{
public:
	MwFile3dsHierarchyNode *parent;

	MwFile3dsHierarchy(MwFile3dsHierarchyNode *parent);
	~MwFile3dsHierarchy(void);
};

class MWDLLCLASS MwFile3dsHierarchyNode
{

public:
	MwFile3dsBaseObject *obj;
	MwFile3dsKeyFrameObject *keyFrames;
	MwFile3dsHierarchy *children;
	bool isDummy;

	MwFile3dsHierarchyNode(MwFile3dsBaseObject *obj, MwFile3dsKeyFrameObject *keyFrames);
	~MwFile3dsHierarchyNode(void);
};