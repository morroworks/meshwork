#pragma once

#include "..\..\..\..\MwGlobals.h"

class Soras;

typedef bool (*SrCullMode)(Soras *soras);

class MWDLLCLASS SrCullModes
{
public:
    static bool None(Soras *soras);
    static bool CounterClockWise(Soras *soras);
	static bool ClockWise(Soras *soras);
};