#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionCallout :
	public MwScriptExpression
{
public:
	MwScriptExpressionCallout(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionCallout(void);
};

