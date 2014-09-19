#pragma once

#include "..\..\MwGlobals.h"

#include "..\MwMedia.h"

#include "..\..\Engine\Primitive\MwPixelFormat.h"

#include "..\..\Tools\Streams\MwBaseStream.h"

// TODO For symmetry, either merge this and MwTexture (with MwDeviceIndependentImage, for example) or make a similar object for meshes
class MWDLLCLASS MwImage :
	public MwMedia
{
private:
	void Init();

protected:
	int exportEncoding;

public:
	int width, height, depth;
	unsigned char *pixelData;
	MwPixelFormat pixelFormat;


	MwImage(void);
	MwImage(MwImage &source);
	MwImage(MwImage &source, MwPixelFormat &pixelFormat);
	virtual ~MwImage(void);

	virtual bool Load(MwBaseStream &source);
	virtual bool Save(MwBaseStream &destination, const char *encoding);

	void SetPixelFormat(MwPixelFormat &pixelFormat, bool dither = true);
	MwPixelFormat GetPixelFormat();
	
	void SetSize(int width, int height, int depth);

	void CopyPixels(MwImage &source, int srcX, int srcY, int srcZ, int destX, int destY, int destZ, int width, int height, int depth);
	void CopyPixels(MwImage &source, int srcX, int srcY, int srcZ, int width, int height, int depth);
	void CopyPixels(MwImage &source);
	void Copy(MwImage &source);

	void SetPixel(int x, int y, int z, int unsigned value);
	unsigned int GetPixel(int x, int y, int z);
	unsigned int GetSample(float u, float v, int z);
	unsigned int GetSample(float u, float v, float w);
};

