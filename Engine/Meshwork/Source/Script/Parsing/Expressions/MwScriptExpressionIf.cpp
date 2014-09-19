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

#include "MwScriptExpressionIf.h"

#include "MwScriptExpressionEvaluation.h"
#include "MwScriptExpressionUnion.h"

MwScriptExpressionIf::MwScriptExpressionIf(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionIf::~MwScriptExpressionIf(void)
{
}

bool MwScriptExpressionIf::Run()
{
	// if
	if (!this->codeBuilder->GetToken()->name.Equals("if"))
		return false;
	this->codeBuilder->tokenIndex++;

	// (
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_LeftBracket)
		return false;
	this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindClosingBracket(this->codeBuilder->tokenId_RightBracket, this->codeBuilder->tokenIndex) - 1);
	this->codeBuilder->tokenIndex++;

	// x == y
	if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
		return false;
	this->codeBuilder->tokenIndex--;
	this->codeBuilder->UnlockTokenRange();

	// )
	if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_RightBracket)
		return false;
	this->codeBuilder->tokenIndex++;

	this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JZ);
	long long jumpAddressEndIf = this->codeBuilder->code->position;
	this->codeBuilder->code->WriteInt32(0);

	// { .. }
	if (!MwScriptExpressionUnion(this->codeBuilder).Run())
		return false;

	// else
	if (this->codeBuilder->GetToken()->name.Equals("else"))
	{
		this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_JMP);
		long long jumpAddressEndElse = this->codeBuilder->code->position;
		this->codeBuilder->code->WriteInt32(0);

		long long endCodePos = this->codeBuilder->code->position;
		this->codeBuilder->code->Seek(jumpAddressEndIf);
		this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
		this->codeBuilder->code->Seek(endCodePos);

		this->codeBuilder->tokenIndex++;

		if (!MwScriptExpressionUnion(this->codeBuilder).Run())
			return false;

		endCodePos = this->codeBuilder->code->position;
		this->codeBuilder->code->Seek(jumpAddressEndElse);
		this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
		this->codeBuilder->code->Seek(endCodePos);
	}
	else
	{
		long long endCodePos = this->codeBuilder->code->position;
		this->codeBuilder->code->Seek(jumpAddressEndIf);
		this->codeBuilder->code->WriteInt32((int)(endCodePos - this->codeBuilder->code->position - 4));
		this->codeBuilder->code->Seek(endCodePos);
	}

	return true;
}