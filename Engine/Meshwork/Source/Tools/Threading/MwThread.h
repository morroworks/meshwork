#pragma once

#include "..\..\MwGlobals.h"


typedef int (*ThreadExecuteFunction) (void *parameter);

class MWDLLCLASS MwThread
{
private:
	void *handle, *id;

	int Initialize(bool start, bool reusable);

public:
	void *signalEvent;

	bool reusable,		// Indicates that the thread is reusable and can be re-run multiple times
		 running,		// Indicates that the thread is running its task
		 terminated;	// Indicates that the thread has finished doing its work

	ThreadExecuteFunction function;
	void *finctionParameter;
		
	MwThread(bool start = true, bool reusable = false);
	MwThread(ThreadExecuteFunction function, void *functionParameter, bool start = true, bool reusable = false);
	virtual ~MwThread(void);

	// Runs the thread's task, calling the Execute() method
	void Run();
	// Signals the thread to terminate after finishing its task
	void Finish();
	// Waits until the thread has finished its task;
	void WaitTask();
	// Waits until the thread has terminated;
	void Wait();

	virtual int Execute();
};