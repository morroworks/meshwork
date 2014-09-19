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

#include "MwScriptExpressionFor.h"

#include "MwScriptExpressionEvaluation.h"
#include "MwScriptExpressionUnion.h"


MwScriptExpressionFor::MwScriptExpressionFor(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionFor::~MwScriptExpressionFor(void)
{
}

bool MwScriptExpressionFor::Run()
{
	// for
	if (!this->codeBuilder->GetToken()->name.Equals("for"))
		return false;
	this->codeBuilder->tokenIndex++;

	// (
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_LeftBracket)
		return false;
	this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindClosingBracket(this->codeBuilder->tokenId_RightBracket, this->codeBuilder->tokenIndex) - 1);
	this->codeBuilder->tokenIndex++;

	// int i = 0;
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;

	long long jumpAddressConditionFor = this->codeBuilder->code->position;

	// i < 10;
	if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
		return false;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JZ);
	long long jumpAddressEndFor = this->codeBuilder->code->position;
	this->codeBuilder->code->WriteInt32(0);

	// i++; Performed after the body, so written in another memory and patched later, after the body
	MwMemoryStream *originalCode = this->codeBuilder->code;
	this->codeBuilder->code = new MwMemoryStream();
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;
	MwMemoryStream *postOperation = this->codeBuilder->code;
	this->codeBuilder->code = originalCode;
	this->codeBuilder->UnlockTokenRange();

	// )
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_RightBracket)
		return false;
	this->codeBuilder->tokenIndex++;

	// {...}
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;

	postOperation->Seek(0);
	this->codeBuilder->code->WriteStreamData(*postOperation);
	delete postOperation;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JMP);
	this->codeBuilder->code->WriteInt32((int)(jumpAddressConditionFor - this->codeBuilder->code->position - 4));

	long long endCodePos = this->codeBuilder->code->position;
	this->codeBuilder->code->Seek(jumpAddressEndFor);
	this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
	this->codeBuilder->code->Seek(endCodePos);

	return true;
}