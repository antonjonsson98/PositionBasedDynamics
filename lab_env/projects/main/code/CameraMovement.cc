#include "CameraMovement.h"

CameraMovement::CameraMovement()
{
	pressed = false;
	prevX = -1;
	prevY = -1;
	yaw = -3.1415 * 250;
	pitch = 0;
	movementSpeed = 0.15f;
	shiftSpeed = 0.3f;
	deltaX = 0;
	deltaZ = 0;
	isPressedShift = false;
	isPressedW = false;
	isPressedA = false;
	isPressedS = false;
	isPressedD = false;
}

void CameraMovement::setWindow(Display::Window * window)
{
	window->SetMousePressFunction([this](int32 button, int32 pressed, int32)
	{
		if (button == 0)
		{
			this->pressed = pressed == 1;
		}
	});

	window->SetMouseMoveFunction([this](float64 x, float64 y)
	{
		if (pressed)
		{
			if (prevX != -1 & prevY != -1)
			{
				yaw = yaw + x - prevX;
				pitch = pitch + y - prevY;
				prevX = x;
				prevY = y;
			}
			else
			{
				prevX = x;
				prevY = y;
			}
		}
		else
		{
			prevX = -1;
			prevY = -1;
		}
	});
}

void CameraMovement::keyPressed(int32 key, int32 scanCode, int32 action, int32 modifier)
{
	if (key == GLFW_KEY_LEFT_SHIFT)
	{
		isPressedShift = action != 0;
	}
	if (key == GLFW_KEY_W)
	{
		isPressedW = action != 0;
	}
	if (key == GLFW_KEY_A)
	{
		isPressedA = action != 0;
	}
	if (key == GLFW_KEY_S)
	{
		isPressedS = action != 0;
	}
	if (key == GLFW_KEY_D)
	{
		isPressedD = action != 0;
	}
}

float CameraMovement::getYaw()
{
	return yaw;
}

float CameraMovement::getPitch()
{
	return pitch;
}

void CameraMovement::updateKeyPresses()
{
	float speed = movementSpeed;	
	if (isPressedShift)
	{
		speed = shiftSpeed;
	}
	
	if (isPressedW)
	{
		deltaZ += speed;
	}
	if (isPressedA)
	{
		deltaX -= speed;
	}
	if (isPressedS)
	{
		deltaZ -= speed;
	}
	if (isPressedD)
	{
		deltaX += speed;
	}
}

float CameraMovement::getDeltaX()
{
	float r = deltaX;
	deltaX = 0;
	return r;
}

float CameraMovement::getDeltaZ()
{
	float r = deltaZ;
	deltaZ = 0;
	return r;
}
