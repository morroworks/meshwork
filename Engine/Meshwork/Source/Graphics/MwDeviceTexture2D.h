#pragma once

#include "..\MwGlobals.h"

class MwGraphicsDevice;

class MWDLLCLASS MwDeviceTexture2D
{
public:
	MwDeviceTexture2D(void);
	virtual ~MwDeviceTexture2D(void);

	virtual void Update(void *data, int width, int height) = 0;
	virtual void GetData(void *data) = 0;
};

