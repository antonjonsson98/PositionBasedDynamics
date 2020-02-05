#pragma once

#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include "core/app.h"
#include "Matrix4D.h"
#include "Vector4D.h"


class ShaderObject 
{
public:
	ShaderObject();
	~ShaderObject();
	void insertVertexShader(const char* shader);
	void insertFragmentShader(const char* shader);
	void loadVertexShader(const char * filename);
	void loadFragmentShader(const char * filename);
	GLuint & getProgram();
	void useShaders();
	void insertUniform(Matrix4D m, const char * uniformName);
	void insertUniform(Vector4D v, const char * uniformName);
	void insertUniform(float f, const char * uniformName);
private:
	std::map<std::string, unsigned int> uniformMap;
	const char * vs;
	const char * ps;
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
};