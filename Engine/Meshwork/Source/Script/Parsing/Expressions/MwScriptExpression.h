#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\MwCodeBuilder.h"

#include "..\..\Processing\MwCodeProcessor.h"

class MwScriptExpression
{
public:
	MwCodeBuilder *codeBuilder;

	MwScriptExpression(MwCodeBuilder *codeBuilder);
	~MwScriptExpression(void);

	// If succeeds, returns true and leaves the token index after the end of the expression's last token (and at the beginning of the next, if any)
	// If fails, returns false. The token index and other code generation variables remain undefined and should be reset to the state before calling the method
	// This method can be called inside other MwScriptExpression Run methods, but only with having in mind that if it fails, the codeBuilder state (tokenIndex, code position and etc.) remain undefined.
	virtual bool Run() = 0;

	// Executes the Run method and if it fails, resets the codeBuilder's state as it was before the call, so the codeBuilder is ready for any other expression to try to build
	bool Build();
};

