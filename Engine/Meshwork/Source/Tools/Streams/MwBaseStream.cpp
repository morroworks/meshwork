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

#include "MwBaseStream.h"

#include "..\MwMath.h"
#include "..\MwMem.h"

StreamException::StreamException(const char *message)
{
	this->message = MwString::CopyNew(message);
}

StreamException::~StreamException(void)
{
	MwString::Dispose(&this->message);
}

const char *StreamException::what() const throw()
{
	return this->message;
}



MwBaseStream::MwBaseStream(void)
{
	this->position = 0;
	this->length = 0;
}

MwBaseStream::~MwBaseStream(void)
{
}

bool MwBaseStream::Seek(long long offset, StreamSeekMode seekType)
{
	long long newPosition = seekType == StreamSeekMode_FromBeginning ? offset : seekType == StreamSeekMode_Relative ? this->position + offset : seekType == StreamSeekMode_FromEnd ? this->length - offset : -1;

	if ((newPosition >= 0) && (newPosition <= this->length))
	{
		this->position = newPosition;
		return true;
	}

	return false;
}

long long MwBaseStream::WriteStreamData(MwBaseStream &stream, long long size, int maxBufferSize)
{
	if (size == -1)
		size = stream.length - stream.position;

	long long chunkSize = MwMath::Min(size, (long long)maxBufferSize);
	void *dataChunk = MwMem::Get((int)chunkSize);
	
	long long bytesToWrite = size;
	while (bytesToWrite > 0)
	{
		long long bytesToRead = MwMath::Min(bytesToWrite, chunkSize);
		long long bytesRead = stream.ReadData(dataChunk, bytesToRead);
		long long bytesWritten = this->WriteData(dataChunk, bytesRead);

		bytesToWrite -= bytesWritten;

		if (bytesToRead != bytesWritten)
			break;
	}
	
	MwMem::FreeAndNull(&dataChunk);

	return size - bytesToWrite;
}

bool MwBaseStream::ReadBool()
{
	bool result;
	this->ReadData(&result, 1);
	return result;
}

void MwBaseStream::WriteBool(bool value)
{
	this->WriteData(&value, 1);
}


char MwBaseStream::ReadInt8()
{
	char result;
	this->ReadData(&result, 1);
	return result;
}

void MwBaseStream::WriteInt8(char value)
{
	this->WriteData(&value, 1);
}

short MwBaseStream::ReadInt16()
{
	short result;
	this->ReadData(&result, 2);
	return result;
}

void MwBaseStream::WriteInt16(short value)
{
	this->WriteData(&value, 2);
}

int MwBaseStream::ReadInt32()
{
	int result;
	this->ReadData(&result, 4);
	return result;
}

void MwBaseStream::WriteInt32(int value)
{
	this->WriteData(&value, 4);
}

long long MwBaseStream::ReadInt64()
{
	long long result;
	this->ReadData(&result, 8);
	return result;
}

void MwBaseStream::WriteInt64(long long value)
{
	this->WriteData(&value, 8);
}


int MwBaseStream::Read7BitEncodedInt32()
{
	int result = 0;
	char bits;
	do
	{
		this->ReadData(&bits, 1);
		result = (result << 7) | (bits & 0x7f);
	} 
	while ((bits & (1 << 7)) != 0);
		
	return result;
}

void MwBaseStream::Write7BitEncodedInt32(int value)
{
	int writeValue = 0, writeBytes = 0;
 
	for (;;)
	{
		writeValue = (writeValue << 8) | (value & 0x7f);
		value = value >> 7;
		writeBytes++;

		if (value != 0)
			writeValue |= 0x80;
		else
			break;
	}

	this->WriteData(&writeValue, writeBytes);
}

unsigned char MwBaseStream::ReadUInt8()
{
	unsigned char result;
	this->ReadData(&result, 1);
	return result;
}

void MwBaseStream::WriteUInt8(unsigned char value)
{
	this->WriteData(&value, 1);
}

