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

#include "MwScriptExpression.h"


MwScriptExpression::MwScriptExpression(MwCodeBuilder *codeBuilder)
{
	this->codeBuilder = codeBuilder;
}


MwScriptExpression::~MwScriptExpression(void)
{
}

bool MwScriptExpression::Build()
{
	int startTokenIndex = this->codeBuilder->tokenIndex;
	int startCodePos = (int)this->codeBuilder->code->position;
	int numTokenRangeLocks = this->codeBuilder->tokenRanges.count;
	int numIdentifiers = this->codeBuilder->identifiers.list.count;
	bool result = this->Run();
	if (!result)
	{
		this->codeBuilder->tokenIndex = startTokenIndex;
		this->codeBuilder->code->Seek(startCodePos);
		while (this->codeBuilder->tokenRanges.count > numTokenRangeLocks)
			this->codeBuilder->tokenRanges.Pop();
		for (int i = numIdentifiers; i < this->codeBuilder->identifiers.list.count; i++)
			delete this->codeBuilder->identifiers.list[i];
		this->codeBuilder->identifiers.list.SetSize(numIdentifiers);
	}

	return result;
}
