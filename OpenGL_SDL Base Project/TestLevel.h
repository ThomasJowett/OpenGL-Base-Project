#pragma once
#include "GameScreen.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Transform.h"
#include "Camera.h"

class TestLevel :
	public GameScreen
{
public:
	TestLevel();
	~TestLevel();

	void Update(float deltaTime, std::vector<SDL_Event> e) override;
	void Render() override;

private:
	Shader* mShader;

	PointLight light;

	Camera camera;

	float rotation;
};

