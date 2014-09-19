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

#include "MwString.h"

#include <stdlib.h>
#include <string>

#include "MwMem.h"
#include "MwMath.h"

MwString base64Map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

MwString::MwString(void)
{
	this->Initialize();
}

MwString::MwString(MwString &str)
{
	this->Initialize();
	*this = str;
}

MwString::MwString(const char *str)
{
	this->Initialize();
	*this = str;
}

MwString::MwString(const wchar_t *str)
{
	this->Initialize();
	*this = str;
}

MwString::MwString(const char *str, int length)
{
	this->Initialize();

	this->EnsureCapacity(length);

	int i;
	for (i = 0; i < length; i++)
		this->contents[i] = str[i];

	this->contents[length] = 0;
	this->length = length;

	this->charContentsChanged = true;
}

MwString::MwString(const wchar_t *str, int length)
{
	this->Initialize();
	
	this->EnsureCapacity(length);

	MwMem::Copy(this->contents, str, length * sizeof(wchar_t));

	this->contents[length] = 0;
	this->length = length;

	this->charContentsChanged = true;
}

MwString::MwString(char str)
{
	this->Initialize();

	this->EnsureCapacity(1);

	this->contents[0] = str;

	this->contents[1] = 0;
	this->length = 1;

	this->charContentsChanged = true;
}

MwString::MwString(wchar_t str)

{
	this->Initialize();

	this->EnsureCapacity(1);

	this->contents[0] = str;

	this->contents[1] = 0;
	this->length = 1;

	this->charContentsChanged = true;
}

MwString::MwString(int value, int radix)
{
	this->Initialize();

	int maxLength = sizeof(int) * 8;
	wchar_t *v = new wchar_t[maxLength + 1];
	_itow_s(value, v, maxLength, radix);
	*this = v;
	delete[] v;
}

MwString::MwString(unsigned int value, int radix)
{
	this->Initialize();

	int maxLength = sizeof(int) * 8;
	wchar_t *v = new wchar_t[maxLength + 1];
	_i64tow_s(value, v, maxLength, radix);
	*this = v;
	delete[] v;
}

MwString::MwString(long long value, int radix)
{
	this->Initialize();

	int maxLength = sizeof(int) * 8;
	wchar_t *v = new wchar_t[maxLength + 1];
	_i64tow_s(value, v, maxLength, radix);
	*this = v;
	delete[] v;
}

MwString::MwString(unsigned long long value, int radix)
{
	this->Initialize();

	int maxLength = sizeof(int) * 8;
	wchar_t *v = new wchar_t[maxLength + 1];
	_ui64tow_s(value, v, maxLength, radix);
	*this = v;
	delete[] v;
}

MwString::MwString(double value)
{
	this->Initialize();

	*this = std::to_wstring((long double)value).c_str();
}

MwString::~MwString(void)
{
	delete[] this->contents;
	
	if (this->charContents != 0)
		delete[] this->charContents;
}


wchar_t &MwString::operator [] (int index) 
{ 
	return this->contents[index];
}


// MwString operators
void MwString::operator = (const MwString &argument) 
{ 
	this->Copy(argument);
}

void MwString::operator += (const MwString &argument) 
{ 
	this->Insert(argument);
}

MwString MwString::operator + (const MwString &argument) 
{ 
	MwString result;
	result.Copy(*this);
	result.Insert(argument);

	return MwString(result.GetContents());
}

bool MwString::operator == (const MwString &argument) 
{ 
	return this->Compare(argument) == 0;
}

bool MwString::operator != (const MwString &argument) 
{ 
	return this->Compare(argument) != 0;
}

bool MwString::operator > (const MwString &argument) 
{ 
	return this->Compare(argument) > 0;
}

bool MwString::operator >= (const MwString &argument) 
{ 
	return this->Compare(argument) >= 0;
}

bool MwString::operator < (const MwString &argument) 
{ 
	return this->Compare(argument) < 0;
}

bool MwString::operator <= (const MwString &argument) 
{ 
	return Compare(argument) <= 0;
}


// WChar operators
void MwString::operator = (const wchar_t *argument) 
{ 
	this->Copy(argument);
}

void MwString::operator += (const wchar_t *argument) 
{ 
	this->Insert(argument);
}

MwString MwString::operator + (const wchar_t *argument) 
{ 
	MwString result;
	result.Copy(*this);
	result.Insert(argument);

	return MwString(result);
}

