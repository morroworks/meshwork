#pragma once

#include "..\..\MeshworkEngine.h"

class MwOpenGL1_1Texture2D
	: public MwDeviceTexture2D
{
public:
	unsigned int textureId;

	MwOpenGL1_1Texture2D();
	~MwOpenGL1_1Texture2D(void);

	void Update(void *data, int width, int height);
	void GetData(void *data);
};

