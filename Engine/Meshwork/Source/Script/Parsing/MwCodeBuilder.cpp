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

#include "MwCodeBuilder.h"

#include "Expressions\MwScriptExpression.h"
#include "Expressions\MwScriptExpressionUnion.h"

#include "..\..\Tools\MwMem.h"

MwScriptTokenToOperationMapping::MwScriptTokenToOperationMapping(int tokenId, int iOperationId, int fOperationId, bool isAssignmentOperation, bool singleArgument)
{
	this->tokenId = tokenId;
	this->iOperationId = iOperationId;
	this->fOperationId = fOperationId;
	this->isAssignmentOperation = isAssignmentOperation;
	this->singleArgument = singleArgument;
}

MwCodeBuilder::MwCodeBuilder(void)
{
	this->tokens.ignoreCharset = " \n\r\t";

	this->tokenId_LeftBracket		= this->tokens.AddSign("(");
	this->tokenId_RightBracket		= this->tokens.AddSign(")");
	this->tokenId_LeftIndexBracket	= this->tokens.AddSign("[");
	this->tokenId_RightIndexBracket	= this->tokens.AddSign("]");
	this->tokenId_LeftBracket_Big	= this->tokens.AddSign("{");
	this->tokenId_RightBracket_Big	= this->tokens.AddSign("}");
	this->tokenId_Point				= this->tokens.AddSign(".");
	this->tokenId_Comma				= this->tokens.AddSign(",");
	this->tokenId_Colon				= this->tokens.AddSign(":");
	this->tokenId_SemiColon			= this->tokens.AddSign(";");
	this->tokenId_Question			= this->tokens.AddSign("?");
	// Evaluation tokens - token's respective operation yields a resulting value
	this->tokenId_BinNot			= this->tokens.AddSign("~");
	this->tokenId_BinAnd			= this->tokens.AddSign("&");
	this->tokenId_BinOr				= this->tokens.AddSign("|");
	this->tokenId_BinXor			= this->tokens.AddSign("^");
	this->tokenId_LogicalNot		= this->tokens.AddSign("!");
	this->tokenId_LogicalAnd		= this->tokens.AddSign("&&");
	this->tokenId_LogicalOr			= this->tokens.AddSign("||");
	this->tokenId_Greater			= this->tokens.AddSign(">");
	this->tokenId_Lesser			= this->tokens.AddSign("<");
	this->tokenId_Equal				= this->tokens.AddSign("==");
	this->tokenId_NotEqual			= this->tokens.AddSign("!=");
	this->tokenId_GreaterEqual		= this->tokens.AddSign(">=");
	this->tokenId_LesserEqual		= this->tokens.AddSign("<=");
	this->tokenId_Shl				= this->tokens.AddSign("<<");
	this->tokenId_Shr				= this->tokens.AddSign(">>");
	this->tokenId_Div				= this->tokens.AddSign("/");
	this->tokenId_Mod				= this->tokens.AddSign("%");
	this->tokenId_Mul				= this->tokens.AddSign("*");
	this->tokenId_Sub				= this->tokens.AddSign("-");
	this->tokenId_Add				= this->tokens.AddSign("+");
	// Assignment tokens - token's respective operation sets a value to a variable
	this->tokenId_Set				= this->tokens.AddSign("=");
	this->tokenId_SubSub			= this->tokens.AddSign("--");
	this->tokenId_AddAdd			= this->tokens.AddSign("++");
	this->tokenId_AddEquals			= this->tokens.AddSign("+=");
	this->tokenId_SubEquals			= this->tokens.AddSign("-=");
	this->tokenId_MulEquals			= this->tokens.AddSign("*=");
	this->tokenId_DivEquals			= this->tokens.AddSign("/=");
	this->tokenId_XorEquals			= this->tokens.AddSign("^=");
	this->tokenId_OrEquals			= this->tokens.AddSign("|=");
	this->tokenId_AndEquals			= this->tokens.AddSign("&=");
	this->tokenId_ModEquals			= this->tokens.AddSign("%=");

	this->dataType_int		= this->dataTypes.Add(new MwScriptDataType("int", 4));
	this->dataType_float	= this->dataTypes.Add(new MwScriptDataType("float", 4));
	this->dataType = this->dataType_int;

	this->code = new MwMemoryStream();

	this->invalidToken = new MwScriptToken("INVALID_TOKEN", -999, -1, -1);
}


MwCodeBuilder::~MwCodeBuilder(void)
{
	delete invalidToken;
	
	delete this->code;

	for (int i = 0; i < this->tokenToOperationMapping.count; i++)
		delete this->tokenToOperationMapping[i];
}

void MwCodeBuilder::LockTokenRange(int lastTokenIndex)
{
	this->tokenRanges.Push(lastTokenIndex);
}

void MwCodeBuilder::UnlockTokenRange()
{
	if (this->tokenRanges.count > 0)
		this->tokenRanges.Pop();
}

MwScriptToken *MwCodeBuilder::GetToken(int peekOffset)
{
	int checkIndex = this->tokenIndex + peekOffset;
	int lastTokenIndex = this->tokenRanges.count > 0 ? this->tokenRanges.Peek() : this->tokens.count - 1;

	if ((checkIndex < 0) || (checkIndex > lastTokenIndex))
		return this->invalidToken;

	return &this->tokens[checkIndex];
}

