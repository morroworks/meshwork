#pragma once

#include "..\..\MwGlobals.h"

#include "MwThread.h"
#include "MwMutex.h"

class MWDLLCLASS ThreadsPoolTask
{
public:
	ThreadExecuteFunction function;
	void *functionParameter;
	int id;

	ThreadsPoolTask(void);
	ThreadsPoolTask(ThreadExecuteFunction function, void *functionParameter, int id);
};

class MwThreadsPool;

class MWDLLCLASS MwThreadsPoolThread :
	public MwThread
{
public:
	MwThreadsPool *pool;
	ThreadsPoolTask task;

	MwThreadsPoolThread(MwThreadsPool *pool);
	virtual ~MwThreadsPoolThread(void);

	virtual int Execute();
};

