#pragma once

#include "..\MwGlobals.h"

class MWDLLCLASS MwIntegralQuotientDistribution
{
private:
	int integralQuotient, integralModulus ,integralError;

public:
	int dividend, divisor;

	MwIntegralQuotientDistribution(void);
	MwIntegralQuotientDistribution(int dividend, int divisor);
	~MwIntegralQuotientDistribution(void);

	void Setup(int dividend, int divisor);
	int PullSequential();
};

