#pragma once

#include "..\..\MwGlobals.h"

#include "MwBaseStream.h"

class MWDLLCLASS MwSubStream :
	public MwBaseStream
{
public:
	MwBaseStream *mainStream;

	long long offset;
	bool writeBeyondLength;

	MwSubStream(MwBaseStream &mainStream, long long length = -1, long long offset = -1, bool writeBeyondLength = true);
	~MwSubStream(void);

	virtual long long ReadData(void *data, long long size) = 0;
	virtual long long WriteData(const void *data, long long size) = 0;
};

