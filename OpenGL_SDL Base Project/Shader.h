#pragma once

#include <string>

#include "Commons.h"
#include "Transform.h"

class Camera;

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind() { glUseProgram(mProgram); }
	void UnBind() { glUseProgram(0); }
	void UpdateWorld(const Transform* transform);
	void UpdateViewProjection(const Matrix4x4& view, const Matrix4x4& projection, const Vector3D eyePosition);
	void UpdateLight(const PointLight& pointLight);
	void UpdateMaterial(const Material& material);
	
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		MODEL_U,
		VIEW_U,
		PROJECTION_U,
		EYEPOSW_U,
		TEXTURE_DIFFUSE_U,
		TEXTURE_SPECULAR_U,

		NUM_UNIFORMS
	};

	enum
	{
		MATERIAL_UB,
		LIGHT_UB,

		NUM_UNIFORM_BLOCKS
	};

	GLuint mProgram;
	GLuint mShaders[NUM_SHADERS];
	GLuint mUniforms[NUM_UNIFORMS];
	GLuint mUniformBlocks[NUM_UNIFORM_BLOCKS];

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, GLenum shaderType);
};

