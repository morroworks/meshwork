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

#include "MwScriptExpressionConstantValue.h"


MwScriptExpressionConstantValue::MwScriptExpressionConstantValue(MwCodeBuilder *codeBuilder) :
	MwScriptExpression(codeBuilder)
{
}


MwScriptExpressionConstantValue::~MwScriptExpressionConstantValue(void)
{
}

bool MwScriptExpressionConstantValue::Run()
{
    if (this->codeBuilder->tokenIndex < this->codeBuilder->tokens.count)
	{
		if (this->codeBuilder->tokenIndex + 2 < this->codeBuilder->tokens.count)
		{
			if (this->codeBuilder->tokens[this->codeBuilder->tokenIndex + 1].id == this->codeBuilder->tokenId_Point)
			{
				MwString floatValue = this->codeBuilder->tokens[this->codeBuilder->tokenIndex].name + this->codeBuilder->tokens[this->codeBuilder->tokenIndex + 1].name + this->codeBuilder->tokens[this->codeBuilder->tokenIndex + 2].name;
				if (floatValue.EndsWith('f'))
					floatValue.SetLength(floatValue.length - 1);
				double value;
				if (floatValue.ToDouble(value))
				{
					if (this->codeBuilder->dataType == this->codeBuilder->dataType_float)
					{
						this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FPushAddress);
						this->codeBuilder->code->WriteFloat((float)value);
					}
					else if (this->codeBuilder->dataType == this->codeBuilder->dataType_int)
					{
						this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IPushAddress);
						this->codeBuilder->code->WriteInt32((int)value);
					}

					this->codeBuilder->tokenIndex += 3;

					return true;
				}
			}
		}

		int value;
		if (this->codeBuilder->GetToken()->name.ToInt(value))
		{
			if (this->codeBuilder->dataType == this->codeBuilder->dataType_int)
			{
				this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_IPushAddress);
				this->codeBuilder->code->WriteInt32(value);
			}
			else if (this->codeBuilder->dataType == this->codeBuilder->dataType_float)
			{
				this->codeBuilder->code->WriteUInt8(this->codeBuilder->processor->operationId_FPushAddress);
				this->codeBuilder->code->WriteFloat((float)value);
			}

			this->codeBuilder->tokenIndex += 1;

			return true;
		}
	}

	return false;
}
