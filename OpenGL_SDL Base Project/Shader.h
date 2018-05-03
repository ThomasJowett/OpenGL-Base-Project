#pragma once

#include <string>
#include <glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);
	void Bind();
	virtual ~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	GLuint mProgram;
	GLuint mShaders[NUM_SHADERS];
	GLuint mUniforms[NUM_UNIFORMS];

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, GLenum shaderType);
};

