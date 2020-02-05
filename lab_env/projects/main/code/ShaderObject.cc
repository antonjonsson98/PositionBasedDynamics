#include "ShaderObject.h"

ShaderObject::ShaderObject()
{

}

ShaderObject::~ShaderObject()
{
}

void ShaderObject::insertVertexShader(const char* shader)
{
	vs = shader;

	// setup vertex shader
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint length = strlen(vs);
	glShaderSource(this->vertexShader, 1, &vs, &length);
	glCompileShader(this->vertexShader);

	// get error log
	GLint shaderLogSize;
	glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 1)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}
}

void ShaderObject::insertFragmentShader(const char* shader)
{
	ps = shader;

	// setup pixel shader
	this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint length = strlen(ps);
	glShaderSource(this->pixelShader, 1, &ps, &length);
	glCompileShader(this->pixelShader);

	// get error log
	GLint shaderLogSize;
	glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 1)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}
}

void ShaderObject::loadVertexShader(const char * filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{

		printf("Vertex shader not loaded. File not found! ");
		return;
	}

	std::stringstream buffer;
	buffer << in.rdbuf();
	std::string s = buffer.str();

	insertVertexShader(s.c_str());
}

void ShaderObject::loadFragmentShader(const char * filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{

		printf("Fragment shader not loaded. File not found! ");
		return;
	}

	std::stringstream buffer;
	buffer << in.rdbuf();
	std::string s = buffer.str();
	
	insertFragmentShader(s.c_str());
}

GLuint & ShaderObject::getProgram() 
{
	return program;
}

void ShaderObject::useShaders()
{
	GLint shaderLogSize;
	this->program = glCreateProgram();

	glAttachShader(program, this->vertexShader);
	glAttachShader(program, this->pixelShader);

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 1)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}
}

void ShaderObject::insertUniform(Matrix4D m, const char * uniformName)
{
	std::map<std::string, unsigned int>::iterator i = uniformMap.find(uniformName);
	if (i != uniformMap.end()) // If key exists
	{
		glUniformMatrix4fv(i->second, 1, GL_TRUE, m.getFloatPointer());
	}
	else
	{
		unsigned int uniformLoc = glGetUniformLocation(program, uniformName);
		glUniformMatrix4fv(uniformLoc, 1, GL_TRUE, m.getFloatPointer());
		uniformMap[uniformName] = uniformLoc;
	}
	
}

void ShaderObject::insertUniform(Vector4D v, const char * uniformName)
{
	std::map<std::string, unsigned int>::iterator i = uniformMap.find(uniformName);
	if (i != uniformMap.end()) // If key exists
	{
		glUniform4fv(i->second, 1, v.getFloatPointer());
	}
	else
	{
		unsigned int uniformLoc = glGetUniformLocation(program, uniformName);

		glUniform4fv(uniformLoc, 1, v.getFloatPointer());
		uniformMap[uniformName] = uniformLoc;
	}
}

void ShaderObject::insertUniform(float f, const char * uniformName)
{
	std::map<std::string, unsigned int>::iterator i = uniformMap.find(uniformName);
	if (i != uniformMap.end()) // If key exists
	{
		glUniform1f(i->second, f);
	}
	else
	{
		unsigned int uniformLoc = glGetUniformLocation(program, uniformName);
		glUniform1f(uniformLoc, f);
		uniformMap[uniformName] = uniformLoc;
	}
}
