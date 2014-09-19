#pragma once

#include "..\..\MwGlobals.h"

class MWDLLCLASS MwPCMFormat
{
public:
	int sampleSizeInBytes, frequency, channelsCount;

	MwPCMFormat(void);
	MwPCMFormat(int sampleSizeInBytes, int frequency, int channelsCount);
	~MwPCMFormat();
};