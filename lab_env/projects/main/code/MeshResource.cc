#include "MeshResource.h"


MeshResource::MeshResource()
{
	
}

MeshResource::MeshResource(float * vertexBuffer, int * indexBuffer, int vertexBufferLength, int indexBufferLength)
{
	vBuf = vertexBuffer;
	iBuf = indexBuffer;
	vBufLen = vertexBufferLength;
	iBufLen = indexBufferLength;
}

MeshResource::~MeshResource()
{
	/*free(vBuf);
	free(iBuf);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);*/
}

void MeshResource::setup()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void MeshResource::bindVertexBuffer()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vBufLen, vBuf, GL_STATIC_DRAW);
}

void MeshResource::bindIndexBuffer()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iBufLen, iBuf, GL_STATIC_DRAW);
}

void MeshResource::drawSetup()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshResource::bindVAO()
{
	glBindVertexArray(VAO);
}

void MeshResource::unbindVAO()
{
	glBindVertexArray(0);
}

int MeshResource::numIndices()
{
	return iBufLen / sizeof(int);
}

void MeshResource::loadFromFile(const char* filename)
{
	std::vector<Vector4D> vertices, normals, textures;
	std::vector<unsigned int> vertexIndices, normalIndices, textureIndices;
	std::vector<Vertex> vertexBuffer = std::vector<Vertex>();
	std::vector<int> indexBuffer = std::vector<int>();

	FILE* file = fopen(filename, "r");
	char line[256];
	while (fscanf(file, "%s", line) != EOF)
	{
		if (line[0] == 'v')
		{
			Vector4D coords;
			fscanf(file, "%f %f %f\n", &coords[0], &coords[1], &coords[2]);
			
			if (line[1] == 'n')
			{
				// vn
				normals.push_back(coords);
			}
			else if (line[1] == 't')
			{
				// vt
				textures.push_back(coords);
			}
			else
			{
				// v
				vertices.push_back(coords);
			}
		}
		else if (line[0] == 'f')
		{
			unsigned int tempVI[4], tempNI[4], tempTI[4];
			if (fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
			&tempVI[0], &tempTI[0], &tempNI[0], 
			&tempVI[1], &tempTI[1], &tempNI[1], 
			&tempVI[2], &tempTI[2], &tempNI[2], 
			&tempVI[3], &tempTI[3], &tempNI[3]) == 12)
			{
				// Split quad into two triangles
				vertexIndices.push_back(tempVI[0]);
				normalIndices.push_back(tempNI[0]);
				textureIndices.push_back(tempTI[0]);
				vertexIndices.push_back(tempVI[1]);
				normalIndices.push_back(tempNI[1]);
				textureIndices.push_back(tempTI[1]);
				vertexIndices.push_back(tempVI[2]);
				normalIndices.push_back(tempNI[2]);
				textureIndices.push_back(tempTI[2]);

				vertexIndices.push_back(tempVI[0]);
				normalIndices.push_back(tempNI[0]);
				textureIndices.push_back(tempTI[0]);
				vertexIndices.push_back(tempVI[2]);
				normalIndices.push_back(tempNI[2]);
				textureIndices.push_back(tempTI[2]);
				vertexIndices.push_back(tempVI[3]);
				normalIndices.push_back(tempNI[3]);
				textureIndices.push_back(tempTI[3]);
			}
			else
			{
				vertexIndices.push_back(tempVI[0]);
				normalIndices.push_back(tempNI[0]);
				textureIndices.push_back(tempTI[0]);
				vertexIndices.push_back(tempVI[1]);
				normalIndices.push_back(tempNI[1]);
				textureIndices.push_back(tempTI[1]);
				vertexIndices.push_back(tempVI[2]);
				normalIndices.push_back(tempNI[2]);
				textureIndices.push_back(tempTI[2]);
			}
			
		}
		else
		{
			// Line doesnt start with v, vn or vt. Read until next newline
			fscanf(file, "%256[^\n]\n");
		}

	}

	fclose(file);

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		Vertex v;
		v.pos[0] = vertices[vertexIndices[i] - 1][0];
		v.pos[1] = vertices[vertexIndices[i] - 1][1];
		v.pos[2] = vertices[vertexIndices[i] - 1][2];

		v.norm[0] = normals[normalIndices[i] - 1][0];
		v.norm[1] = normals[normalIndices[i] - 1][1];
		v.norm[2] = normals[normalIndices[i] - 1][2];

		v.tex[0] = textures[textureIndices[i] - 1][0];
		v.tex[1] = textures[textureIndices[i] - 1][1];

		vertexBuffer.push_back(v);
		indexBuffer.push_back(i);
	}
	
	vBuf = (float*)malloc(vertexBuffer.size() * sizeof(Vertex));
	memcpy(this->vBuf, (void*)&vertexBuffer[0], vertexBuffer.size() * sizeof(Vertex));
	
	iBuf = (int*)malloc(indexBuffer.size() * sizeof(int));
	memcpy(this->iBuf, (void*)&indexBuffer[0], indexBuffer.size() * sizeof(int));
	
	vBufLen = vertexBuffer.size() * sizeof(Vertex);
	iBufLen = indexBuffer.size() * sizeof(int);
}

MeshResource * MeshResource::getCubeMesh(Vector4D centerPoint, float width)
{
	float hw = width / 2; // Half the width
	float x = centerPoint[0];
	float y = centerPoint[1];
	float z = centerPoint[2];
	float* vertexBuffer = new float[72] 
	{ 
		-hw + x,	-hw + y,	-hw + z,		// pos 0
		0.8,		0.8,		0.8,		1,	// color 0
		1,			0.9,						// texture coord 0 
		-hw + x,	hw + y,		-hw + z,		// pos 1
		1,			0,			0,			1,	// color 1
		1,			0.1,						// texture coord 1 
		hw + x,		hw + y,		-hw + z,		// pos 2
		0,			1,			0,			1,	// color 2
		0,			0.1,						// texture coord 2
		hw + x,		-hw + y,	-hw + z,		// pos 3
		0,			0,			1,			1,	// color 3
		0,			0.9,						// texture coord 3
		-hw + x,	-hw + y,	hw + z,			// pos 4
		0,			1,			0,			1,	// color 4
		2,			0.9,						// texture coord 4
		-hw + x,	hw + y,		hw + z,			// pos 5
		0,			0,			1,			1,	// color 5
		2,			0.1,						// texture coord 5
		hw + x,		hw + y,		hw + z,			// pos 6
		0.8,		0.8,		0.8,		1,	// color 6
		3,			0.1,						// texture coord 6
		hw + x,		-hw + y,	hw + z,			// pos 7
		1,			0,			0,			1,	// color 7
		3,			0.9,						// texture coord 7
	};
	int* indexBuffer = new int[36]
	{
		0, 1, 2, 
		0, 2, 3,
		4, 0 ,3,
		4, 3, 7,
		4, 5, 1,
		4, 1, 0,
		5, 1, 2,
		5, 2, 6,
		7, 6, 3,
		6, 2, 3,
		4, 5, 7,
		5, 6, 7
	};
	MeshResource * r = new MeshResource(vertexBuffer, indexBuffer, 72, 36);
	return r;
}
