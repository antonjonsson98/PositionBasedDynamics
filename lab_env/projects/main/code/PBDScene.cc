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
	PBDSolver solver = PBDSolver();
	SoftBodyObject object = SoftBodyObject(Vector4D(0, 0, 0), 4, 2, 1, 0.5f, 40.0f, 1.0f);
	//object.addForce(Vector4D(1000, 0, 0));
	object.particleList[7].vel = Vector4D(0, -20, 0);
	solver.addObject((PBDObject*)&object);
	//SoftBodyObject object2 = SoftBodyObject(Vector4D(3, 6, 0), 7, 7, 7, 0.5f, 20.0f, 0.5f);
	//object2.addForce(Vector4D(-50, 0, 0));
	//solver.addObject((PBDObject*)&object2);
	//FluidObject fluid = FluidObject(Vector4D(0, 1, 0), 6, 8, 6, 0.5f, 10.0f);
	//solver.addObject((PBDObject*)&fluid);



    LightNode lightNode = LightNode(Vector4D(0, 10, 0), Vector4D(1, 1, 1), 1);

	Matrix4D perspective = Matrix4D::getPerspectiveMatrix(-0.1f, 0.1f, 0.1f, -0.1f, 100, 0.1f);

	glEnable(GL_DEPTH_TEST);

	Vector4D cameraPos = Vector4D(-0.5f, 0, 5);
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

	solver.simulateTimeStep(0.0167f);
	
	object.draw(view, perspective, lightNode, cameraPos);
	//object2.draw(view, perspective, lightNode, cameraPos);
	//fluid.draw(view, perspective, lightNode, cameraPos);

	this->window->SwapBuffers();
	
	}
}
}