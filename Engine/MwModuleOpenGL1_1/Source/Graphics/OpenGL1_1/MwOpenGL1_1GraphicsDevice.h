#pragma once

#include "..\..\MeshworkEngine.h"

#include <windows.h>
#include <gl\GL.h>

class MwOpenGL1_1Mesh;
class MwOpenGL1_1Shader;

class MwOpenGL1_1GraphicsDevice
	: public MwGraphicsDevice
{
private:
	MwOpenGL1_1Mesh *currentMesh;
	MwOpenGL1_1Shader *currentShader;
    
	MwPixelFormat pixelFormat;

	void *windowHandle_HWND, *deviceContext_HDC, *renderContext_HGLRC;
	int pixelFormatIndex;
	
	MwOpenGL1_1Mesh *animatedMesh;

	// Fills the animatedMesh member variable with vertex positions and normals affected by skinning
	void CreateAnimatedMesh(MwOpenGL1_1Mesh *glMesh);

public:
	MwMatrix *bones;
	int maxBones;

	MwOpenGL1_1GraphicsDevice();
	~MwOpenGL1_1GraphicsDevice(void);

	MwDeviceMesh *CreateMesh();
	MwDeviceTexture2D *CreateTexture();
	MwDeviceShader *CreateShader();

	bool SetRenderTargetWindow(void *windowHandle);
	bool SetRenderTargetTexture(MwDeviceTexture2D *texture);
	
	MwPixelFormat GetPixelFormat();

	void Clear(MwVector4 &color);

	void BeginScene();
	void EndScene();
	
	void SetViewport(int x, int y, int width, int height);
	
	void SetMesh(MwDeviceMesh &mesh);

	void SetShader(MwDeviceShader &shader);

	void SetRenderState(MwRenderState renderState);

	void RenderMesh();

	bool Present();
};
