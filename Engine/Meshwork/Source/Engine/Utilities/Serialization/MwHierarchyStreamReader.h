#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwStack.h"
#include "..\..\..\Tools\Streams\MwBaseStream.h"

class MWDLLCLASS MwHierarchyStreamReader
{
public:
    MwStack<long long> chunkStack;

	MwBaseStream *stream;

	unsigned int chunkId;
	long long chunkSize;

    MwHierarchyStreamReader(MwBaseStream &stream);
	~MwHierarchyStreamReader(void);

    bool ReadChunkHeader();
    void SkipChunk();
};

