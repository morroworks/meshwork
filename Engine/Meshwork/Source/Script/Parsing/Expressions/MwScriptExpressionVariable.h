#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionVariable :
	public MwScriptExpression

{
public:
	bool assignmentMode;

	MwScriptExpressionVariable(MwCodeBuilder *codeBuilder, bool assignmentMode);
	~MwScriptExpressionVariable(void);

	bool Run();
};

