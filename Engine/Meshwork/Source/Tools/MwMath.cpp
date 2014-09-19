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

#include "MwMath.h"

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <float.h>
#include <limits.h>

const float MwMath::Pi = 3.14159265358979f;
const double MwMath::Pi_d = 3.141592653589793238462;

// a.k.a. Tau
const float MwMath::Pi2 = MwMath::Pi * 2.0f;
const double MwMath::Pi2_d = MwMath::Pi_d * 2.0;

const float MwMath::PiHalf = MwMath::Pi / 2.0f;
const double MwMath::PiHalf_d = MwMath::Pi_d / 2.0;

// a.k.a The golden ratio
const float MwMath::Phi = 1.61803398874989f;
const double MwMath::Phi_d = 1.6180339887498948482;

const int MwMath::IntMin = INT_MIN;
const int MwMath::IntMax = INT_MAX;

const float MwMath::FloatMin = FLT_MIN;
const float MwMath::FloatMax = FLT_MAX;

const unsigned int MwMath::crcPolynomial_Normal = 0x04C11DB7;
const unsigned int MwMath::crcPolynomial_Reversed = 0xEDB88320;
const unsigned int MwMath::crcPolynomial_ReversedReciprocal = 0x82608EDB;

unsigned int MwMath::crcTable[256];

MwMath::Initialization MwMath::initialization;

MwMath::Initialization::Initialization(void)
{
	MwMath::CRC32GenerateTable(MwMath::crcPolynomial_Reversed);
}

MwMath::MwMath(void)
{
}


MwMath::~MwMath(void)
{
}

int MwMath::Min(int a, int b)
{
	if (a < b)
		return a;

	return b;
}

long long MwMath::Min(long long a, long long b)
{
	if (a < b)
		return a;

	return b;
}

float MwMath::Min(float a, float b)
{
	if (a < b)
		return a;

	return b;
}

int MwMath::Max(int a, int b)
{
	if (a > b)
		return a;

	return b;
}

long long MwMath::Max(long long a, long long b)
{
	if (a > b)
		return a;

	return b;
}

float MwMath::Max(float a, float b)
{
	if (a > b)
		return a;

	return b;
}

int MwMath::Trim(int x, int min, int max)
{
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}

long long MwMath::Trim(long long x, long long min, long long max)
{
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}

float MwMath::Trim(float x, float min, float max)
{
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}

int MwMath::High(int value)
{
	return value >> 16;
}

int MwMath::Low(int value)
{
	return value & 0xffff;
}

int MwMath::HighLow(int high, int low)
{
	return (high << 16) | (low & 0xffff);
}

int MwMath::Sign(int x)
{
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

float MwMath::Sign(float x)
{
	return x > 0 ? 1.0f : x < 0 ? -1.0f : 0.0f;
}

int MwMath::Abs(int x)
{
	return x >= 0 ? x : -x;
}

float MwMath::Abs(float x)
{
	return x >= 0 ? x : -x;
}

float MwMath::Round(float x)
{
	float intPart;
	return modf(x, &intPart) >= 0.5f ? ceilf(x) : floorf(x);
}

double MwMath::Round(double x)
{
	double intPart;
	return modf(x, &intPart) >= 0.5f ? ceil(x) : floor(x);
}

int MwMath::Power(int base, int exponent)
{
	return (int)pow((float)base, exponent);
}

float MwMath::Power(float base, float exponent)
{
	return powf(base, exponent);
}

double MwMath::Power(double base, double exponent)
{
	return pow(base, exponent);
}

float MwMath::Sqrt(float x)
{
	return sqrtf(x);
}

double MwMath::Sqrt(double x)
{
	return sqrt(x);
}

// TODO: test against 1 / Sqrt (SSE rsqrtss is faster and the compiler might optimize the code)
float MwMath::InvSqrt(float x)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
 
    x2 = x * 0.5f;
    y  = x;
    i  = *(long*)&y;						
    i  = 0x5F3759DF - (i >> 1);				
    y  = *(float*)&i;
    y  = y * (threehalfs - (x2 * y * y));	
 
    return y;
}

float MwMath::Sin(float x)
{
	return sinf(x);
}

double MwMath::Sin(double x)
{
	return sin(x);
}


float MwMath::Cos(float x)
{
	return cosf(x);
}

double MwMath::Cos(double x)
{
	return cos(x);
}


float MwMath::Tan(float x)
{
	return tanf(x);
}

double MwMath::Tan(double x)
{
	return tan(x);
}


float MwMath::Cot(float x)
{
	return 1.0f / tanf(x);
}

double MwMath::Cot(double x)
{
	return 1.0 / tan(x);
}


float MwMath::ArcSin(float x)
{
	return asinf(x);
}

double MwMath::ArcSin(double x)
{
	return asin(x);
}


float MwMath::ArcCos(float x)
{
	return acosf(x);
}

double MwMath::ArcCos(double x)
{
	return acos(x);
}


float MwMath::ArcTan(float x)
{
	return atanf(x);
}

double MwMath::ArcTan(double x)
{
	return atan(x);
}


float MwMath::ArcCot(float x)
{
	return MwMath::Pi / 2.0f - atanf(x);
}

double MwMath::ArcCot(double x)
{
	return MwMath::PiHalf_d - atan(x);
}


float MwMath::ArcTan2(float y, float x)
{
	return atan2f(y, x);
}

double MwMath::ArcTan2(double y, double x)
{
	return atan2(y, x);
}


int MwMath::Random(int n)
{
	return rand() % n;
}

float MwMath::Random()
{
	return (float)rand() / (float)RAND_MAX;
}

void MwMath::Randomize()
{
	srand((unsigned int)time(NULL));
}

void MwMath::CRC32GenerateTable(unsigned int crcPolynomial)
{
	for (int i = 0; i < 256; i++)
	{
		unsigned int remainder = i;
		for(int j = 0; j < 8; j++)
		{
			if (remainder & 1)
			{
				remainder = (remainder >> 1) ^ crcPolynomial;
			}
			else
			{
				remainder >>= 1;
			}
		}

		MwMath::crcTable[i] = remainder;
	}
}

unsigned int MwMath::CRC32(const void *source, unsigned int size, unsigned int seed)
{
    unsigned int result = ~seed;

    for (unsigned int i = 0; i < size; i++)
        result = MwMath::crcTable[((result & 0xFF) ^ ((unsigned char*)source)[i])] ^ (result >> 8);
            
    return ~result;
}