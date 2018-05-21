#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName)
{
	mProgram = glCreateProgram();
	mShaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	mShaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(mProgram, mShaders[i]);
	}

	glLinkProgram(mProgram);
	CheckShaderError(mProgram, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(mProgram);
	CheckShaderError(mProgram, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//TexCoord
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	//Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	//Uniforms
	mUniforms[MODEL_U] = glGetUniformLocation(mProgram, "model");
	mUniforms[VIEW_U] = glGetUniformLocation(mProgram, "view");
	mUniforms[PROJECTION_U] = glGetUniformLocation(mProgram, "projection");
	mUniforms[EYEPOSW_U] = glGetUniformLocation(mProgram, "eyePosW");

	//Texture Samplers
	mUniforms[TEXTURE_DIFFUSE_U] = glGetUniformLocation(mProgram, "diffuseTexture");
	glUniform1i(mUniforms[TEXTURE_DIFFUSE_U], 0);
	mUniforms[TEXTURE_SPECULAR_U] = glGetUniformLocation(mProgram, "specularTexture");
	glUniform1i(mUniforms[TEXTURE_SPECULAR_U], 1);

	//UniformBlocks
	glGenBuffers(1, &mUniformBlocks[MATERIAL_UB]);
	glBindBuffer(GL_UNIFORM_BUFFER, mUniformBlocks[MATERIAL_UB]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, mUniformBlocks[MATERIAL_UB], 0, sizeof(Material));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	GLuint MaterialIndex = glGetUniformBlockIndex(mProgram, "Material");
	glUniformBlockBinding(mProgram, MaterialIndex, mUniformBlocks[MATERIAL_UB]);	
	
	glGenBuffers(1, &mUniformBlocks[LIGHT_UB]);
	glBindBuffer(GL_UNIFORM_BUFFER, mUniformBlocks[LIGHT_UB]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLight), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 2, mUniformBlocks[LIGHT_UB], 0, sizeof(PointLight));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	GLuint LightIndex = glGetUniformBlockIndex(mProgram, "Light");
	glUniformBlockBinding(mProgram, LightIndex, mUniformBlocks[LIGHT_UB]);
}

void Shader::UpdateWorld(const Transform* transform)
{
	Matrix4x4 model = transform->GetWorldMatrix();
	glUniformMatrix4fv(mUniforms[MODEL_U], 1, GL_TRUE, &model.m[0][0]);
}

void Shader::UpdateViewProjection(const Matrix4x4& view, const Matrix4x4& projection, const Vector3D eyePosition)
{
	glUniformMatrix4fv(mUniforms[VIEW_U], 1, GL_FALSE, &view.m[0][0]);

	glUniformMatrix4fv(mUniforms[PROJECTION_U], 1, GL_FALSE, &projection.m[0][0]);

	glUniform3f(mUniforms[EYEPOSW_U], eyePosition.x, eyePosition.y, eyePosition.z);
}

void Shader::UpdateLight(const PointLight& pointLight)
{
	glBindBuffer(GL_UNIFORM_BUFFER, mUniformBlocks[LIGHT_UB]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PointLight), &pointLight);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Shader::UpdateMaterial(const Material& material)
{
	glBindBuffer(GL_UNIFORM_BUFFER, mUniformBlocks[MATERIAL_UB]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Material), &material);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Shader::~Shader()
{
	UnBind();
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(mProgram, mShaders[i]);
		glDeleteShader(mShaders[i]);
	}
	glDeleteProgram(mProgram);
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	char error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": " << error << " " << std::endl;
	}
}

std::string Shader::LoadShader(const std::string & fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

GLuint Shader::CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const char* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}
