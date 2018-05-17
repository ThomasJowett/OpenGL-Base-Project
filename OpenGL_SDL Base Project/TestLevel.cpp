#include "TestLevel.h"
#include "OBJLoader2.h"

TestLevel::TestLevel()
{
	shader = new Shader("Shaders/BasicShader");

	OBJModel obj;
	OBJModel obj2;

	mesh = new Mesh(obj.LoadOBJ("Models/SpaceMan.obj"));
	mesh2 = new Mesh(obj2.LoadOBJ("Models/Ball.obj"));
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, Texture2D::LoadTexture2D("Textures/SpaceMan_Diffuse.png"));

	camera.Initialise(Vector3D(0, 0, -100), Vector3D(0, 0, 1), Vector3D(0, 1, 0), 90, 0.1, 1000);

	rotation = 0.0f;
}


TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime, std::vector<SDL_Event> e)
{
	shader->Bind();
	GameScreen::Update(deltaTime, e);
	camera.Update();
	shader->UpdateViewProjection(camera);
	shader->UpdateLight(Vector3D(100 * sin(rotation), 100 * sin(rotation), 0));
	rotation+= 0.01f;
	transform.SetRotation(Quaternion(0, rotation, 0));
	transform2.SetRotation(Quaternion(0, rotation * -1, 0));
	transform2.SetScale(Vector3D(0.5, 0.5, 0.5));
	
	transform.UpdateWorldMatrix();
	transform2.UpdateWorldMatrix();
}

void TestLevel::Render()
{
	transform.SetPosition(Vector3D(-50, 0, 0));
	shader->UpdateWorld(transform);
	mesh->Draw();
	transform2.SetPosition(Vector3D(50, 0, 0));
	shader->UpdateWorld(transform2);
	mesh2->Draw();
	GameScreen::Render();
}
