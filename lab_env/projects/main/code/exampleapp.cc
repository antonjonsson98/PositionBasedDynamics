//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "Matrix4D.h"

using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	delete lightNode;
	delete cameraMovement;
	delete window;
}

//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	cameraMovement = new CameraMovement();
	cameraMovement->setWindow(window);

	lightNode = new LightNode(Vector4D(0, 10, 0), Vector4D(1, 1, 1), 1);

	window->SetKeyPressFunction([this](int32 key, int32 scanCode, int32 action, int32 modifier)
	{
		cameraMovement->keyPressed(key, scanCode, action, modifier);
	});


	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{
	float rotation = 0.0f;
	bool active;
	Matrix4D perspective = Matrix4D::getPerspectiveMatrix(-0.1, 0.1, 0.1, -0.1, 10000000000000, 0.1f);

	glEnable(GL_DEPTH_TEST);

	Vector4D cameraPos = Vector4D(0, 0, 4);
	Vector4D cameraFront = Vector4D(0, 0, -1);
	Vector4D cameraUp = Vector4D(0, 1, 0);

	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();

		cameraMovement->updateKeyPresses();

		cameraFront[0] = cosf(-cameraMovement->getPitch() / 500) * cosf(cameraMovement->getYaw() / 500);
		cameraFront[1] = sinf(-cameraMovement->getPitch() / 500);
		cameraFront[2] = cosf(-cameraMovement->getPitch() / 500) * sinf(cameraMovement->getYaw() / 500);
		cameraFront[3] = 1;
		cameraFront = cameraFront.norm();

		cameraPos = cameraPos + cameraFront * cameraMovement->getDeltaZ();
		cameraPos = cameraPos + (cameraFront.cross(cameraUp)).norm() * cameraMovement->getDeltaX();

		Matrix4D view = Matrix4D::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		Matrix4D identity = Matrix4D::getIdentityMatrix();

		this->window->SwapBuffers();

	}
}

} // namespace Example