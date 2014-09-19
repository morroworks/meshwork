#pragma once

#include "..\..\..\..\MwGlobals.h"

class MWDLLCLASS SrMatrix
{
public:
    float 
		_11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44;

	static void Identity(SrMatrix &result);
	static void InvertTranspose3x3(SrMatrix &result, SrMatrix &source);
};