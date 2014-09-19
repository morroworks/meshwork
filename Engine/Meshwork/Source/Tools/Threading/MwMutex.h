#pragma once

#include "..\..\MwGlobals.h"

class MWDLLCLASS MwMutex
{
private:
	void *handle;

public:

	MwMutex(void);
	virtual ~MwMutex(void);

	virtual bool Lock();
	virtual void Unlock();
};

