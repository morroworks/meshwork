#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionTernaryIf :
	public MwScriptExpression
{
public:
	MwScriptExpressionTernaryIf(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionTernaryIf(void);

	bool Run();
};

