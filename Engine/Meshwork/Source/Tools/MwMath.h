#pragma once

#include "..\MwGlobals.h"

class MWDLLCLASS MwMath
{
private:
	class MWDLLCLASS Initialization
	{
	public:
		Initialization(void);
	};

	static Initialization initialization;

public:
	static const float Pi;
	static const double Pi_d;

	static const float Pi2;			// a.k.a. Tau
	static const double Pi2_d;		// a.k.a. Tau

	static const float PiHalf;
	static const double PiHalf_d;

	static const float Phi;			// a.k.a The golden ratio
	static const double Phi_d;		// a.k.a The golden ratio

	static const int IntMin;
	static const int IntMax;
	static const float FloatMin;
	static const float FloatMax;

	static const unsigned int crcPolynomial_Normal;
	static const unsigned int crcPolynomial_Reversed;
	static const unsigned int crcPolynomial_ReversedReciprocal;
	static unsigned int crcTable[256];

	MwMath(void);
	~MwMath(void);

	static int Min(int a, int b);
	static long long Min(long long a, long long b);
	static float Min(float a, float b);
	
	static int Max(int a, int b);
	static long long Max(long long a, long long b);
	static float Max(float a, float b);
	
	static int Trim(int x, int min, int max);
	static long long Trim(long long x, long long int min, long long int max);
	static float Trim(float x, float min, float max);

	static int High(int value);
	static int Low(int value);
	static int HighLow(int high, int low);

	static int Sign(int x);
	static float Sign(float x);
	
	static int Abs(int x);
	static float Abs(float x);

	static float Round(float x);
	static double Round(double x);

	static int Power(int base, int exponent);
	static float Power(float base, float exponent);
	static double Power(double base, double exponent);

	static float Sqrt(float x);
	static double Sqrt(double x);

	static float InvSqrt(float x);

	static float Sin(float x);
	static double Sin(double x);

	static float Cos(float x);
	static double Cos(double x);

	static float Tan(float x);
	static double Tan(double x);

	static float Cot(float x);
	static double Cot(double x);

	static float ArcSin(float x);
	static double ArcSin(double x);

	static float ArcCos(float x);
	static double ArcCos(double x);

	static float ArcTan(float x);
	static double ArcTan(double x);

	static float ArcCot(float x);
	static double ArcCot(double x);

	static float ArcTan2(float y, float x);
	static double ArcTan2(double y, double x);

	static int Random(int n);
	static float Random();
	static void Randomize();

	static void CRC32GenerateTable(unsigned int crcPolynomial);
	static unsigned int CRC32(const void *source, unsigned int size, unsigned int seed);
};

