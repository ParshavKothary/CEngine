#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader(const std::string&  fileName);
	virtual ~Shader();

	void Bind();

private:
	static const int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, unsigned int type);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	GLuint _program;
	GLuint _shaders[2];
};

#endif // !SHADER_H
