#include "GraphicsNode.h"

GraphicsNode::GraphicsNode()
{
}

GraphicsNode::~GraphicsNode()
{
}

std::shared_ptr<MeshResource> GraphicsNode::getMeshResource()
{
	return this->mesh;
}

void GraphicsNode::setMeshResource(std::shared_ptr<MeshResource> meshResource)
{
	this->mesh = meshResource;
}

std::shared_ptr<ShaderObject> GraphicsNode::getShaderObject()
{
	return this->shader;
}

void GraphicsNode::setShaderObject(std::shared_ptr<ShaderObject> shaderObject)
{
	this->shader = shaderObject;
}

std::shared_ptr<Matrix4D> GraphicsNode::getTransform()
{
	return this->transform;
}

void GraphicsNode::setTransform(std::shared_ptr<Matrix4D> transform)
{
	this->transform = transform;
}

void GraphicsNode::setup()
{
	shader->loadVertexShader("VertexShader.txt");
	shader->loadFragmentShader("FragmentShader.txt");
	shader->useShaders();
	glUseProgram(shader->getProgram());
	mesh->loadFromFile("");
	mesh->setup();
	mesh->bindVertexBuffer();
	mesh->bindIndexBuffer();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	mesh->drawSetup();
}

void GraphicsNode::draw()
{
	mesh->bindVAO();
	GLint program2 = shader->getProgram();
 
	glUseProgram(shader->getProgram());

	glDrawElements(GL_TRIANGLES, mesh->numIndices(), GL_UNSIGNED_INT, 0);
	mesh->unbindVAO();
}
