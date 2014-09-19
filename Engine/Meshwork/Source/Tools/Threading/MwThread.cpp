//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwThread.h"

#include <windows.h>

DWORD WINAPI ExecuteThread(LPVOID lpParam)
{
	MwThread *instance = (MwThread*)lpParam;

	int result = 0;
	
	while (!instance->terminated)
	{
		if (WaitForSingleObject(*(HANDLE*)instance->signalEvent, INFINITE) == WAIT_OBJECT_0)
		{
			if (instance->running)
			{
				// Run has been requested
				result = instance->Execute();

				ResetEvent(*(HANDLE*)instance->signalEvent);

				instance->running = false;

				instance->terminated = !instance->reusable;
			}
			else
			{
				// Finish has been requested
				instance->terminated = true;
				result = 0;
			}
		}
		else
		{
			// Timeout or other erroneous case
			instance->terminated = true;
			result = 1;
		}
	}
	
	return result;
}

int MwThread::Initialize(bool start, bool reusable)
{
	this->signalEvent = new HANDLE();
	*(HANDLE*)this->signalEvent = CreateEvent(NULL, TRUE, start ? TRUE : FALSE, NULL);

	this->reusable = reusable;

	this->handle = new HANDLE;
	this->id = new DWORD;
		
	this->reusable = reusable;
	this->running = start;
	this->terminated = false;

	*(HANDLE*)this->handle = CreateThread(
		NULL,										// default security attributes
		0,											// default stack size
		(LPTHREAD_START_ROUTINE) ExecuteThread,		// funciton
		this,										// parameter
		NULL,										// default creation flags
		(DWORD*)this->id);							// receive thread identifier

    if(*(HANDLE*)this->handle == NULL)
		return GetLastError();
	else
		return 0;
}

MwThread::MwThread(bool start, bool reusable)
{
	this->Initialize(start, reusable);

	this->function = 0;
}

MwThread::MwThread(ThreadExecuteFunction function, void *functionParameter, bool start, bool reusable)
{
	this->function = function;
	this->finctionParameter = functionParameter;

	this->Initialize(start, reusable);
}

MwThread::~MwThread(void)
{
	this->Wait();
    
	CloseHandle(*(HANDLE*)this->handle);

	CloseHandle(*(HANDLE*)this->signalEvent);
	delete this->signalEvent;

	delete this->handle;
	delete this->id;
}

void MwThread::Run()
{
	this->running = true;
	SetEvent(*(HANDLE*)this->signalEvent);
}

void MwThread::Finish()
{
	this->running = false;
	SetEvent(*(HANDLE*)this->signalEvent);
}

void MwThread::WaitTask()
{
	while (this->running)
		Sleep(0);
}

void MwThread::Wait()
{
	while (!this->terminated)
		Sleep(0);
}

//void MwThread::Suspend()
//{
//	if (this->suspended)
//		return;
//
//	this->suspended = true;
//
//	SuspendThread(*(HANDLE*)this->handle);
//}
//
//void MwThread::Resume()
//{
//	if (!this->suspended)
//		return;
//
//	this->suspended = false;
//
//	ResumeThread(*(HANDLE*)this->handle);
//}

//void MwThread::Terminate()
//{
//	if (this->terminated)
//		return;
//
//	TerminateThread(*(HANDLE*)this->handle, -1);
//	this->terminated = true;
//}

int MwThread::Execute()
{
	if (this->function == 0)
		return 0;
	
	return this->function(this->finctionParameter);
}
