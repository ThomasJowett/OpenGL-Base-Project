#include "TestLevel.h"
//#include "Mesh.h"

TestLevel::TestLevel()
{
	//shader = new Shader("Shaders/BasicShader");
	//Vertex vertices[] = {
		//Vertex(Vector3D(-0.5, -0.5, 0), Vector2D(0, 0)),
		//Vertex(Vector3D(0, 0.5, 0), Vector2D(0.5, 1)),
		//Vertex(Vector3D(0.5, -0.5, 0), Vector2D(1, 0))
	//};

	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	//glBindTexture(GL_TEXTURE_2D, Texture2D::LoadTexture2D("Images/DodgeballLogo.png"));
}


TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	//transform.UpdateWorldMatrix();
	///shader->Bind();
	//shader->Update(transform);
}

void TestLevel::Render()
{
	//mesh->Draw();
}
