#pragma once
#include "GameScreen.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Transform.h"

class TestLevel :
	public GameScreen
{
public:
	TestLevel();
	~TestLevel();

	void Update(float deltaTime, std::vector<SDL_Event> e) override;
	void Render() override;

private:
	Mesh* mesh;
	Mesh* mesh2;
	Shader* shader;
	Transform transform;
	Transform transform2;
	Camera camera;

	float rotation;
};

