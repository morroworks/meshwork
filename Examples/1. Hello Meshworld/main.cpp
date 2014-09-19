//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine example Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This example shows how to create a basic setup with meshwork.
// It creates a windows form, an instance of the engine, opens a scene and renders it.
// Default renderer is Meshwork's software rasterizer - Soras

#include "MeshworkEngine.h"

class MyRenderWindow :
	public MwWindowsForm
{
public:
	Meshwork *engine;

	MyRenderWindow(void)
	{
		this->engine = new Meshwork(&this->handle);

		this->engine->ImportScene("..\\..\\Resources\\Robot\\Robot.3ds");
	};

	~MyRenderWindow()
	{
		delete this->engine;
	};

	void MainLoop()
	{
		this->engine->RenderWorld();
	};
};

int main(int argc, char *args[])
{
	MyRenderWindow renderWindow;
	return MwWindowsForm::PerformFormLoop();
}