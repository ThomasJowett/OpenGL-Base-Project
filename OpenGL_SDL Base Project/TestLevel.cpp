#include "TestLevel.h"

TestLevel::TestLevel()
{
	shader = new Shader("Shaders/BasicShader");
	Vertex vertices[] = {
		Vertex(Vector3D(-0.5, -0.5, 0), Vector2D(0, 0), Vector3D(0,0,1)),
		Vertex(Vector3D(0, 0.5, 0), Vector2D(0.5, 1), Vector3D(0,0,1)),
		Vertex(Vector3D(0.5, -0.5, 0), Vector2D(1, 0), Vector3D(0,0,1))
	};

	mesh = new Mesh("Models/SpaceMan.obj");
	glBindTexture(GL_TEXTURE_2D, Texture2D::LoadTexture2D("Textures/SpaceMan_Diffuse.png"));

	camera.Initialise(Vector3D(0, 0, -100), Vector3D(0, 0, 1), Vector3D(0, 1, 0), 90, 0.1, 1000);
}


TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime, std::vector<SDL_Event> e)
{
	camera.Update();
	transform.UpdateWorldMatrix();
	shader->Bind();
	shader->Update(transform, camera);
}

void TestLevel::Render()
{
	mesh->Draw();
}
