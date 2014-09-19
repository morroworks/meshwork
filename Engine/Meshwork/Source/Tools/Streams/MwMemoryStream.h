#pragma once

#include "..\..\MwGlobals.h"

#include "MwBaseStream.h"

enum StreamWriteMode
{
	StreamWriteMode_Overwrite,
	StreamWriteMode_Insert
};

class MWDLLCLASS MwMemoryStream :
	public MwBaseStream
{
public:
	StreamWriteMode writeMode;

	void *data;

	long long capacity;

	MwMemoryStream(int initialCapacity = 2048);
	MwMemoryStream(void *data, int size);
	~MwMemoryStream(void);

	virtual long long ReadData(void *data, long long size);
	virtual long long WriteData(const void *data, long long size);

	virtual void SetWriteMode(StreamWriteMode writeMode);

	void MwMemoryStream::Resize(long long newCapacity);
	void *GetDataPointer(long long offset);

};

