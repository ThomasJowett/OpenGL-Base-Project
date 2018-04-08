#include "GameScreenLevel1.h"

using namespace::std;

extern float gWinningTime;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	mWon = false;
	std::cout << "GameScreenLevel1Constructor\n";
	srand(time(NULL));

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	glShadeModel(GL_SMOOTH);

	mCamera = new Camera({ 0,0,0 }, 90.0f, -30.0f, 1300.0f);

	//clear background colour.
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
	
	//Load Models
	MeshData floorGeometry = OBJLoader::LoadOBJ("Models/Floor.obj");
	MeshData dodgeballGeometry = OBJLoader::LoadOBJ("Models/Dodgeball.obj");
	MeshData characterGeometry = OBJLoader::LoadOBJ("Models/SpaceMan.obj");

	//Load Textures
	GLuint dodgeBallTextureID = Texture2D::LoadTexture2D("Textures/Dodgeball_Diffuse.png");
	GLuint courtTextureID = Texture2D::LoadTexture2D("Textures/Court_Diffuse.png");
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
	//collider = new AABB(transform, 180.0f, 100.0f, 100.0f);
	gameObject = new Level1Character("Denzel", transform, appearance, particle, collider, { 0.0f, 0.0f, 1.0f });

	mGameObjects.push_back(gameObject);

	
	for (int i = 0; i < 100; i++)
	{
		position.x = 800 * (float)rand() / (RAND_MAX) -400;
		position.y = 800 * (float)rand() / (RAND_MAX);
		position.z = 1600 * (float)rand() / (RAND_MAX) -800;
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
		transform = new Transform(position, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
		collider = new Sphere(transform, 10.0f);
		//particle = new ParticleModel(1000 * (float)rand() / (RAND_MAX), { 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f }, transform, 20.0f);

		particle = new ParticleModel(10, { 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f }, transform);
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
	

	//FPS Counter
	mInitialTime = time(NULL);
	mFrameCount = 0;

	//glutTimerFunc();

	//enable Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	//Enable the Texture2D
	glEnable(GL_TEXTURE_2D);

	mText = new TextRender("Fonts/Calibri.ttf", 20);
	
	//pre-load the sound effects
	SoundManager::GetInstance()->LoadSoundEffect("SFX/Victory.wav");
	SoundManager::GetInstance()->LoadSoundEffect("SFX/Bounce.wav");
	SoundManager::GetInstance()->LoadSoundEffect("SFX/Scream.wav");

	mPlayerController = new PlayerController((Character*)mGameObjects[1], 0);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::SetLight() {
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

GameScreenLevel1::~GameScreenLevel1()
{	
	if (Root)  delete Root;
}

//--------------------------------------------------------------------------------------------------


void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glEnable(GL_LIGHTING);
		
	mCamera->Render();
	SetLight();

	Root->Traverse();

	glDisable(GL_LIGHTING);

	//Render text
	mText->DisplayText(mTime, SDL_Colour{ 1,5,1 }, 1632, 1000, LEFT);
	mText->DisplayText(FPS, SDL_Colour{ 1,1,1 }, 96, 1000, RIGHT);
}
//--------------------------------------------------------------------------------------------------
void GameScreenLevel1::Update(float deltaTime, std::vector<SDL_Event> e)
{
	//Detect Input
	mPlayerController->Update(deltaTime, e);

	//Update the Transforms
	
	for (auto GameObject : mGameObjects)
	{
		GameObject->Update(deltaTime);
		if (GameObject->GetName() == "Denzel")
		{
			Level1Character* denzel = dynamic_cast<Level1Character*>(GameObject);

			if (GameObject->GetTransform()->GetPosition().z > 800.0f)
			{
				if (!mWon)
				{
					SoundManager::GetInstance()->PlaySoundEffect("SFX/Victory.wav", -1, 0);
					mWon = true;
					gWinningTime = mTimer;
					GameScreenManager::GetInstance()->ChangeScreen(SCREEN_HIGHSCORES);
					return;
				}
			}
			else if (denzel->GetLives() <= 0)
			{
				SoundManager::GetInstance()->PlaySoundEffect("SFX/Scream.wav", -1, 0);
				GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL1);
				return;
			}
		}
	}

	// check for collisions
	Collision::ResolveCollisions(Collision::DetectCollisions(mGameObjects));

	mCamera->Update(deltaTime, mGameObjects[0]->GetTransform()->GetPosition());
	
	//Update FPS
	mFrameCount++;
	mFinalTime = time(NULL);
	if (mFinalTime - mInitialTime >= 1)
	{
		sprintf(FPS, "FPS: %i", mFrameCount / (mFinalTime - mInitialTime));
		mFrameCount = 0;
		mInitialTime = mFinalTime;
	}

	//update timer
	mTimer += deltaTime;
	sprintf(mTime, "Time: %fs", mTimer);
	
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x80 != 0))
	{
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
		return;
	}
	else if((GetAsyncKeyState('R') & 0x80 != 0))
	{
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL1);
		return;
	}
}
//--------------------------------------------------------------------------------------------------