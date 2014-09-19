#pragma once

#include "..\..\MwGlobals.h"

#include <exception>

#include "..\MwString.h"

class MWDLLCLASS StreamException
	: public std::exception
{
public:
	char *message;

	StreamException::StreamException(const char *message);
	StreamException::~StreamException(void);

	virtual const char *what() const throw();
};

enum StreamSeekMode
{
	StreamSeekMode_FromBeginning,
	StreamSeekMode_Relative,
	StreamSeekMode_FromEnd
};


class MWDLLCLASS MwBaseStream
{
public:
	MwBaseStream(void);
	virtual ~MwBaseStream(void);

	long long position, length;

	virtual long long ReadData(void *data, long long size) = 0;
	virtual long long WriteData(const void *data, long long size) = 0;

	virtual bool Seek(long long offset, StreamSeekMode seekType = StreamSeekMode_FromBeginning);

	//virtual long long ReadStreamData(MwBaseStream &stream, long long size = -1, int maxBufferSize = 65536) { stream.WriteStreamData(this, size, maxBufferSize); };
	virtual long long WriteStreamData(MwBaseStream &stream, long long size = -1, int maxBufferSize = 65536);

	virtual bool ReadBool();
	virtual void WriteBool(bool value);

	virtual char ReadInt8();
	virtual void WriteInt8(char value);
	virtual short ReadInt16();
	virtual void WriteInt16(short value);
	virtual int ReadInt32();
	virtual void WriteInt32(int value);
	virtual long long ReadInt64();
	virtual void WriteInt64(long long value);
	virtual int Read7BitEncodedInt32();
	virtual void Write7BitEncodedInt32(int value);
	
	virtual unsigned char ReadUInt8();
	virtual void WriteUInt8(unsigned char value);
	virtual unsigned short ReadUInt16();
	virtual void WriteUInt16(unsigned short value);
	virtual unsigned int ReadUInt32();
	virtual void WriteUInt32(unsigned int value);
	virtual unsigned long long ReadUInt64();
	virtual void WriteUInt64(unsigned long long value);

	virtual float ReadFloat();
	virtual void WriteFloat(float value);
	virtual double ReadDouble();
	virtual void WriteDouble(double value);

	virtual MwString ReadString();
	virtual void WriteString(MwString &value);

	virtual MwString ReadText();
	virtual void WriteText(MwString text);
	virtual MwString ReadUText();
	virtual void WriteUText(MwString text);
	virtual MwString ReadTextLine();
	virtual void WriteTextLine(MwString text);
	virtual MwString ReadUTextLine();
	virtual void WriteUTextLine(MwString text);
	virtual MwString ReadTextFull();
	virtual MwString ReadUTextFull();
};

