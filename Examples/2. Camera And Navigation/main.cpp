//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine example Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MeshworkEngine.h"

class MyRenderWindow :
	public MwWindowsForm
{
public:
	Meshwork *engine;
	
	MwTransform *cameraTransform;

	MyRenderWindow(void)
	{
		this->engine = new Meshwork(&this->handle);

		this->engine->SetGraphicsDevice("Direct3D 11");
		
		this->engine->ImportScene("..\\..\\Resources\\Terrain\\Terrain postprocess v1.mw");

		this->cameraTransform = (MwTransform*)this->engine->FindResourceX("Camera", MwResourceType_Transform);
	};

	~MyRenderWindow()
	{
		delete this->engine;
	};

	void MainLoop()
	{
		if (this->cameraTransform != 0)
		{
			// Free flight navigation - as it would be in a non reference point environments like space
			MwMatrix m;
			MwMatrix::CreateRotationY(m, -this->mouseDeltaX / 100.0f);
			MwMatrix::Multiply(this->cameraTransform->manual, m, this->cameraTransform->manual);
			MwMatrix::CreateRotationX(m, this->mouseDeltaY / 100.0f);
			MwMatrix::Multiply(this->cameraTransform->manual, m, this->cameraTransform->manual);

			MwVector3 moveVector(
				this->keys['D'] ? -1.0f : this->keys['A'] ? 1.0f : 0.0f,
				this->keys[VK_SPACE] ? 1.0f : this->keys[VK_SHIFT] ? -1.0f : 0.0f,
				this->keys['W'] ? 1.0f : this->keys['S'] ? -1.0f : 0.0f);
			MwVector3::Scale(moveVector, moveVector, this->engine->timer->time * 10.0f);
			MwMatrix::CreateTranslation(m, moveVector);
			MwMatrix::Multiply(this->cameraTransform->manual, m, this->cameraTransform->manual);
		}

		this->engine->RenderWorld();
	};
};

int main(int argc, char *args[])
{
	MyRenderWindow renderWindow;
	return MwWindowsForm::PerformFormLoop();
}