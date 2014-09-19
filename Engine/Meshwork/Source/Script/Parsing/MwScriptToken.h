#pragma once

#include "..\..\MwGlobals.h"

#include "..\..\Tools\MwString.h"

class MWDLLCLASS MwScriptToken
{
public:
	MwString name;
	int id;
	int start, end;

	MwScriptToken(void);
	MwScriptToken(MwString name, int id, int start, int end);
	~MwScriptToken(void);
};

