#pragma once

#include "core/app.h"
#include "render/window.h"
#include "MeshResource.h"
#include "ShaderObject.h"
#include "GraphicsNode.h"
#include "CameraMovement.h"
#include "LightNode.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

namespace PBD
{
class PBDScene : public Core::App
{
public:
	/// constructor
	PBDScene();
	/// destructor
	~PBDScene();

	/// open app
	bool Open();
	/// run app
	void Run();
private:

	Display::Window * window;
	CameraMovement * cameraMovement;
};
}