int MwCodeBuilder::FindTokenEvaluationOperationByPriority(int startToken, int endToken, int &operationId)
{
	for (int mappingIndex = this->tokenToOperationMapping.count - 1; mappingIndex >= 0 ; mappingIndex--)
	{
		if (!this->tokenToOperationMapping[mappingIndex]->isAssignmentOperation)
		{
			int bracketLevel = 0;
			for (int tokenIndex = startToken; tokenIndex <= endToken; tokenIndex++)
			{
				if (bracketLevel == 0)
				{
					if (this->tokens[tokenIndex].id == this->tokenToOperationMapping[mappingIndex]->tokenId)
					{
						if (this->dataType == this->dataType_int)
							operationId = this->tokenToOperationMapping[mappingIndex]->iOperationId;
						else if (this->dataType == this->dataType_float)
							operationId = this->tokenToOperationMapping[mappingIndex]->fOperationId;

						return tokenIndex;
					}
				}
        
				if ((this->tokens[tokenIndex].id == this->tokenId_LeftBracket) || (this->tokens[tokenIndex].id == this->tokenId_LeftIndexBracket))
					bracketLevel++;
				else
					if ((this->tokens[tokenIndex].id == this->tokenId_RightBracket) || (this->tokens[tokenIndex].id == this->tokenId_RightIndexBracket))
						bracketLevel--;
			}
		}
	}

	operationId = -1;
	return -1;
}

int MwCodeBuilder::GetTokenAssignmentOperation()
{
	if (this->tokenIndex >= this->tokens.count)
		return -1;
	int tokenId = this->tokens[this->tokenIndex].id;

	for (int mappingIndex = this->tokenToOperationMapping.count - 1; mappingIndex >= 0 ; mappingIndex--)
	{
		if (this->tokenToOperationMapping[mappingIndex]->isAssignmentOperation)
			if (this->tokenToOperationMapping[mappingIndex]->tokenId == tokenId)
				if (this->dataType == this->dataType_int)
					return this->tokenToOperationMapping[mappingIndex]->iOperationId;
				else if (this->dataType == this->dataType_float)
					return this->tokenToOperationMapping[mappingIndex]->fOperationId;

	}

	return -1;
}

void MwCodeBuilder::SetProcessor(MwCodeProcessor *processor)
{
	this->processor = processor;

	this->tokenToOperationMapping.Clear();
	// Evaluation operations (evaluation operations sorted from greater to lesser priority)
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_BinNot,			this->processor->operationId_INot,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_BinAnd,			this->processor->operationId_IAnd,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_BinOr,			this->processor->operationId_IOr,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_BinXor,			this->processor->operationId_IXor,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Shl,			this->processor->operationId_IShl,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Shr,			this->processor->operationId_IShr,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Div,			this->processor->operationId_IDiv,			this->processor->operationId_FDiv,			false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Mod,			this->processor->operationId_IMod,			-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Mul,			this->processor->operationId_IMul,			this->processor->operationId_FMul,			false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Sub,			this->processor->operationId_ISub,			this->processor->operationId_FSub,			false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Add,			this->processor->operationId_IAdd,			this->processor->operationId_FAdd,			false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_LogicalNot,		this->processor->operationId_ILogicalNot,	-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_LogicalAnd,		this->processor->operationId_ILogicalAnd,	-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_LogicalOr,		this->processor->operationId_ILogicalOr,	-1,											false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Greater,		this->processor->operationId_IGreater,		this->processor->operationId_FGreater,		false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Lesser,			this->processor->operationId_ILesser,		this->processor->operationId_FLesser,		false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Equal,			this->processor->operationId_IEqual,		this->processor->operationId_FEqual,		false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_NotEqual,		this->processor->operationId_INotEqual,		this->processor->operationId_FNotEqual,		false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_GreaterEqual,	this->processor->operationId_IGreaterEqual,	this->processor->operationId_FGreaterEqual,	false,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_LesserEqual,	this->processor->operationId_ILesserEqual,	this->processor->operationId_FLesserEqual,	false,	false));
	// Assignment operations
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_Set,			this->processor->operationId_ISet,			this->processor->operationId_FSet,			true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_AddAdd,			this->processor->operationId_IAddAdd,		-1,											true,	true));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_SubSub,			this->processor->operationId_ISubSub,		-1,											true,	true));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_AddEquals,		this->processor->operationId_IAddEquals,	this->processor->operationId_FAddEquals,	true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_SubEquals,		this->processor->operationId_ISubEquals,	this->processor->operationId_FSubEquals,	true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_ModEquals,		this->processor->operationId_IModEquals,	-1,											true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_MulEquals,		this->processor->operationId_IMulEquals,	this->processor->operationId_FMulEquals,	true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_DivEquals,		this->processor->operationId_IDivEquals,	this->processor->operationId_FDivEquals,	true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_XorEquals,		this->processor->operationId_IXorEquals,	-1,											true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_OrEquals,		this->processor->operationId_IOrEquals,		-1,											true,	false));
	this->tokenToOperationMapping.Add(new MwScriptTokenToOperationMapping(this->tokenId_AndEquals,		this->processor->operationId_IAndEquals,	-1,											true,	false));
}

bool MwCodeBuilder::Build(MwBaseStream *output, MwString sourceCode)
{
	this->tokens.Clear();
	this->tokens.Parse(sourceCode);

	this->tokenIndex = 0;

	this->identifiers.Clear();

	this->code->Seek(0);

	while (this->tokenIndex < this->tokens.count)
		if (!MwScriptExpressionUnion(this).Build())
			return false;

	output->Seek(0);
	output->length = 0;

	void *variables = MwMem::Get(this->identifiers.size);
	MwMem::Zero(variables, this->identifiers.size);
	output->WriteData(variables, this->identifiers.size);
	MwMem::FreeAndNull(&variables);

	long long codePos = output->position;
	this->code->Seek(0);
	output->WriteStreamData(*this->code);
	output->Seek(codePos);

	return true;
}
