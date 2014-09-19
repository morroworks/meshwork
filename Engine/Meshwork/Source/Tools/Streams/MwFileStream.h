#pragma once

#include "..\..\MwGlobals.h"

#include "MwBaseStream.h"

#include "..\MwString.h"

enum FileStreamAccessMode
{
	FileStreamAccessMode_Read,
	FileStreamAccessMode_Write,
	FileStreamAccessMode_ReadWrite
};

class MWDLLCLASS MwFileStream :
	public MwBaseStream
{
private:
	void *fileStream_fstream;

public:
	MwFileStream(const MwString &fileName, FileStreamAccessMode accessMode);
	~MwFileStream(void);

	virtual long long ReadData(void *data, long long size);
	virtual long long WriteData(const void *data, long long size);

	virtual bool Seek(long long offset, StreamSeekMode seekType = StreamSeekMode_FromBeginning);
};