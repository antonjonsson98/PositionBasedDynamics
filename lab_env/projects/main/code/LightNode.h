#pragma once

#include "Vector4D.h"

class LightNode
{
public:
	LightNode();
    LightNode(Vector4D pos, Vector4D color, float intensity);
	~LightNode();
    Vector4D getPos();
    Vector4D getColor();
    float getIntensity();

private:
    Vector4D pos;
    Vector4D color;
    float intensity;
};