bool MwString::operator == (const wchar_t *argument) 
{ 
	return this->Compare(argument) == 0;
}

bool MwString::operator != (const wchar_t *argument) 
{ 
	return this->Compare(argument) != 0;
}

bool MwString::operator > (const wchar_t *argument) 
{ 
	return this->Compare(argument) > 0;
}

bool MwString::operator >= (const wchar_t *argument) 
{ 
	return this->Compare(argument) >= 0;
}

bool MwString::operator < (const wchar_t *argument) 
{ 
	return this->Compare(argument) < 0;
}

bool MwString::operator <= (const wchar_t *argument) 
{ 
	return this->Compare(argument) <= 0;
}


// Char operators
void MwString::operator = (const char *argument) 
{ 
	this->Copy(argument);
}

void MwString::operator += (const char *argument) 
{ 
	this->Insert(argument);
}

MwString MwString::operator + (const char *argument) 
{
	MwString result;
	result.Copy(*this);
	result.Insert(argument);

	return MwString(result);
}

bool MwString::operator == (const char *argument) 
{ 
	return this->Compare(argument) == 0;
}

bool MwString::operator != (const char *argument) 
{ 
	return this->Compare(argument) != 0;
}

bool MwString::operator > (const char *argument) 
{ 
	return this->Compare(argument) > 0;
}

bool MwString::operator >= (const char *argument) 
{ 
	return this->Compare(argument) >= 0;
}

bool MwString::operator < (const char *argument) 
{ 
	return this->Compare(argument) < 0;
}

bool MwString::operator <= (const char *argument) 
{ 
	return this->Compare(argument) <= 0;
}

// Dynamic methods
void MwString::Initialize()
{
	this->length = 0;
	this->capacity = 0;
	this->contents = 0;
	this->ResizeCapacity(16);

	this->charContentsCapacity = 0;
	this->charContents = 0;
	this->charContentsChanged = true;
}

void MwString::ResizeCapacity(int newCapacity, bool keepContents)
{
	wchar_t *newContents = new wchar_t[newCapacity + 1];
	int newLength = newCapacity > this->length ? this->length : newCapacity;
	
	if (keepContents)
		if (this->length > 0)
			MwMem::Copy(newContents, this->contents, newLength * sizeof(wchar_t));
	newContents[newLength] = 0;

	if (this->contents != 0)
		delete[] this->contents;

	this->contents = newContents;
	this->length = newLength;
	this->capacity = newCapacity;

	this->charContentsChanged = true;
};

void MwString::EnsureCapacity(int length)
{
	int newCapacity = this->capacity;
	while (length > newCapacity)
	{
		newCapacity *= 2;
	}

	if (newCapacity > this->capacity)
	{
		this->ResizeCapacity(newCapacity, true);
	}
}

void MwString::SetLength(int length)
{
	if (length == this->length)
		return;

	this->EnsureCapacity(length);

	this->length = length;
	this->contents[this->length] = 0;
	this->charContentsChanged = true;
}

int MwString::GetLength()
{
	return this->length;
}

bool MwString::IsEmpty()
{
	return this->length == 0;
}

const wchar_t *MwString::GetContents()
{
	return this->contents;
}

const char *MwString::GetCharContents()
{
	if (this->charContentsChanged)
	{
		if (this->capacity > this->charContentsCapacity)
		{
			if (this->charContents != 0)
				delete[] this->charContents;

			this->charContentsCapacity = this->capacity;
			this->charContents = new char[this->charContentsCapacity + 1];
		}

		for (int i = 0; i < this->length; i++)
			this->charContents[i] = (char)this->contents[i];

		this->charContents[this->length] = 0;

		this->charContentsChanged = false;
	}

	return this->charContents;
}

int MwString::Compare(const MwString &str)
{
	return this->Compare(str.contents);
}

int MwString::Compare(const char *str)
{
	int length = MwString::GetLength(str);
	int extraLength = length - this->length;
	int minLength = extraLength < 0 ? length : this->length;

	for (int i = 0; i < minLength; i++)
	{
		int difference = str[i] - this->contents[i];

		if (difference > 0)
			return -1;
		else if (difference < 0)
			return 1;
	}

	if (extraLength > 0)
		return -1;
	else if (extraLength < 0)
		return 1;

	return 0;
}

