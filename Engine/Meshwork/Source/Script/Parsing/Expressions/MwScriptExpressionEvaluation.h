#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionEvaluation :
	public MwScriptExpression

{
private:
	bool EvaluateExpression(int startToken, int endToken);

public:

	MwScriptExpressionEvaluation(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionEvaluation(void);

	bool Run();
};

