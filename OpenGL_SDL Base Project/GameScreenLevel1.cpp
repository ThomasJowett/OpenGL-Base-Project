#include "GameScreenLevel1.h"
#include "OBJLoader2.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1()
{
	mShader = new Shader("Shaders/BasicShader");

	mWon = false;
	srand(time(NULL));

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	glShadeModel(GL_SMOOTH);

	mCamera = new Camera();

	mCamera->Initialise(Vector3D(0, 1000, -1000), Vector3D(0, -1, 1), Vector3D(0, 1, 0), 90, 0.1f, 10000.0f);

	//clear background colour.
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);

	OBJModel obj;
	
	//Load Models
	Mesh* floorGeometry = new Mesh(obj.LoadOBJ("Models/Floor.obj", false));
	Mesh* dodgeballGeometry = new Mesh(obj.LoadOBJ("Models/Dodgeball.obj", false));
	Mesh* characterGeometry = new Mesh(obj.LoadOBJ("Models/SpaceMan.obj", false));

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

	Appearance * appearance = new Appearance(floorGeometry, floorMaterial, courtTextureID, courtTextureID);
	transform = new Transform({ 0.0f,0.0f,0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });

	Collider * collider = new AABB(transform, 10.0f, 944.0f, 1700.0f);

	gameObject = new GameObject("Floor", transform, appearance, nullptr, collider);
	mGameObjects.push_back(gameObject);
	position = { 0.0f, 100.0f, -800.0f };

	appearance = new Appearance(characterGeometry, SpaceManMaterial, SpaceManTextureID, SpaceManTextureID);
	transform = new Transform(position, {0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
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
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID, dodgeBallTextureID);
		transform = new Transform(position, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
		collider = new Sphere(transform, 10.0f);
		//particle = new ParticleModel(1000 * (float)rand() / (RAND_MAX), { 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f }, transform, 20.0f);

		particle = new ParticleModel(10, { 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f }, transform);
		gameObject = new GameObject("Ball", transform, appearance, particle, collider);

		mGameObjects.push_back(gameObject);
	}

	//Set the Relationships
	for (auto gameObject : mGameObjects)
	{
		Root->AddChild(gameObject);
	}
	

	//FPS Counter
	mInitialTime = time(NULL);
	mFrameCount = 0;
	
	mText = new TextRender("Fonts/Calibri.ttf", 20);
	
	//pre-load the sound effects
	SoundManager::GetInstance()->LoadSoundEffect("SFX/Victory.wav");
	SoundManager::GetInstance()->LoadSoundEffect("SFX/Bounce.wav");
	SoundManager::GetInstance()->LoadSoundEffect("SFX/Scream.wav");

	mPlayerController = new PlayerController((Character*)mGameObjects[1], 0);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::SetLight() {
	PointLight light = {
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
	if (mShader) delete mShader;
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{		
	//mCamera->Render();
	//SetLight();
	mShader->Bind();
	mCamera->Update(mShader);
	//mShader->UpdateLight(Vector3D(0, 10000, 0));
	Root->Traverse(mShader);
	mShader->UnBind();

	//Render text
	mText->DisplayText(mTime, SDL_Colour{ 255,255,255 }, 1632, 1000, LEFT);
	mText->DisplayText(FPS, SDL_Colour{ 255,255,255 }, 96, 1000, RIGHT);
	mText->DisplayText(mBallsHit, SDL_Colour{ 255,255,255 }, 96, 20, RIGHT);
}
//--------------------------------------------------------------------------------------------------
void GameScreenLevel1::Update(float deltaTime, std::vector<SDL_Event> events)
{
	//Detect Input
	mPlayerController->Update(deltaTime, events);

	//Update the Transforms
	
	for (auto GameObject : mGameObjects)
	{
		GameObject->Update(deltaTime);
		if (GameObject->GetName() == "Denzel")
		{
			Level1Character* denzel = dynamic_cast<Level1Character*>(GameObject);
			//gBallsHit = 4 - denzel->GetLives();
			if (GameObject->GetTransform()->GetPosition().z > 800.0f)
			{
				if (!mWon)
				{
					SoundManager::GetInstance()->PlaySoundEffect("SFX/Victory.wav", -1, 0);
					mWon = true;
					//gWinningTime = mTimer;
					GameScreenManager::GetInstance()->ChangeScreen(SCREEN_HIGHSCORES);
					
					return;
				}
			}
			else if (denzel->GetLives() <= 0)
			{
				
				SoundManager::GetInstance()->PlaySoundEffect("SFX/Scream.wav", -1, 0);
				GameScreenManager::GetInstance()->ChangeScreen(SCREEN_GAMEOVER);
				return;
			}
		}
	}

	// check for collisions
	Collision::ResolveCollisions(Collision::DetectCollisions(mGameObjects));

	//Update FPS
	mFrameCount++;
	mFinalTime = time(NULL);
	if (mFinalTime - mInitialTime >= 1)
	{
		sprintf_s(FPS, "FPS: %i", mFrameCount / (mFinalTime - mInitialTime));
		mFrameCount = 0;
		mInitialTime = mFinalTime;
	}

	//update timer
	mTimer += deltaTime;
	sprintf_s(mTime, "Time: %fs", mTimer);

	//sprintf(mBallsHit, "%i", gBallsHit);
	
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