#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionIf :
	public MwScriptExpression
{
public:
	MwScriptExpressionIf(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionIf(void);

	bool Run();
};

