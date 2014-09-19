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

#include "MwThreadsPoolThread.h"

#include "MwThreadsPool.h"


ThreadsPoolTask::ThreadsPoolTask(void)
{
}

ThreadsPoolTask::ThreadsPoolTask(ThreadExecuteFunction function, void *functionParameter, int id)
{
	this->function = function;
	this->functionParameter = functionParameter;
	this->id = id;
}

MwThreadsPoolThread::MwThreadsPoolThread(MwThreadsPool *pool)
	: MwThread(false, true)
{
	this->pool = pool;
}


MwThreadsPoolThread::~MwThreadsPoolThread(void)
{
}

int MwThreadsPoolThread::Execute()
{
	while (this->pool->PullQueuedTask(this->task))
	{
		this->running = true;
		this->task.function(this->task.functionParameter);
	}

	return 0;
}