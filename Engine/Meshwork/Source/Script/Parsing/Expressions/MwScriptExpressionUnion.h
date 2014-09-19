#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionUnion :
	public MwScriptExpression
{
public:
	MwScriptExpressionUnion(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionUnion(void);

	bool Run();
};

