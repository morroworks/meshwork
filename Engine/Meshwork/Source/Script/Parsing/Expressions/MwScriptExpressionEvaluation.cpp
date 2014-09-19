//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwScriptExpressionEvaluation.h"

#include "MwScriptExpressionConstantValue.h"
#include "MwScriptExpressionVariable.h"

MwScriptExpressionEvaluation::MwScriptExpressionEvaluation(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionEvaluation::~MwScriptExpressionEvaluation(void)
{
}

bool MwScriptExpressionEvaluation::EvaluateExpression(int startToken, int endToken)
{
	if (this->codeBuilder->tokens[startToken].id == this->codeBuilder->tokenId_LeftBracket)
    {
        // if we have a fully-bracketed expression, reevaluate it without the brackets.
        if (this->codeBuilder->tokens.FindClosingBracket(this->codeBuilder->tokenId_RightBracket, startToken) == endToken)
            return this->EvaluateExpression(startToken + 1, endToken - 1);
    }

	int operationId;
	int operationTokenId = this->codeBuilder->FindTokenEvaluationOperationByPriority(startToken, endToken, operationId);

    if (operationTokenId == -1)
    {
		this->codeBuilder->tokenIndex = startToken;
		if (!MwScriptExpressionConstantValue(this->codeBuilder).Build())
			if (!MwScriptExpressionVariable(this->codeBuilder, false).Build())
				return false;

		return this->codeBuilder->tokenIndex > endToken;
    }
    else
    {
        bool right = this->EvaluateExpression(operationTokenId + 1, endToken);
        bool left = this->EvaluateExpression(startToken, operationTokenId - 1);

		this->codeBuilder->code->WriteUInt8(operationId);

        return left && right;
    }
}

bool MwScriptExpressionEvaluation::Run()
{
	int start = this->codeBuilder->tokenIndex;
	int end = 0;

	while (this->codeBuilder->GetToken(end) != this->codeBuilder->invalidToken)
		if (this->codeBuilder->GetToken(end)->id == this->codeBuilder->tokenId_SemiColon)
			break;
		else
			end++;
	end += start;

	bool result = this->EvaluateExpression(start, end - 1);

	this->codeBuilder->tokenIndex = end + 1;

	return result;
}
