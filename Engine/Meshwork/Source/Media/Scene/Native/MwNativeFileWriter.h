#pragma once

#include "..\..\..\MwGlobals.h"

#include "..\..\..\Tools\MwString.h"
#include "..\..\..\Tools\Streams\MwBaseStream.h"

class Meshwork;

class MWDLLCLASS MwNativeFileWriter
{
public:
	Meshwork *context;

	MwNativeFileWriter(Meshwork *context);
	~MwNativeFileWriter(void);

	void Write(MwBaseStream &destination);
};

