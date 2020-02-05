#include "LightNode.h"

LightNode::LightNode()
{

}

LightNode::LightNode(Vector4D pos, Vector4D color, float intensity)
{
    this->pos = pos;
    this->color = color;
    this->intensity = intensity;
}

LightNode::~LightNode()
{
    
}

Vector4D LightNode::getPos()
{
    return this->pos;
}

Vector4D LightNode::getColor()
{
    return this->color;
}

float LightNode::getIntensity()
{
    return this->intensity;
}