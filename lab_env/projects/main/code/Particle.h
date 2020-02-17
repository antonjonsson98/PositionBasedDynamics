#pragma once

#include "Sphere.h"
#include "LightNode.h"

class Particle
{
public:
    Particle();
    ~Particle();
    float mass;
    float radius;
    Vector4D pos;
    Vector4D vel;
    void draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos);
private:
    Sphere sphere;
};

inline Particle::Particle()
{
    sphere = Sphere();
    sphere.setup();
    pos = Vector4D();
    vel = Vector4D();
    mass = 0.1f;
    radius = 0.2f;

}

inline Particle::~Particle()
{
}

inline void Particle::draw(Matrix4D view, Matrix4D perspective, LightNode light, Vector4D cameraPos)
{
    sphere.transform = Matrix4D::getTranslationMatrix(pos);
    sphere.draw();
    sphere.shader.insertUniform(sphere.transform, "transform");
    sphere.shader.insertUniform(view, "view");
    sphere.shader.insertUniform(perspective, "perspective");
    sphere.shader.insertUniform(light.getColor(), "LightColor");
    sphere.shader.insertUniform(light.getIntensity(), "Intensity");
    sphere.shader.insertUniform(light.getPos(), "LightPos");
    sphere.shader.insertUniform(cameraPos, "camPos");
    sphere.shader.insertUniform(Vector4D(1,0,0), "color");
}
