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

#include "MwScriptExpressionWhile.h"

#include "MwScriptExpressionEvaluation.h"
#include "MwScriptExpressionUnion.h"

MwScriptExpressionWhile::MwScriptExpressionWhile(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionWhile::~MwScriptExpressionWhile(void)
{
}

bool MwScriptExpressionWhile::Run()
{
	// while
	if (!this->codeBuilder->GetToken()->name.Equals("while"))
		return false;
	this->codeBuilder->tokenIndex++;

	// (
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_LeftBracket)
		return false;
	this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindClosingBracket(this->codeBuilder->tokenId_RightBracket, this->codeBuilder->tokenIndex) - 1);
	this->codeBuilder->tokenIndex++;

	long long jumpAddressConditionWhile = this->codeBuilder->code->position;

	// x < y
	if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
		return false;
	this->codeBuilder->tokenIndex--;

	// )
	this->codeBuilder->UnlockTokenRange();
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_RightBracket)
		return false;
	this->codeBuilder->tokenIndex++;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JZ);
	long long jumpAddressEndWhile = this->codeBuilder->code->position;
	this->codeBuilder->code->WriteInt32(0);

	// { ... }
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JMP);
	this->codeBuilder->code->WriteInt32((int)(jumpAddressConditionWhile - this->codeBuilder->code->position - 4));

	long long endCodePos = this->codeBuilder->code->position;
	this->codeBuilder->code->Seek(jumpAddressEndWhile);
	this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
	this->codeBuilder->code->Seek(endCodePos);

    return true;
}