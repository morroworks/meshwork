#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwList.h"

#include "MwScriptDataType.h"

class MWDLLCLASS MwScriptDataTypes :
	public MwList<MwScriptDataType*>
{
public:
	MwScriptDataTypes(void);
	~MwScriptDataTypes(void);

	MwScriptDataType *Find(MwString name);
};
