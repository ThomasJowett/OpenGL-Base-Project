#include "Shader.h"
#include <iostream>
#include <fstream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

Shader::Shader(const std::string& fileName)
{
	mProgram = glCreateProgram();
	mShaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	mShaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(mProgram, mShaders[i]);
	}

	glBindAttribLocation(mProgram, 0, "position");
	glBindAttribLocation(mProgram, 1, "texCoord");
	glBindAttribLocation(mProgram, 2, "normal");

	glLinkProgram(mProgram);
	CheckShaderError(mProgram, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(mProgram);
	CheckShaderError(mProgram, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	mUniforms[MODEL_U] = glGetUniformLocation(mProgram, "model");
	mUniforms[VIEW_U] = glGetUniformLocation(mProgram, "view");
	mUniforms[PROJECTION_U] = glGetUniformLocation(mProgram, "projection");
}

void Shader::Bind()
{
	glUseProgram(mProgram);
}

void Shader::Update(const Transform & transform, Camera& camera)
{
	Matrix4x4 model = transform.GetWorldMatrix();
	glUniformMatrix4fv(mUniforms[MODEL_U], 1, GL_TRUE, &model.m[0][0]);

	//glm::mat4 world = transform.GetWorldMatrix();
	//glUniformMatrix4fv(mUniforms[WORLD_U], 1, GL_FALSE, &world[0][0]);

	//glm::mat4 view = camera.GetView();
	//glUniformMatrix4fv(mUniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);

	//glm::mat4 projection = camera.GetProjection();
	//glUniformMatrix4fv(mUniforms[PROJECTION_U], 1, GL_FALSE, &projection[0][0]);

	Matrix4x4 view = camera.GetView();
	glUniformMatrix4fv(mUniforms[VIEW_U], 1, GL_FALSE, &view.m[0][0]);

	Matrix4x4 projection = camera.GetProjection();
	glUniformMatrix4fv(mUniforms[PROJECTION_U], 1, GL_FALSE, &projection.m[0][0]);
}

Shader::~Shader()
{
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
