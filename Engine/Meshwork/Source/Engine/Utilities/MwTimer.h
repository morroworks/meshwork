#pragma once

#include "..\..\MwGlobals.h"

class MWDLLCLASS MwTimer
{
private:
	long long timeAnchor;
	float lastSecondTime;
    int lastSecondTicks;
	float tickOutTime;

public:
    float time, actualTime, elapsedTime, elapsedActualTime, ticksPerSecond, ticksLastSecond, speed;
	unsigned long long ticksTotal;

	MwTimer(void);
	~MwTimer(void);

	void Reset();
	void Tick();
	void TickOut(float time);

	static long long MwTimer::GetFrequency();
	static long long MwTimer::GetAnchor();
	static float MwTimer::GetAnchorTime(long long anchor);
};