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

	mCamera = new Camera(180.0f, -30.0f, 500.0f);

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
	ParticleModel * PhysicsComponent;
	Appearance* appearance;
	Collider* collider;
	Vector3D position;
	GameObject * gameObject;
	
	//the floor
	appearance = new Appearance(floorGeometry, floorMaterial, courtTextureID);
	transform = new Transform({ 0.0f,0.0f,0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
	collider = new AABB(transform, 10.0f, 944.0f, 1700.0f);
	gameObject = new GameObject("Floor", transform, appearance, nullptr, collider);
	mGameObjects.push_back(gameObject);
	
	//the Character
	position = { 0.0f, 100.0f, -800.0f };
	appearance = new Appearance(characterGeometry, SpaceManMaterial, SpaceManTextureID);
	transform = new Transform(position, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
	PhysicsComponent = new ParticleModel(100.0f, { 0.0f, 0.0f, 0.0f }, transform);
	collider = new Sphere(transform, 62.0f);
	mCharacter = new Level2Character("Denzel", transform, appearance, PhysicsComponent, collider, { 0.0f, 0.0f, 1.0f });
	mCharacter->AddChild(mCamera);
	mGameObjects.push_back(mCharacter);
	

	PlayerController* playerController = new PlayerController(mCharacter, 0);
	mPlayerControllers.push_back(playerController);

	//the oponent
	position = { 0.0f, 100.0f, 800.0f };
	appearance = new Appearance(characterGeometry, SpaceManMaterial, SpaceManTextureID);
	transform = new Transform(position, { 0.0f, (float)M_PI, 0.0f}, { 1.0f, 1.0f, 1.0f });
	PhysicsComponent = new ParticleModel(100.0f, { 0.0f, 0.0f, 0.0f }, transform);
	collider = new Sphere(transform, 62.0f);
	mEnemy = new Level2Enemy("Enemy", transform, appearance, PhysicsComponent, collider, { 0.0f, 0.0f, 1.0f });
	mGameObjects.push_back(mEnemy);

	//the balls
	position = { 0.0f, 40.0f, 0.0f };
	
	for (int i = 0; i < 8; i++)
	{
		position.x = 200.0f + (-50.0f * i);
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
		transform = new Transform(position, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
		collider = new Sphere(transform, 10.0f);
		PhysicsComponent = new ParticleModel(10, { 0.0f, 0.0f, 0.0f }, transform);
		gameObject = new GameObject("Ball", transform, appearance, PhysicsComponent, collider);
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

	mText = new TextRender("Fonts/Calibri.ttf", 20);
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
	if (mCamera) delete mCamera;
	if (Root)  delete Root;
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glEnable(GL_LIGHTING);

	mCamera->Render();
	SetLight();
	GameScreen::Render();//render all game objects

	mText->DisplayText(mPlayerScore, { 0, 0, 0 }, 960, 50, CENTER);
	mText->DisplayText(mEnemyScore, { 0, 0, 0 }, 960, 1000, CENTER);

	glDisable(GL_LIGHTING);
}

void GameScreenLevel2::Update(float deltaTime, std::vector<SDL_Event> events)
{
	GameScreen::Update(deltaTime, events);

	for (auto playerController : mPlayerControllers)
	{
		playerController->Update(deltaTime, events);
	}

	// check for collisions
	Collision::ResolveCollisions(Collision::DetectCollisions(mGameObjects));
	int i = 0;
	while (i < mGameObjects.size())
	{
		if (mGameObjects.at(i)->GetWorldTransform().GetPosition().y < -10.0f)
		{
			GameObject* toDelete = mGameObjects.at(i);
			mGameObjects.erase(mGameObjects.begin() + i);
			delete toDelete;
		}
		else
			i++;
	}

	sprintf(mPlayerScore, "%i", mCharacter->GetTimesHit());
	sprintf(mEnemyScore, "%i", mEnemy->GetTimesHit());

	if (!GetAllGameObjectsWithTag("Ball").size())
	{
		mTimer += deltaTime;
		if (mTimer > 5.0f)
		{
			GameScreenManager::GetInstance()->ChangeScreen(SCREEN_GAMEOVER);
			return;
		}
	}

	//mCamera->Update(deltaTime, events);

	if ((GetAsyncKeyState(VK_ESCAPE) & 0x80 != 0))
	{
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
		return;
	}
}
