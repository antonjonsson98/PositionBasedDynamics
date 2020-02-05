#pragma once

#include "Vector4D.h"
#include "core/app.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <map>

class MeshResource
{
public:
	MeshResource();
	MeshResource(float* vertexBuffer, int* indexBuffer, int vertexBufferLength, int indexBufferLength);

	~MeshResource();

	void setup();
	void bindVertexBuffer();
	void bindIndexBuffer();
	void drawSetup();
	void debugDrawSetup();
	void bindVAO();
	void unbindVAO();
	int numIndices();
	void loadFromFile(const char* filename);
	static MeshResource * getCubeMesh(Vector4D centerPoint, float width);
	static float * getCubeMeshVertexBuffer(Vector4D centerPoint, float width);
	static int * getCubeMeshIndexBuffer(Vector4D centerPoint, float width);

private:
	float * vBuf;
	int * iBuf;
	int vBufLen;
	int iBufLen;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
};

struct Vertex
{
	GLfloat pos[3];
	GLfloat norm[3];
	GLfloat tex[2];
};
