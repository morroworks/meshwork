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

#include "MwScriptExpressionVariable.h"

#include "..\MwScriptIdentifier.h"
#include "MwScriptExpressionEvaluation.h"

MwScriptExpressionVariable::MwScriptExpressionVariable(MwCodeBuilder *codeBuilder, bool assignmentMode) :
	MwScriptExpression(codeBuilder)
{
	this->assignmentMode = assignmentMode;
}


MwScriptExpressionVariable::~MwScriptExpressionVariable(void)
{
}

bool MwScriptExpressionVariable::Run()
{
	MwScriptIdentifier *identifier = this->codeBuilder->identifiers.Find(this->codeBuilder->GetToken()->name);
	
	if (identifier != 0)
	{
		this->codeBuilder->tokenIndex++;

		bool indexed = false;
		if (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_LeftIndexBracket)
		{
			this->codeBuilder->LockTokenRange(this->codeBuilder->tokens.FindClosingBracket(this->codeBuilder->tokenId_RightIndexBracket, this->codeBuilder->tokenIndex) - 1);
			this->codeBuilder->tokenIndex++;
			if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
				return false;
			this->codeBuilder->UnlockTokenRange();

			this->codeBuilder->tokenIndex--;
			if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_RightIndexBracket)
				return false;
			this->codeBuilder->tokenIndex++;

			indexed = true;
		}

		if (this->assignmentMode)
		{
			this->codeBuilder->dataType = identifier->dataType;

			// Set an operation that puts the address of the variable into the stack
			if (indexed)
			{
				if (identifier->dataType == this->codeBuilder->dataType_int)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IPushIndexedAddress);
				else if (identifier->dataType == this->codeBuilder->dataType_float)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FPushIndexedAddress);
			}
			else
			{
				if (identifier->dataType == this->codeBuilder->dataType_int)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IPushAddress);
				else if (identifier->dataType == this->codeBuilder->dataType_float)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FPushAddress);
			}

			this->codeBuilder->code->WriteUInt32(identifier->address);
		}
		else
		{
			// Set an operation that puts the value of the variable's address into the stack
			if (indexed)
			{
				if (identifier->dataType == this->codeBuilder->dataType_int)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IPushIndexedAddressValue);
				else if (identifier->dataType == this->codeBuilder->dataType_float)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FPushIndexedAddressValue);
			}
			else
			{
				if (identifier->dataType == this->codeBuilder->dataType_int)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IPushAddressValue);
				else if (identifier->dataType == this->codeBuilder->dataType_float)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FPushAddressValue);
			}

			this->codeBuilder->code->WriteUInt32(identifier->address);

			// Convert data type if necessary
			if (identifier->dataType == this->codeBuilder->dataType_float)
				if (this->codeBuilder->dataType == this->codeBuilder->dataType_int)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FToI);

			if (identifier->dataType == this->codeBuilder->dataType_int)
				if (this->codeBuilder->dataType == this->codeBuilder->dataType_float)
					this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IToF);
		}

		return true;
	}

	return false;
}