int MwString::Compare(const wchar_t *str)
{
	int length = MwString::GetLength(str);
	int extraLength = length - this->length;
	int minLength = extraLength < 0 ? length : this->length;

	for (int i = 0; i < minLength; i++)
	{
		int difference = str[i] - this->contents[i];

		if (difference > 0)
			return -1;
		else if (difference < 0)
			return 1;
	}

	if (extraLength > 0)
		return -1;
	else if (extraLength < 0)
		return 1;

	return 0;
}

bool MwString::Equals(const MwString &str)
{
	return this->Compare(str) == 0;
}

bool MwString::Equals(const char *str)
{
	return this->Compare(str) == 0;
}

bool MwString::Equals(const wchar_t *str)
{
	return this->Compare(str) == 0;
}

void MwString::InsertCharacters(int position, int count)
{
	int oldLength = this->length;
	int tailCharacters = oldLength - position;
	
	this->SetLength(this->length + count);

	if (count > tailCharacters)
	{
		MwMem::Copy(&this->contents[position + count], &this->contents[position], tailCharacters * sizeof(wchar_t));
	}
	else
	{
		void *tailData = new wchar_t[tailCharacters];
		MwMem::Copy(tailData, &this->contents[position], tailCharacters * sizeof(wchar_t));
		MwMem::Copy(&this->contents[position + count], tailData, count * sizeof(wchar_t));
		MwMem::FreeAndNull(&tailData);
	}

	this->charContentsChanged = true;
}

void MwString::CopyCharacters(int offset, const MwString &source, int sourceOffset, int count)
{
	this->CopyCharacters(offset, source.contents, sourceOffset, count);
}

void MwString::CopyCharacters(int offset, const char *source, int sourceOffset, int count)
{
	for (int i = 0; i < count; i++)
		this->contents[offset + i] = source[sourceOffset + i];

	this->charContentsChanged = true;
}

void MwString::CopyCharacters(int offset, const wchar_t *source, int sourceOffset, int count)
{
	MwMem::Copy(&this->contents[offset], &source[sourceOffset], count * sizeof(wchar_t));

	this->charContentsChanged = true;
}

void MwString::FillCharacters(int offset, const char fillChar, int count)
{
	int end = offset + count;
	for (int i = offset; i < end; i++)
		this->contents[i] = fillChar;

	this->charContentsChanged = true;
}

void MwString::FillCharacters(int offset, const wchar_t fillChar, int count)
{
	int end = offset + count;
	for (int i = offset; i < end; i++)
		this->contents[i] = fillChar;

	this->charContentsChanged = true;
}

void MwString::Copy(const MwString &source)
{
	this->Copy(source.contents);
}

void MwString::Copy(const char *source)
{
	int length = MwString::GetLength(source);
	
	this->EnsureCapacity(length);

	int i;
	for (i = 0; i < length; i++)
		this->contents[i] = source[i];

	this->contents[length] = 0;
	this->length = length;

	this->charContentsChanged = true;
}

void MwString::Copy(const wchar_t *source)
{
	int length = MwString::GetLength(source);
	
	this->EnsureCapacity(length);

	MwMem::Copy(this->contents, source, length * sizeof(wchar_t));

	this->contents[length] = 0;
	this->length = length;

	this->charContentsChanged = true;
}

void MwString::Insert(const MwString &source, int position, int count)
{
	this->Insert(source.contents, position);
}

void MwString::Insert(const char *source, int position, int count)
{
	if (position == -1)
		position = this->length;

	if (count == -1)
		count = MwString::GetLength(source);

	this->InsertCharacters(position, count);
	this->CopyCharacters(position, source, 0, count);
}

void MwString::Insert(const wchar_t *source, int position, int count)
{
	if (position == -1)
		position = this->length;

	if (count == -1)
		count = MwString::GetLength(source);

	this->InsertCharacters(position, count);
	this->CopyCharacters(position, source, 0, count);
}

int MwString::IndexOf(const MwString &substr, int start)
{
	return this->IndexOf(substr.contents, start);
}

int MwString::IndexOf(const char *substr, int start)
{
	int substrLength = MwString::GetLength(substr);

	for (int index = start; index <= this->length - substrLength; index++)
	{
		int thisIndex = index;
		int substrIndex = 0;
		while (this->contents[thisIndex] == substr[substrIndex])
		{
			substrIndex++;
			if (substrIndex == substrLength)
				return index;
			thisIndex++;
			if (thisIndex == this->length)
				return -1;
		}
	}

	return -1;
}

