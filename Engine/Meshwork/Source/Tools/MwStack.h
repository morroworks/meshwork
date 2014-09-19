#pragma once

#include "..\MwGlobals.h"

#include "MwList.h"

template <typename T> class MWDLLCLASS MwStack
	: public MwList<T>
{
public:

	MwStack(int capacity = 8)
		: MwList(capacity)
	{
	};

	T& Push(T value)
	{
		return this->Add(value);
	};

	T& Pop()
	{
		return this->values[--this->count];
	};

	T& Peek()
	{
		return this->values[this->count - 1];
	};
};
