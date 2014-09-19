#pragma once

#include "..\Tools\MwString.h"

struct MwSerializationParameters
{
	// The root dir for the serialization. Used as a base for relative paths. Can be used when loading from a stream, when fullSourceName is not available
	MwString rootDir;
	// A friendly name of the serialization source. Used when such is needed, for example to give names to resources
	MwString friendlyName;
	// The full name of the source. Generally, the path with file name.
	MwString fullSourceName;
};