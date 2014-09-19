#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionFor :
	public MwScriptExpression
{
public:
	MwScriptExpressionFor(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionFor(void);

	bool Run();
};

