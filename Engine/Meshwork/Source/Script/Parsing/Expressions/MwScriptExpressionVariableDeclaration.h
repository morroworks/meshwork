#pragma once

#include "..\..\..\MwGlobals.h"

#include "MwScriptExpression.h"

class MwScriptExpressionVariableDeclaration :
	public MwScriptExpression
{
public:
	MwScriptExpressionVariableDeclaration(MwCodeBuilder *codeBuilder);
	~MwScriptExpressionVariableDeclaration(void);

	bool Run();
};

