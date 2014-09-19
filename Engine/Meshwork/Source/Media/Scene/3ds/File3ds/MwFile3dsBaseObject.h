#pragma once

#include "..\..\..\..\MwGlobals.h"

#include "..\..\..\..\Tools\MwString.h"

enum MWDLLCLASS MwFile3dsObjectType
{
	MwFile3dsObjectType_Mesh,
	MwFile3dsObjectType_Light,
	MwFile3dsObjectType_Camera
};

class MWDLLCLASS MwFile3dsBaseObject
{
public:
	MwFile3dsObjectType objectType;

	MwString name;

	MwFile3dsBaseObject(void);
	virtual ~MwFile3dsBaseObject(void);
};