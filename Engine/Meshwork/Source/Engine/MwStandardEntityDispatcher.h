#pragma once

#include "Base\MwEntityDispatcher.h"

class MwStandardEntityDispatcher :
	public MwEntityDispatcher
{
public:
	MwStandardEntityDispatcher(void);
	~MwStandardEntityDispatcher(void);

	virtual MwEntity *CreateEntity(Meshwork *context, int typeId);
};

