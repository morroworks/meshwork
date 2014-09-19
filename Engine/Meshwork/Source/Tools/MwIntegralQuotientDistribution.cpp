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

#include "MwIntegralQuotientDistribution.h"


// Represents a dithered integral distribution. Can be used for tasks of dispersing the error of integral division among the quotiens, such as Bresenham's line algorithm
MwIntegralQuotientDistribution::MwIntegralQuotientDistribution(void)
{
}

MwIntegralQuotientDistribution::MwIntegralQuotientDistribution(int dividend, int divisor)
{
	this->Setup(dividend, divisor);
}


MwIntegralQuotientDistribution::~MwIntegralQuotientDistribution(void)
{
}

void MwIntegralQuotientDistribution::Setup(int dividend, int divisor)
{
	this->dividend = dividend;
	this->divisor = divisor;

	this->integralQuotient = dividend / divisor;
    this->integralModulus = dividend % divisor;
    this->integralError = divisor >> 1;
}

int MwIntegralQuotientDistribution::PullSequential()
{
    this->integralError -= this->integralModulus;
    if (this->integralError < 0)
    {
        this->integralError += this->divisor;
        return this->integralQuotient + 1;
    }

	return this->integralQuotient;
}