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

#include "MwScriptExpressionVariableDeclaration.h"

#include "MwScriptExpressionAssignment.h"

MwScriptExpressionVariableDeclaration::MwScriptExpressionVariableDeclaration(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionVariableDeclaration::~MwScriptExpressionVariableDeclaration(void)
{
}

bool MwScriptExpressionVariableDeclaration::Run()
{
	MwScriptDataType *dataType = this->codeBuilder->dataTypes.Find(this->codeBuilder->GetToken()->name);

	if (dataType != 0)
	{
		this->codeBuilder->tokenIndex++;

		int numElements = 1;
		if (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_LeftIndexBracket)
		{
			this->codeBuilder->tokenIndex++;
			
			if (!this->codeBuilder->GetToken()->name.ToInt(numElements))
				return false;
			this->codeBuilder->tokenIndex++;

			if (this->codeBuilder->GetToken()->id != this->codeBuilder->tokenId_RightIndexBracket)
				return false;
			this->codeBuilder->tokenIndex++;
		}

		this->codeBuilder->tokenIndex--;
		
		do
		{
			this->codeBuilder->tokenIndex++;

			if (this->codeBuilder->GetToken()->id == -1)
			{
				MwScriptIdentifier *identifier = this->codeBuilder->identifiers.Find(this->codeBuilder->GetToken()->name);
				if (identifier == 0)
				{
					identifier = this->codeBuilder->identifiers.Add(this->codeBuilder->GetToken()->name, dataType, numElements);

					this->codeBuilder->tokenIndex++;

					if (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_Set)
					{
						this->codeBuilder->tokenIndex--;
						
						int endToken = this->codeBuilder->tokens.FindId(this->codeBuilder->tokenIndex, this->codeBuilder->tokens.count - 1, this->codeBuilder->tokenId_Comma);
						if (endToken == -1)
							endToken = this->codeBuilder->tokens.FindId(this->codeBuilder->tokenIndex, this->codeBuilder->tokens.count - 1, this->codeBuilder->tokenId_SemiColon);
						if (endToken != -1)
							this->codeBuilder->LockTokenRange(endToken - 1);
						if (!MwScriptExpressionAssignment(this->codeBuilder).Run())
							return false;
						this->codeBuilder->UnlockTokenRange();

						this->codeBuilder->tokenIndex--;
					}

					if (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_SemiColon)
					{
						this->codeBuilder->tokenIndex++;
						return true;
					}
				}
				else
					return false;
			}
			else 
				return false;
		}
		while (this->codeBuilder->GetToken()->id == this->codeBuilder->tokenId_Comma);
	}

	return false;
}
