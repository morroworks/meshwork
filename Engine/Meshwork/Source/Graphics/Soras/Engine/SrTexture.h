#pragma once

#include "..\..\..\MwGlobals.h"

#include "Primitive\SrARGB.h"

class MWDLLCLASS SrTexture
{
public:
    unsigned char* data;
    int width, height,
		highX, highY;
    int dataSize, numPixels;

	SrTexture(void);
    SrTexture(int width, int height);
	~SrTexture(void);

    void SetSize(int width, int height);
    void SetPixel(int X, int Y, SrARGB &color);
    void GetPixel(int X, int Y, SrARGB &color);
    void Clear();
    void Fill(SrARGB color);
};