int MwString::IndexOf(const wchar_t *substr, int start)
{
	int substrLength = MwString::GetLength(substr);

	for (int index = start; index <= this->length - substrLength; index++)
	{
		int thisIndex = index;
		int substrIndex = 0;
		while (this->contents[thisIndex] == substr[substrIndex])
		{
			substrIndex++;
			if (substrIndex == substrLength)
				return index;
			thisIndex++;
			if (thisIndex == this->length)
				return -1;
		}
	}

	return -1;
}

int MwString::LastIndexOf(const MwString &substr, int start)
{
	return this->LastIndexOf(substr.contents, start);
}

int MwString::LastIndexOf(const char *substr, int start)
{
	if (start == -1)
		start = MwString::GetLength(this->contents) - 1;
	
	int substrLast = MwString::GetLength(substr) - 1;

	for (int index = start; index >= substrLast; index--)
	{
		int thisIndex = index;
		int substrIndex = substrLast;
		while (this->contents[thisIndex] == substr[substrIndex])
		{
			if (substrIndex == 0)
				return index - substrLast;
			if (thisIndex == 0)
				return -1;
			substrIndex--;
			thisIndex--;
		}
	}

	return -1;
}

int MwString::LastIndexOf(const wchar_t *substr, int start)
{
	if (start == -1)
		start = MwString::GetLength(this->contents) - 1;
	
	int substrLast = MwString::GetLength(substr) - 1;

	for (int index = start; index >= substrLast; index--)
	{
		int thisIndex = index;
		int substrIndex = substrLast;
		while (this->contents[thisIndex] == substr[substrIndex])
		{
			if (substrIndex == 0)
				return index;
			if (thisIndex == 0)
				return -1;
			substrIndex--;
			thisIndex--;
		}
	}

	return -1;
}

MwString MwString::SubString(int start, int count)
{
	start = MwMath::Trim(start, 0, this->length);
	count = MwMath::Trim(count, 0, this->length - start);

	MwString result;
	result.SetLength(count);
	MwMem::Copy(result.contents, &this->contents[start], count * sizeof(wchar_t));
	result.contents[count] = 0;

	return MwString(result.contents);
}

MwString MwString::Remove(int start, int count)
{
	start = MwMath::Trim(start, 0, this->length);
	count = MwMath::Trim(count, 0, this->length - start);

	MwString result;
	result.SetLength(this->length - count);
	MwMem::Copy(result.contents, this->contents, start * sizeof(wchar_t));
	MwMem::Copy(&result.contents[start], &this->contents[start + count], (this->length - start - count) * sizeof(wchar_t));
	result.contents[result.length] = 0;

	return MwString(result.contents);
}

MwString MwString::Remove(const MwString &str)
{
	return this->Remove(str.contents);
}

MwString MwString::Remove(const char *str)
{
	return this->Replace(str, "");
}

MwString MwString::Remove(const wchar_t *str)
{
	return this->Replace(str, L"");
}

MwString MwString::Replace(const MwString &str, const MwString &substitute)
{
	return this->Replace(str.contents, substitute.contents);
}

MwString MwString::Replace(const char *str, const char *substitute)
{
	MwString result;

	int strLength = MwString::GetLength(str);
	int srcPos = 0;
	for (;;)
	{
		int pos = this->IndexOf(str, srcPos);

		if (pos == -1)
			pos = this->length;

		if (pos >= srcPos)
		{
			int chunkLength = pos - srcPos;
			result.Insert(&this->contents[srcPos], result.length, chunkLength);
			if (pos != this->length)
				result.Insert(substitute);
		}

		srcPos = pos + strLength;

		if (srcPos >= this->length)
			break;
	}

	return MwString(result);
}

MwString MwString::Replace(const wchar_t *str, const wchar_t *substitute)
{
	MwString result;

	int strLength = MwString::GetLength(str);
	int srcPos = 0;
	for (;;)
	{
		int pos = this->IndexOf(str, srcPos);

		if (pos == -1)
			pos = this->length;

		if (pos >= srcPos)
		{
			int chunkLength = pos - srcPos;
			result.Insert(&this->contents[srcPos], result.length, chunkLength);
			if (pos != this->length)
				result.Insert(substitute);
		}

		srcPos = pos + strLength;

		if (srcPos >= this->length)
			break;
	}

	return MwString(result);
}

MwString MwString::PadLeft(int minLength, const char fillChar)
{
	int padLength = minLength - this->length;
	if (padLength <= 0)
		return MwString(*this);

	MwString result;
	result.SetLength(minLength);

	result.FillCharacters(0, fillChar, padLength);
	result.CopyCharacters(padLength, this->contents, 0, this->length);

	return MwString(result);
}

