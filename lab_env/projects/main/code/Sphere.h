#pragma once

#include "MeshResource.h"
#include "ShaderObject.h"
#include "core/app.h"

class Sphere
{
public:
    Sphere();
    ~Sphere();

    MeshResource mesh;
    ShaderObject shader;
    Matrix4D transform;

    void setup();
    void draw();
};

inline Sphere::Sphere()
{
}

inline Sphere::~Sphere()
{
}

inline void Sphere::setup()
{
    shader.loadVertexShader("VertexShader.txt");
	shader.loadFragmentShader("FragmentShader.txt");
	shader.useShaders();
    glUseProgram(shader.getProgram());
    mesh.loadFromFile("sphere.obj");
	mesh.setup();
	mesh.bindVertexBuffer();
	mesh.bindIndexBuffer();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	mesh.drawSetup();
}

inline void Sphere::draw()
{
    mesh.bindVAO();

	glUseProgram(shader.getProgram());

	glDrawElements(GL_TRIANGLES, mesh.numIndices(), GL_UNSIGNED_INT, 0);
	mesh.unbindVAO();
}