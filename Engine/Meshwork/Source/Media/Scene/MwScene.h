#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwMedia.h"

class Meshwork;

class MWDLLCLASS MwScene :
	public MwMedia
{
protected:
	Meshwork *context;

public:
	MwScene(void);
	virtual ~MwScene(void);

	void SetContext(Meshwork *context);
};

