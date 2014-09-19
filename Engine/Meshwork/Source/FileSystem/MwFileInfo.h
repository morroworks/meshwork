#pragma once

#include "..\MwGlobals.h"

#include "..\Tools\MwString.h"

struct MwFileInfo
{
	MwString fileName;
	bool isDirectory;
	unsigned long long size;
};