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

#include "MwTimer.h"

#include "..\..\Tools\OS\MwOSUtils.h"

MwTimer::MwTimer(void)
{
	this->Reset();
}


MwTimer::~MwTimer(void)
{
}

void MwTimer::Reset()
{
	this->time = 0.0f;
	this->actualTime = 0.0f;
	this->elapsedTime = 0.0f;
	this->elapsedActualTime = 0.0f;
	this->ticksPerSecond = 0.0f;
	this->ticksLastSecond = 0.0f;
	this->speed = 1.0f;
	this->ticksTotal = 0;
	
	this->lastSecondTicks = 0;
    this->lastSecondTime = 0.0f;

	this->tickOutTime = 0.0;

	this->timeAnchor = MwTimer::GetAnchor();
}

void MwTimer::Tick()
{
	this->actualTime = MwTimer::GetAnchorTime(this->timeAnchor);
	this->time = this->actualTime * this->speed + this->tickOutTime;
    this->elapsedTime += this->time;
	this->elapsedActualTime += this->actualTime;
    this->ticksPerSecond = 1.0f / this->actualTime;
	this->ticksTotal++;
	this->lastSecondTicks++;
    this->lastSecondTime += this->actualTime;
    if (this->lastSecondTime >= 1.0f)
    {
        this->ticksLastSecond = (float)this->lastSecondTicks / this->lastSecondTime;
        this->lastSecondTicks = 0;
        this->lastSecondTime = 0.0f;
    }
        
	this->tickOutTime = 0.0;

	this->timeAnchor = MwTimer::GetAnchor();
}

void MwTimer::TickOut(float time)
{
	this->tickOutTime = time;
}

long long MwTimer::GetFrequency()
{
	return MwOSUtils::GetPerformanceCounterFrequency();
}

long long MwTimer::GetAnchor()
{
	return MwOSUtils::GetPerformanceCounter();
}

float MwTimer::GetAnchorTime(long long anchor)
{
	return (float)(MwTimer::GetAnchor() - anchor) / (float)MwTimer::GetFrequency();
}
