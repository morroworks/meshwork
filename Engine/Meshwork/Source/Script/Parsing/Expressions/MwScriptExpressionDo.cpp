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

#include "MwScriptExpressionDo.h"

#include "MwScriptExpressionUnion.h"
#include "MwScriptExpressionEvaluation.h"

MwScriptExpressionDo::MwScriptExpressionDo(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionDo::~MwScriptExpressionDo(void)
{
}

bool MwScriptExpressionDo::Run()
{
	// do
	if (!this->codeBuilder->GetToken()->name.Equals("do"))
		return false;
	this->codeBuilder->tokenIndex++;

	long long jumpAddressDo = this->codeBuilder->code->position;

	// { ... }
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;

	// while
	if (!this->codeBuilder->GetToken()->name.Equals("while"))
		return false;
	this->codeBuilder->tokenIndex++;

	// (
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_LeftBracket)
		return false;
	this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindClosingBracket(this->codeBuilder->tokenId_RightBracket, this->codeBuilder->tokenIndex) - 1);
	this->codeBuilder->tokenIndex++;

	// x < y
	if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
		return false;
	this->codeBuilder->tokenIndex--;
	this->codeBuilder->UnlockTokenRange();

	// )
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_RightBracket)
		return false;
	this->codeBuilder->tokenIndex++;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JNZ);
	this->codeBuilder->code->WriteInt32((int)(jumpAddressDo - this->codeBuilder->code->position - 4));

	return true;
}