#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwStack.h"
#include "..\..\..\Tools\Streams\MwBaseStream.h"

class MWDLLCLASS MwHierarchyStreamWriter
{
private:
    MwStack<long long> chunkStack;

public:
    MwBaseStream *stream;

	MwHierarchyStreamWriter(MwBaseStream &stream);
	~MwHierarchyStreamWriter(void);
        
	void BeginChunk(unsigned int chunkId);
	void EndChunk();
};

