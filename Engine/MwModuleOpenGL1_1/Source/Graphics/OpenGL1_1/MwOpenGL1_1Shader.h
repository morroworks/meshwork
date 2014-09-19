#pragma once

#include "..\..\MeshworkEngine.h"

class MwOpenGL1_1GraphicsDevice;

class MwOpenGL1_1Shader :
	public MwDeviceIndependentShader
{
public:
	MwOpenGL1_1GraphicsDevice *context;

	MwMatrix modelTransform, viewTransform, projectionTransform,
    		 modelViewTransform;

	bool isAnimated;

	MwOpenGL1_1Shader(void);
	~MwOpenGL1_1Shader(void);
	
	virtual int GetParameterAddress(MwString parameterName);
	virtual void SetParameter(int address, int index, void *value);

	virtual bool Update(MwString &compilationMessage);
};

