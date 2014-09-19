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

#include "MwScriptExpressionUnion.h"

#include "MwScriptExpressionAssignment.h"
#include "MwScriptExpressionEvaluation.h"
#include "MwScriptExpressionVariableDeclaration.h"
#include "MwScriptExpressionIf.h"
#include "MwScriptExpressionTernaryIf.h"
#include "MwScriptExpressionWhile.h"
#include "MwScriptExpressionFor.h"
#include "MwScriptExpressionDo.h"

MwScriptExpressionUnion::MwScriptExpressionUnion(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionUnion::~MwScriptExpressionUnion(void)
{
}

bool MwScriptExpressionUnion::Run()
{
	int numBrackets = 0;

	do
	{
		if (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_LeftBracket_Big)
		{
			numBrackets++;
			this->codeBuilder->tokenIndex++;
		}
		else if (this->codeBuilder->GetToken()->id ==  this->codeBuilder->tokenId_RightBracket_Big)
		{
			numBrackets--;
			this->codeBuilder->tokenIndex++;
		}
		else
		{
			if (!MwScriptExpressionAssignment(this->codeBuilder).Build())
				if (!MwScriptExpressionEvaluation(this->codeBuilder).Build())
					if (!MwScriptExpressionVariableDeclaration(this->codeBuilder).Build())
						if (!MwScriptExpressionIf(this->codeBuilder).Build())
							if (!MwScriptExpressionTernaryIf(this->codeBuilder).Build())
								if (!MwScriptExpressionWhile(this->codeBuilder).Build())
									if (!MwScriptExpressionFor(this->codeBuilder).Build())
										if (!MwScriptExpressionDo(this->codeBuilder).Build())
											return false;
		}
	}
	while (numBrackets > 0);

	return true;
}