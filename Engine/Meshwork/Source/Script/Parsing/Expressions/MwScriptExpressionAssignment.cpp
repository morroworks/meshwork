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

#include "MwScriptExpressionAssignment.h"

#include "MwScriptExpressionVariable.h"
#include "MwScriptExpressionEvaluation.h"
#include "MwScriptExpressionUnion.h"

MwScriptExpressionAssignment::MwScriptExpressionAssignment(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionAssignment::~MwScriptExpressionAssignment(void)
{
}

bool MwScriptExpressionAssignment::Run()
{
	if (!MwScriptExpressionVariable(this->codeBuilder, true).Run())
		return false;

	int operationId = this->codeBuilder->GetTokenAssignmentOperation();
	if (operationId == -1)
		return false;

	this->codeBuilder->tokenIndex++;

	if (this->codeBuilder->GetToken() != this->codeBuilder->invalidToken)
		if (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_SemiColon)
			this->codeBuilder->tokenIndex++;
		else
			if (!MwScriptExpressionUnion(this->codeBuilder).Run())
			//if (!MwScriptExpressionEvaluation(this->codeBuilder).Run())
				return false;

	this->codeBuilder->code->WriteUInt8(operationId);
	
	return true;
}