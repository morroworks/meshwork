#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionAssignment :
	public MwScriptExpression
{
public:
	MwScriptExpressionAssignment(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionAssignment(void);

	bool Run();
};

