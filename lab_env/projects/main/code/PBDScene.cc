//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "PBDScene.h"
#include <cstring>
#include "Matrix4D.h"

using namespace Display;
namespace PBD
{

//------------------------------------------------------------------------------
/**
*/
PBDScene::PBDScene()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
PBDScene::~PBDScene()
{
	delete cameraMovement;
	delete window;
}

//------------------------------------------------------------------------------
/**
*/
bool
PBDScene::Open()
{
	App::Open();
	this->window = new Display::Window;
	cameraMovement = new CameraMovement();
	cameraMovement->setWindow(window);

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
PBDScene::Run()
{
    Sphere sphere = Sphere();
    sphere.setup();
    sphere.transform = Matrix4D::getTranslationMatrix(Vector4D(0.25f, 0, -3));

    Sphere sphere2 = Sphere();
    sphere2.setup();
    sphere2.transform = Matrix4D::getTranslationMatrix(Vector4D(-0.25f, 0, -3));

    Sphere sphere3 = Sphere();
    sphere3.setup();
    sphere3.transform = Matrix4D::getTranslationMatrix(Vector4D(0, sqrt(3)/4, -3));

    LightNode lightNode = LightNode(Vector4D(0, 10, 0), Vector4D(1, 1, 1), 1);

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

        sphere.draw();

        sphere.shader.insertUniform(sphere.transform, "transform");
		sphere.shader.insertUniform(view, "view");
		sphere.shader.insertUniform(perspective, "perspective");
		sphere.shader.insertUniform(lightNode.getColor(), "LightColor");
		sphere.shader.insertUniform(lightNode.getIntensity(), "Intensity");
		sphere.shader.insertUniform(lightNode.getPos(), "LightPos");
		sphere.shader.insertUniform(cameraPos, "camPos");
        sphere.shader.insertUniform(Vector4D(0,0,1), "color");

        sphere2.draw();

        sphere2.shader.insertUniform(sphere2.transform, "transform");
		sphere2.shader.insertUniform(view, "view");
		sphere2.shader.insertUniform(perspective, "perspective");
		sphere2.shader.insertUniform(lightNode.getColor(), "LightColor");
		sphere2.shader.insertUniform(lightNode.getIntensity(), "Intensity");
		sphere2.shader.insertUniform(lightNode.getPos(), "LightPos");
		sphere2.shader.insertUniform(cameraPos, "camPos");
        sphere2.shader.insertUniform(Vector4D(1,0,0), "color");

        sphere3.draw();

        sphere3.shader.insertUniform(sphere3.transform, "transform");
		sphere3.shader.insertUniform(view, "view");
		sphere3.shader.insertUniform(perspective, "perspective");
		sphere3.shader.insertUniform(lightNode.getColor(), "LightColor");
		sphere3.shader.insertUniform(lightNode.getIntensity(), "Intensity");
		sphere3.shader.insertUniform(lightNode.getPos(), "LightPos");
		sphere3.shader.insertUniform(cameraPos, "camPos");
        sphere3.shader.insertUniform(Vector4D(0,1,0), "color");

		Matrix4D identity = Matrix4D::getIdentityMatrix();

		this->window->SwapBuffers();

	}
}
}