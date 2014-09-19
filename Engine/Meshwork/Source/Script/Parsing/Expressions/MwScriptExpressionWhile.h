#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionWhile :
	public MwScriptExpression
{
public:
	MwScriptExpressionWhile(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionWhile(void);

	bool Run();
};

