#pragma once
#include "render/window.h"
#include "Vector4D.h"


class CameraMovement
{
public:
	CameraMovement();
	void setWindow(Display::Window * window);
	void keyPressed(int32 key, int32 scanCode, int32 action, int32 modifier);
	float getYaw();
	float getPitch();
	void updateKeyPresses();
	float getDeltaX();
	float getDeltaZ();
private:
	bool pressed;
	float64 prevX;
	float64 prevY;
	float yaw;
	float pitch;
	float movementSpeed;
	float shiftSpeed;
	float deltaX;
	float deltaZ;
	bool isPressedShift;
	bool isPressedW;
	bool isPressedA;
	bool isPressedS;
	bool isPressedD;

};
