#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2()
{
	srand(time(NULL));

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	glShadeModel(GL_SMOOTH);

	mCamera = new Camera({ 0,0,0 }, 180.0f, -30.0f, 500.0f);

	//clear background colour.
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);

	MeshData floorGeometry = OBJLoader::LoadOBJ("Models/Floor.obj");
	MeshData dodgeballGeometry = OBJLoader::LoadOBJ("Models/Dodgeball.obj");
	MeshData characterGeometry = OBJLoader::LoadOBJ("Models/SpaceMan.obj");

	//Load Textures
	GLuint dodgeBallTextureID = Texture2D::LoadTexture2D("Textures/Dodgeball_Diffuse.png");
	GLuint courtTextureID = Texture2D::LoadTexture2D("Textures/Court2_Diffuse.png");
	GLuint SpaceManTextureID = Texture2D::LoadTexture2D("Textures/SpaceMan_Diffuse.png");


	Material dodgeballMaterial = {
		{ 0.4f, 0.2f, 0.2f, 1.0f },
		{ 0.8f, 0.2f, 0.2f, 1.0f },
		{ 0.4f, 0.4f, 0.4f, 1.0f },
		10.0f
	};

	Material floorMaterial = {
		{ 0.4f, 0.4f, 0.4f, 1.0f },
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		20.0f
	};

	Material SpaceManMaterial = {
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		50.0f
	};

	Transform * transform;
	ParticleModel * particle;
	Vector3D position;
	GameObject * gameObject;

	Appearance * appearance = new Appearance(floorGeometry, floorMaterial, courtTextureID);
	transform = new Transform({ 0.0f,0.0f,0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });

	Collider * collider = new AABB(transform, 10.0f, 944.0f, 1700.0f);

	gameObject = new GameObject("Floor", transform, appearance, nullptr, collider);
	mGameObjects.push_back(gameObject);

	position = { 0.0f, 100.0f, -800.0f };
	appearance = new Appearance(characterGeometry, SpaceManMaterial, SpaceManTextureID);
	transform = new Transform(position, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
	particle = new ParticleModel(10.0f, { 0.0f, 0.0f, 0.0f }, transform);
	collider = new Sphere(transform, 62.0f);
	gameObject = new Level2Character("Denzel", transform, appearance, particle, collider, { 0.0f, 0.0f, 1.0f });
	mGameObjects.push_back(gameObject);

	position = { 0.0f, 40.0f, 0.0f };

	for (int i = 0; i < 8; i++)
	{
		position.x = 200.0f + (-50.0f * i);
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
		transform = new Transform(position, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
		collider = new Sphere(transform, 10.0f);
		particle = new ParticleModel(10, { 0.0f, 0.0f, 0.0f }, transform);
		gameObject = new GameObject("Ball", transform, appearance, particle, collider);
		mGameObjects.push_back(gameObject);
	}

	//Initialise Root Node
	Root = new SceneNode;

	//Set the Relationships
	for (auto gameObject : mGameObjects)
	{
		Root->AddChild(gameObject);
	}

	//enable Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	PlayerController* playerController = new PlayerController((Character*)mGameObjects[1], 0);
	mPlayerControllers.push_back(playerController);
}

void GameScreenLevel2::SetLight() {
	Lighting light = {
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
	// position of the light in homogeneous coordinates (x, y, z, w)
	// w should be 0 for directional lights, and 1 for spotlights
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

GameScreenLevel2::~GameScreenLevel2()
{
	if (Root)  delete Root;
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glEnable(GL_LIGHTING);

	mCamera->Render();
	SetLight();
	Root->Traverse();

	glDisable(GL_LIGHTING);
}

void GameScreenLevel2::Update(float deltaTime, std::vector<SDL_Event> events)
{
	for (auto playerController : mPlayerControllers)
	{
		playerController->Update(deltaTime, events);
	}

	for (auto gameObject : mGameObjects)
	{
		gameObject->Update(deltaTime);
	}

	// check for collisions
	Collision::ResolveCollisions(Collision::DetectCollisions(mGameObjects));

	mCamera->Update(deltaTime, mGameObjects[1]->GetTransform()->GetPosition());

	if ((GetAsyncKeyState(VK_ESCAPE) & 0x80 != 0))
	{
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
	}
}
