#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwDeviceTexture2D.h"

#include "Engine\SrTexture.h"

class MWDLLCLASS MwSorasTexture2D :
	public MwDeviceTexture2D
{
public:
	SrTexture *sorasTexture;

	MwSorasTexture2D(void);
	~MwSorasTexture2D(void);

	virtual void Update(void *data, int width, int height);
	virtual void GetData(void *data);
};

