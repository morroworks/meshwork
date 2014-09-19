#pragma once

#include "..\..\MwGlobals.h"

#include "MwEntity.h"

class Meshwork;

class MWDLLCLASS MwEntityDispatcher
{
public:
	MwEntityDispatcher(void);
	~MwEntityDispatcher(void);

	virtual MwEntity *CreateEntity(Meshwork *context, int typeId) = 0;
};

