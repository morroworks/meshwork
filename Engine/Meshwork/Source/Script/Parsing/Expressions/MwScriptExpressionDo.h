#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionDo :
	public MwScriptExpression
{
public:
	MwScriptExpressionDo(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionDo(void);

	bool Run();
};

