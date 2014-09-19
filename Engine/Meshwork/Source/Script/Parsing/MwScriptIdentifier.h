#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwString.h"

#include "MwScriptDataType.h"

class MwScriptIdentifier
{
public:
	MwString name;
	MwScriptDataType* dataType;
	int address;
	int elements;

	MwScriptIdentifier(MwString name, MwScriptDataType* dataType, int address);
	~MwScriptIdentifier(void);
};