unsigned short MwBaseStream::ReadUInt16()
{
	unsigned short result;
	this->ReadData(&result, 2);
	return result;
}

void MwBaseStream::WriteUInt16(unsigned short value)
{
	this->WriteData(&value, 2);
}

unsigned int MwBaseStream::ReadUInt32()
{
	unsigned int result;
	this->ReadData(&result, 4);
	return result;
}

void MwBaseStream::WriteUInt32(unsigned int value)
{
	this->WriteData(&value, 4);
}

unsigned long long MwBaseStream::ReadUInt64()
{
	unsigned long long result;
	this->ReadData(&result, 8);
	return result;
}

void MwBaseStream::WriteUInt64(unsigned long long value)
{
	this->WriteData(&value, 8);
}


float MwBaseStream::ReadFloat()
{
	float result;
	this->ReadData(&result, 4);
	return result;
}

void MwBaseStream::WriteFloat(float value)
{
	this->WriteData(&value, 4);
}

double MwBaseStream::ReadDouble()
{
	double result;
	this->ReadData(&result, 8);
	return result;
}

void MwBaseStream::WriteDouble(double value)
{
	this->WriteData(&value, 8);
}


MwString MwBaseStream::ReadString()
{
	MwString result;
	result.SetLength(this->Read7BitEncodedInt32());
	this->ReadData(result.contents, result.length * 2);

	return MwString(result);
}

void MwBaseStream::WriteString(MwString &value)
{
	this->Write7BitEncodedInt32(value.length);
	this->WriteData(value.contents, value.length * 2);
}

MwString MwBaseStream::ReadText()
{
	MwString result;
	while (this->position < this->length)
	{
		char c = this->ReadUInt8();
		if ((c != ' ') && (c != '\t') && (c != '\r') && (c != '\n'))
			result += c;
		else
			if (result.length > 0)
				break;
	}

	return MwString(result);
}

void MwBaseStream::WriteText(MwString text)
{
	this->WriteData(text.GetCharContents(), text.length);
}

MwString MwBaseStream::ReadUText()
{
	MwString result;
	while (this->position < this->length)
	{
		wchar_t c = this->ReadUInt16();
		if ((c != ' ') && (c != '\t') && (c != '\r') && (c != '\n'))
			result += c;
		else
			if (result.length > 0)
				break;
	}

	return MwString(result);
}

void MwBaseStream::WriteUText(MwString text)
{
	this->WriteData(text.contents, text.length * 2);
}

MwString MwBaseStream::ReadTextLine()
{
	MwString result;
	while (this->position < this->length)
	{
		char c = this->ReadUInt8();
		if ((c != '\r') && (c != '\n'))
			result += c;
		else
			if (result.length > 0)
				break;
	}

	return MwString(result);
}

void MwBaseStream::WriteTextLine(MwString text)
{
	this->WriteData(text.GetCharContents(), text.length);
	this->WriteUInt8('\r');
	this->WriteUInt8('\n');
}

MwString MwBaseStream::ReadUTextLine()
{
	MwString result;
	while (this->position < this->length)
	{
		wchar_t c = this->ReadUInt8();
		if ((c != '\r') && (c != '\n'))
			result += c;
		else
			if (result.length > 0)
				break;
	}

	return MwString(result);
}

void MwBaseStream::WriteUTextLine(MwString text)
{
	this->WriteData(text.contents, text.length * 2);
	this->WriteUInt16('\r');
	this->WriteUInt16('\n');
}

MwString MwBaseStream::ReadTextFull()
{
	int textLength = (int)(this->length - this->position);
	char *text = new char[textLength];
	this->ReadData(text, textLength);

	MwString result(text, textLength);
	delete[] text;

	return MwString(result);
}

MwString MwBaseStream::ReadUTextFull()
{
	int textLength = (int)((this->length - this->position) / 2);

	MwString result;
	result.SetLength(textLength);
	this->ReadData(result.contents, textLength * 2);

	return MwString(result);
}
