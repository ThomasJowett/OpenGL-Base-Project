#pragma once

#include <string>
#include <glew.h>

#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	void Update(const Transform& transform, Camera& camera);
	
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		WORLD_U,
		VIEW_U,
		PROJECTION_U,

		NUM_UNIFORMS
	};
	GLuint mProgram;
	GLuint mShaders[NUM_SHADERS];
	GLuint mUniforms[NUM_UNIFORMS];

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, GLenum shaderType);
};

