#pragma once

#include "..\MwGlobals.h"

#include "MwList.h"

MWDLLTEMPLATEMEMBER template class MWDLLCLASS MwList<int>;

class MWDLLCLASS MwRandomPool
{
public:
	MwList<int> pool;

	MwRandomPool(void);
	MwRandomPool(int count);
	~MwRandomPool(void);

	void Generate(int count);

	void Put(int value);
	int Pull();

	bool Contains(int value);
	bool Remove(int value);
};

