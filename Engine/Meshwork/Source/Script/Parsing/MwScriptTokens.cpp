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

#include "MwScriptTokens.h"


MwScriptTokens::MwScriptTokens(void)
{
}


MwScriptTokens::~MwScriptTokens(void)
{
}


int MwScriptTokens::AddSign(MwString sign)
{
	this->signSet.Add(sign);
	return this->signSet.count - 1;
}

void MwScriptTokens::Parse(MwString sourceCode)
{
	this->sourceCode = sourceCode;

	int scriptPos = 0;
	int identStart = 0;

	while (scriptPos < this->sourceCode.length)
	{
		int identLength = scriptPos - identStart;

		if (this->ignoreCharset.IndexOf(this->sourceCode[scriptPos]) != -1)
		{
			// Add any token that might have been read so far
			if (identLength > 0)
				this->Add(MwScriptToken(sourceCode.SubString(identStart, identLength), -1, identStart, scriptPos));

			identStart = scriptPos + 1;
		}
		else
		{
			int signIndex = this->FindSignIndex(scriptPos);
			if (signIndex != -1)
			{
				// Add any token that might have been read so far
				if (identLength > 0)
					this->Add(MwScriptToken(sourceCode.SubString(identStart, identLength), -1, identStart, scriptPos));

				// Add the special sign token that was met
				int signLength = this->signSet[signIndex].length;
				this->Add(MwScriptToken(sourceCode.SubString(scriptPos, signLength), signIndex, scriptPos, scriptPos + signLength));

				scriptPos += signLength - 1;
				identStart = scriptPos + 1;
			}
		}

		scriptPos++;
	}

	int identLength = scriptPos - identStart;
	if (identLength > 0)
		this->Add(MwScriptToken(sourceCode.SubString(identStart, identLength), -1, identStart, scriptPos));
}

int MwScriptTokens::FindSignIndex(int scriptPos)
{
	int result = -1;
	int resultLength = -1;
	for (int signIndex = 0; signIndex < this->signSet.count; signIndex++)
	{
		int stringLength = this->signSet[signIndex].length;
		if (stringLength > resultLength)
			if (scriptPos + stringLength <= this->sourceCode.length)
				for (int charIndex = 0; charIndex < stringLength; charIndex++)
					if (this->sourceCode[scriptPos + charIndex] == this->signSet[signIndex][charIndex])
					{
						if (charIndex == stringLength - 1)
						{
							result = signIndex;
							resultLength = stringLength;
						}
					}
					else
						break;

	}

	return result;
}

int MwScriptTokens::FindId(int startIndex, int endIndex, int signId)
{
	for (int index = startIndex; index <= endIndex; index++)
		if ((*this)[index].id == signId)
			return index;

	return -1;
}

int MwScriptTokens::FindClosingBracket(int closingBracketTokenId, int startIndex, int endIndex)
{
	int openingBracketTokenId = (*this)[startIndex].id;

	int numBrackets = 1;

	if (endIndex == -1)
		endIndex = this->count - 1;

	for (int i = startIndex + 1; i <= endIndex; i++)
	{
		int tokenId = (*this)[i].id;

		if (tokenId == openingBracketTokenId)
			numBrackets++;

		if (tokenId == closingBracketTokenId)
		{
			numBrackets--;

			if (numBrackets == 0)
				return i;
		}
	}

	return -1;
}