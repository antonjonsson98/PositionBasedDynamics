#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2018 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------

#include "core/app.h"
#include "render/window.h"
#include "MeshResource.h"
#include "ShaderObject.h"
#include "GraphicsNode.h"
#include "CameraMovement.h"
#include "LightNode.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();

	/// open app
	bool Open();
	/// run app
	void Run();
private:

	GLuint triangle;
	Display::Window * window;
	LightNode * lightNode;
	CameraMovement * cameraMovement;
};
} // namespace Example