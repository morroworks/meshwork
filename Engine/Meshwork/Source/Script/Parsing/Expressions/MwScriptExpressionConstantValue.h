#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionConstantValue :
	public MwScriptExpression

{
public:
	MwScriptExpressionConstantValue(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionConstantValue(void);

	bool Run();
};