MwString MwString::PadLeft(int minLength, const wchar_t fillChar)
{
	int padLength = minLength - this->length;
	if (padLength <= 0)
		return MwString(*this);

	MwString result;
	result.SetLength(minLength);

	result.FillCharacters(0, fillChar, padLength);
	result.CopyCharacters(padLength, this->contents, 0, this->length);

	return MwString(result);
}

MwString MwString::PadRight(int minLength, const char fillChar)
{
	int padLength = minLength - this->length;
	if (padLength <= 0)
		return MwString(*this);

	MwString result;
	result.SetLength(minLength);

	result.CopyCharacters(0, this->contents, 0, this->length);
	result.FillCharacters(padLength, fillChar, padLength);

	return MwString(result);
}

MwString MwString::PadRight(int minLength, const wchar_t fillChar)
{
	int padLength = minLength - this->length;
	if (padLength <= 0)
		return MwString(*this);

	MwString result;
	result.SetLength(minLength);

	result.CopyCharacters(0, this->contents, 0, this->length);
	result.FillCharacters(padLength, fillChar, padLength);

	return MwString(result);
}

bool MwString::StartsWith(const MwString &str)
{
	return this->StartsWith(str.contents);
}

bool MwString::StartsWith(const char *str)
{
	int index = 0;

	while ((str[index] != 0) && (index < this->length))
	{
		if (str[index] != this->contents[index])
			return false;

		index++;
	}

	return str[index] == 0;
}

bool MwString::StartsWith(const wchar_t *str)
{
	int index = 0;

	while ((str[index] != 0) && (index < this->length))
	{
		if (str[index] != this->contents[index])
			return false;

		index++;
	}

	return str[index] == 0;
}

bool MwString::StartsWith(const char chr)
{
	if (this->length == 0)
		return false;

	return this->contents[0] == chr;
}

bool MwString::StartsWith(const wchar_t chr)
{
	if (this->length == 0)
		return false;

	return this->contents[0] == chr;
}


bool MwString::EndsWith(const MwString &str)
{
	return this->EndsWith(str.contents);
}

bool MwString::EndsWith(const char *str)
{
	int thisIndex = this->length - MwString::GetLength(str);
	int index = 0;

	while ((str[index] != 0) && (thisIndex < this->length))
	{
		if (str[index] != this->contents[thisIndex])
			return false;

		index++;
		thisIndex++;
	}

	return str[index] == 0;
}

bool MwString::EndsWith(const wchar_t *str)
{
	int thisIndex = this->length - MwString::GetLength(str);
	int index = 0;

	while ((str[index] != 0) && (thisIndex < this->length))
	{
		if (str[index] != this->contents[thisIndex])
			return false;

		index++;
		thisIndex++;
	}

	return str[index] == 0;
}

bool MwString::EndsWith(const char chr)
{
	if (this->length == 0)
		return false;

	return this->contents[this->length - 1] == chr;
}

bool MwString::EndsWith(const wchar_t chr)
{
	if (this->length == 0)
		return false;

	return this->contents[this->length - 1] == chr;
}


MwString MwString::Trim(const char chr, bool left, bool right)
{
	int leftIndex = 0;
	if (left)
	{
		while (this->contents[leftIndex] == chr)
			leftIndex++;
	}

	int rightIndex = this->length - 1;
	if (right)
	{
		while (this->contents[rightIndex] == chr)
			rightIndex--;
	}

	MwString result(*this);
	return MwString(result.SubString(leftIndex, rightIndex - leftIndex + 1));
}

MwString MwString::Trim(const wchar_t chr, bool left, bool right)
{
	int leftIndex = 0;
	if (left)
	{
		while (this->contents[leftIndex] == chr)
			leftIndex++;
	}

	int rightIndex = this->length - 1;
	if (right)
	{
		while (this->contents[rightIndex] == chr)
			rightIndex--;
	}

	MwString result(*this);
	return MwString(result.SubString(leftIndex, rightIndex - leftIndex + 1));
}


bool MwString::ToInt(int &value, int radix)
{
	if (this->length == 0)
		return false;

	wchar_t *end;
	value = MwString::ToInt(this->contents, &end, radix);

	return end == &this->contents[this->length];
}

bool MwString::ToUInt(unsigned int &value, int radix)
{
	if (this->length == 0)
		return false;

	wchar_t *end;
	value = MwString::ToUInt(this->contents, &end, radix);

	return end == &this->contents[this->length];
}

