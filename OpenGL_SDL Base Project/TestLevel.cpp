#include "TestLevel.h"
#include "OBJLoader2.h"

TestLevel::TestLevel()
{
	mShader = new Shader("Shaders/BasicShader");

	OBJModel obj;

	Mesh* spaceManMesh = new Mesh(obj.LoadOBJ("Models/SpaceMan.obj", false));
	Mesh* ballMesh = new Mesh(obj.LoadOBJ("Models/Ball.obj",true));
	Mesh* cubeMesh = new Mesh(obj.LoadOBJ("Models/Cube.obj", true));

	Material SpaceManMaterial = {
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		100.0f
	};

	light = {
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		Vector3D(0, 00 ,-100)
	};

	GLuint spacemanDiffuse = Texture2D::LoadTexture2D("Textures/SpaceMan_Diffuse.png");
	GLuint spacemanspecular = Texture2D::LoadTexture2D("Textures/SpaceMan_Specular.png");
	GLuint ballDiffuseTexture = Texture2D::LoadTexture2D("Textures/Ball_Diffuse.png");
	GLuint ballSpecularTexture = Texture2D::LoadTexture2D("Textures/Ball_Specular.png");
	GLuint cubeDiffuseTexture = Texture2D::LoadTexture2D("Textures/Crate_COLOR.png");
	GLuint cubeSpecularTexture = Texture2D::LoadTexture2D("Textures/Crate_SPEC.png");

	camera.Initialise(Vector3D(0, 0, -100), Vector3D(0, 0, 1), Vector3D(0, 1, 0), 90, 0.1f, 1000);

	Transform* transform = new Transform(Vector3D(50, 0, 0), Quaternion(0, rotation, 0), Vector3D(1,1,1));
	Appearance* appearance = new Appearance(spaceManMesh, SpaceManMaterial, spacemanDiffuse, spacemanspecular);
	GameObject* gameObject = new GameObject("Spaceman", transform, appearance, nullptr, nullptr);
	mGameObjects.push_back(gameObject);

	//transform = new Transform(Vector3D(-50, 0, 0), Quaternion(0, rotation, 0), Vector3D(0.5, 0.5, 0.5));
	//appearance = new Appearance(ballMesh, SpaceManMaterial, ballDiffuseTexture, ballSpecularTexture);
	//gameObject = new GameObject("Ball", transform, appearance, nullptr, nullptr);
	//mGameObjects.push_back(gameObject);

	transform = new Transform(Vector3D(-50, 0, 0), Quaternion(0, rotation, 0), Vector3D(0.5, 0.5, 0.5));
	appearance = new Appearance(cubeMesh, SpaceManMaterial, cubeDiffuseTexture, spacemanspecular);
	gameObject = new GameObject("Cube", transform, appearance, nullptr, nullptr);
	mGameObjects.push_back(gameObject);

	rotation = 0.0f;

	for (GameObject* gameObject : mGameObjects)
	{
		Root->AddChild(gameObject);
	}
}


TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime, std::vector<SDL_Event> e)
{
	mGameObjects[0]->GetTransform()->SetRotation(Quaternion(0, rotation, 0));
	mGameObjects[1]->GetTransform()->SetRotation(Quaternion(0, -rotation, 0));
	GameScreen::Update(deltaTime, e);
	light.position = Vector3D(0, 100 * sin(rotation), -100);
	
	rotation+= 0.01f;
}

void TestLevel::Render()
{
	mShader->Bind();
	camera.Update(mShader);
	mShader->UpdateLight(light);
	Root->Traverse(mShader);
	mShader->UnBind();
}
