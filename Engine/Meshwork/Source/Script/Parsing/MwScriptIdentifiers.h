#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwList.h"

#include "MwScriptIdentifier.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<MwScriptIdentifier*>;

class MWDLLCLASS MwScriptIdentifiers
{
public:
	MwList<MwScriptIdentifier*> list;
	int size;

	MwScriptIdentifiers(void);
	~MwScriptIdentifiers(void);

	MwScriptIdentifier *Find(MwString name);
	MwScriptIdentifier *Add(MwString name, MwScriptDataType *dataType, int numElements);
	void Clear();
};