bool MwString::ToFloat(float &value)
{
	if (this->length == 0)
		return false;

	wchar_t *end;
	value = (float)MwString::ToDouble(this->contents, &end);

	return end == &this->contents[this->length];
}

bool MwString::ToDouble(double &value)
{
	if (this->length == 0)
		return false;

	wchar_t *end;
	value = MwString::ToDouble(this->contents, &end);

	return end == &this->contents[this->length];
}

MwString MwString::ToLower()
{
	MwString result = *this;
	_wcslwr_s(result.contents, result.length + 1);
	return MwString(result);
}

MwString MwString::ToUpper()
{
	MwString result = *this;
	_wcsupr_s(result.contents, result.length + 1);
	return MwString(result);
}

// Static Methods

int MwString::GetLength(const char *str)
{
	if (str == 0)
		return -1;

	for (int result = 0; ; result++)
		if (str[result] == 0)
			return result;
}

int MwString::GetLength(const wchar_t *str)
{
	if (str == 0)
		return -1;

	for (int result = 0; ; result++)
		if (str[result] == 0)
			return result;
}

char *MwString::CopyNew(const char *source)
{
	int length = MwString::GetLength(source);

	char *newCopy = new char[length + 1];
	MwMem::Copy(newCopy, source, length + 1);

	return newCopy;
}

wchar_t *MwString::CopyNew(const wchar_t *source)
{
	int length = MwString::GetLength(source);

	wchar_t *newCopy = new wchar_t[length + 1];
	MwMem::Copy(newCopy, source, (length + 1) * sizeof(wchar_t));

	return newCopy;
}

void MwString::Dispose(char **str)
{
	if (*str == 0)
		return;

	delete[] *str;
	*str = 0;
}

void MwString::Dispose(wchar_t **str)
{
	if (*str == 0)
		return;

	delete[] *str;
	*str = 0;
}

MwString MwString::ToBase64()
{
	return MwString::ToBase64(this->GetCharContents(), this->length);
}

MwString MwString::FromBase64()
{
	char *data;
	unsigned int length;
	if (MwString::FromBase64(*this, (void**)&data, length))
	{
		MwString result(data, length);
		delete[] data;

		return MwString(result);
	}

	return MwString();
}

MwString MwString::ToBase64(const void *data, unsigned int dataSize)
{
	int actualLength = ((dataSize * 8) + 5) / 6;
	int fullLength = ((actualLength + 3) / 4) * 4;
	
	MwString result;
	result.SetLength(fullLength);

	int charIndex = 0;	
	for (int i = 0; i < actualLength; i++)
	{
		MwMem::CopyBits(data, i * 6, &charIndex, 2, 6);
		result[i] = base64Map[charIndex];
	}

	for (int i = actualLength; i < fullLength; i++)
		result[i] = L'=';
	
	return MwString(result);
}

bool MwString::FromBase64(MwString &base64String, void **data, unsigned int &dataSize)
{
	int actualLength = base64String.length;
	while ((actualLength >= 0) && ((base64String.contents[actualLength - 1] == L'=')))
			actualLength--;

	dataSize = (actualLength * 6) / 8;
	*data = new char[dataSize + 1];

	for (int i = 0; i < actualLength; i++)
	{
		int charIndex = base64Map.IndexOf(MwString(base64String.contents[i]));
		if (charIndex == -1)
		{
			delete[] (*data);
			return false;
		}
		MwMem::CopyBits(&charIndex, 2, *data, i * 6, 6);
	}

	((char*)(*data))[dataSize] = 0;

	return true;
}

int MwString::ToInt(char *str, char **end, int radix)
{
	*end = str;
	return strtol(str, end, radix);
}

int MwString::ToInt(wchar_t *str, wchar_t **end, int radix)
{
	*end = str;
	return wcstol(str, end, radix);
}

unsigned int MwString::ToUInt(char *str, char **end, int radix)
{
	*end = str;
	return strtoul(str, end, radix);
}

unsigned int MwString::ToUInt(wchar_t *str, wchar_t **end, int radix)
{
	*end = str;
	return wcstoul(str, end, radix);
}

double MwString::ToDouble(char *str, char **end)
{
	*end = str;
	return strtod(str, end);
}

double MwString::ToDouble(wchar_t *str, wchar_t **end)
{
	*end = str;
	return wcstod(str, end);
}

//MwString MwString::Format(const wchar_t *formatString, ...)
//{
//}

