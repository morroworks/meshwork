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

#include "MwThreadsPool.h"

#include "..\OS\MwOSUtils.h"

#include <windows.h>

MwThreadsPool::MwThreadsPool(int numThreads)
{
	for (int i = 0; i < numThreads; i++)
	{
		MwThreadsPoolThread *thread = new MwThreadsPoolThread(this);

		this->threads.Add(thread);
		//this->freeThreads.Add(thread);
	}

	this->nextTaskId = 0;

}


MwThreadsPool::~MwThreadsPool(void)
{
	for (int i = 0; i < this->threads.count; i++)
	{
		this->threads[i]->Finish();
	}

	for (int i = 0; i < this->threads.count; i++)
	{
		delete this->threads[i];
	}
}

int MwThreadsPool::ResumeSuspendedThread()
{
	this->synchronization.Lock();

	for (int i = 0; i < this->threads.count; i++)
	{
		if (!this->threads[i]->running)
		{
			this->threads[i]->Run();
			this->synchronization.Unlock();
			return i;
		}
	}

	this->synchronization.Unlock();

	return -1;
}

bool MwThreadsPool::PullQueuedTask(ThreadsPoolTask &task)
{
	this->synchronization.Lock();

	bool result = this->queuedTasks.count != 0;

	if (result)
	{
		task = this->queuedTasks[0];
		this->queuedTasks.RemoveAt(0);
	}

	this->synchronization.Unlock();

	return result;
}

int MwThreadsPool::QueueTask(ThreadExecuteFunction function, void *functionParameter)
{
	this->synchronization.Lock();

	int taskId = this->nextTaskId++;

	this->queuedTasks.Add(ThreadsPoolTask(function, functionParameter, taskId));

	this->ResumeSuspendedThread();

	this->synchronization.Unlock();

	return taskId;
}

bool MwThreadsPool::Pending(int taskId)
{
	this->synchronization.Lock();

	bool result = false;

	for (int i = 0; i < this->queuedTasks.count; i++)
	{
		if (this->queuedTasks[i].id == taskId)
		{
			result = true;
			break;
		}
	}

	this->synchronization.Unlock();

	return result;
}

bool MwThreadsPool::Executing(int taskId)
{
	this->synchronization.Lock();

	bool result = false;

	for (int i = 0; i < this->threads.count; i++)
	{
		if ((this->threads[i]->task.id == taskId) && this->threads[i]->running)
		{
			result = true;
			break;
		}
	}

	this->synchronization.Unlock();

	return result;
}

bool MwThreadsPool::Finished(int taskId)
{
	return !this->Executing(taskId) && !this->Pending(taskId);
}


bool MwThreadsPool::Idle()
{
	if (this->queuedTasks.count != 0)
		return false;

	bool result = true;

	this->synchronization.Lock();

	for (int i = 0; i < this->threads.count; i++)
	{
		if (this->threads[i]->running)
		{
			result = false;
			break;
		}
	}

	this->synchronization.Unlock();

	return result;
}

void MwThreadsPool::Wait(int taskId)
{
	while (!this->Finished(taskId))
	{
		MwOSUtils::SleepX(0);
	}
}

void MwThreadsPool::WaitAll()
{
	while (!this->Idle())
	{
		MwOSUtils::SleepX(0);
	}
}
