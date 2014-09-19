#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Engine\Utilities\Serialization\MwHierarchyStreamReader.h"

#include "..\..\..\Tools\MwDictionary.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwDictionary<long long, long long>;

class Meshwork;

class MWDLLCLASS MwNativeFileReader
{
private:
	MwDictionary<long long, long long> idMap;

	long long GetMappedResourceId(long long originalId);
	void LinkResources();

public:
	Meshwork *context;

	MwNativeFileReader(Meshwork *context);
	~MwNativeFileReader(void);

	bool Read(MwBaseStream &source);
};

