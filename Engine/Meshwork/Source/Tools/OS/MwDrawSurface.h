#pragma once

#include "..\..\MwGlobals.h"

#include <windows.h>

class MWDLLCLASS MwDrawSurface
{
public:
	void* pixelData;
	int width, height, pixelDataSize;
	BITMAPINFO bitmapInfo;

	MwDrawSurface(void);
	~MwDrawSurface(void);

	void SetSize(int width, int height);

	void Copy(void* pixelData);

	void Present(int x, int y, HDC deviceContext);
};

