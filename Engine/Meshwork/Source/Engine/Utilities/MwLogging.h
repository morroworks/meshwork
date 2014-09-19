#pragma once

#include "..\..\Tools\MwString.h"

class MWDLLCLASS MwLogging
{
public:
	static const int MessageType_Info			= 0;
	static const int MessageType_Warning		= 1;
	static const int MessageType_Error			= 2;
	static const int MessageType_CriticalError	= 3;

	MwLogging(void);
	~MwLogging(void);

	void AddMessage(const MwString &message, int messageType);
};

