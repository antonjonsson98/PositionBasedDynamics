#pragma once

#include <memory>
#include "core/app.h"
#include "MeshResource.h"
#include "ShaderObject.h"

class GraphicsNode
{
public:
	GraphicsNode();
	~GraphicsNode();

	std::shared_ptr<MeshResource> getMeshResource();
	void setMeshResource(std::shared_ptr<MeshResource> meshResource);

	std::shared_ptr<ShaderObject> getShaderObject();
	void setShaderObject(std::shared_ptr<ShaderObject> shaderObject);

	std::shared_ptr<Matrix4D> getTransform();
	void setTransform(std::shared_ptr<Matrix4D> transform);

	void setup();
	void draw();

private:
	std::shared_ptr<MeshResource> mesh;
	std::shared_ptr<ShaderObject> shader;
	std::shared_ptr<Matrix4D> transform;
};
