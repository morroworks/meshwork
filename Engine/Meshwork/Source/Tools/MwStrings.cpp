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

#include "MwStrings.h"


MwStrings::MwStrings(void)
	: MwList<MwString>()
{
}


MwStrings::~MwStrings(void)
{
}

void MwStrings::SplitString(MwString &string, const MwString &splitter, bool ignoreEmpty)
{
	this->Clear();
	
	int start = 0, end;
	do
	{
		end = string.IndexOf(splitter, start);
		if (end == -1)
			end = string.length;

		int length = end - start;
		if ((!ignoreEmpty) || (length > 0))
			this->Add(string.SubString(start, length));

		start = end + splitter.length;
	}
	while (start < string.length);

	// Attempt to reuse already existing strings
	//int start = 0, end, count = 0;
	//do
	//{
	//	end = string.IndexOf(splitter, start);
	//	if (end == -1)
	//		end = string.length;

	//	int length = end - start;
	//	if ((!ignoreEmpty) || (length > 0))
	//	{
	//		if (count + 1> this->count)
	//			this->Add(string.SubString(start, length));
	//		else
	//		{
	//			this->values[count].SetLength(length);
	//			this->values[count].CopyCharacters(0, string.contents, start, length);
	//		}

	//		count++;
	//	}

	//	start = end + splitter.length;
	//}
	//while (start < string.length);

	//this->SetSize(count);
}

MwString MwStrings::ToString(const MwString &splitter)
{
	MwString result;
	for (int i = 0;;)
	{
		result.Insert((*this)[i]);
		
		if (++i == this->count)
			break;

		result.Insert(splitter);
	}

	return MwString(result);
}

int MwStrings::IndexOf(MwString &string, StringComparison comparisonMode)
{
	if (comparisonMode == StringComparison_CaseSensitive)
	{
		for (int i = 0; i < this->count; i++)
			if ((*this)[i].Equals(string))
				return i;
	}
	else if (comparisonMode == StringComparison_CaseInsensitive)
	{
		MwString lower = string.ToLower();
		for (int i = 0; i < this->count; i++)
			if ((*this)[i].ToLower().Equals(lower))
				return i;
	}

	return -1;
}
