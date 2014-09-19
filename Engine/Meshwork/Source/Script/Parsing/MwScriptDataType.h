#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwString.h"
#include "..\..\Tools\MwList.h"

class MwScriptDataType
{
public:
	int size;
	MwString name;
	MwList<MwScriptDataType*> fields;

	MwScriptDataType(MwString name);
	MwScriptDataType(MwString name, int size);
	~MwScriptDataType(void);

	void AddField(MwScriptDataType *field);
};

