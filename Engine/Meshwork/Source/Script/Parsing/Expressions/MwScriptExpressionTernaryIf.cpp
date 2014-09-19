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

#include "MwScriptExpressionTernaryIf.h"

#include "MwScriptExpressionEvaluation.h"
#include "MwScriptExpressionUnion.h"

MwScriptExpressionTernaryIf::MwScriptExpressionTernaryIf(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionTernaryIf::~MwScriptExpressionTernaryIf(void)
{
}

bool MwScriptExpressionTernaryIf::Run()
{
	// x == y
	this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindId(this->codeBuilder->tokenIndex, this->codeBuilder->tokens.count, this->codeBuilder->tokenId_Question) - 1);
	if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
		return false;
	this->codeBuilder->UnlockTokenRange();
	this->codeBuilder->tokenIndex--;

	// ?
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_Question)
		return false;
	this->codeBuilder->tokenIndex++;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JZ);
	long long jumpAddressEndIf = this->codeBuilder->code->position;
	this->codeBuilder->code->WriteInt32(0);

	// x++
	this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindId(this->codeBuilder->tokenIndex, this->codeBuilder->tokens.count, this->codeBuilder->tokenId_Colon) - 1);
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;
	this->codeBuilder->UnlockTokenRange();
	this->codeBuilder->tokenIndex--;

	// :
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_Colon)
		return false;
	this->codeBuilder->tokenIndex++;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JMP);
	long long jumpAddressEndElse = this->codeBuilder->code->position;
	this->codeBuilder->code->WriteInt32(0);

	long long endCodePos = this->codeBuilder->code->position;
	this->codeBuilder->code->Seek(jumpAddressEndIf);
	this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
	this->codeBuilder->code->Seek(endCodePos);

	// y++;
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;

	endCodePos = this->codeBuilder->code->position;
	this->codeBuilder->code->Seek(jumpAddressEndElse);
	this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
	this->codeBuilder->code->Seek(endCodePos);

	return true;
}
