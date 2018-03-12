#include "GameScreenLevel1.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
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
	MeshData floorGeometry = OBJLoader::LoadOBJ("Floor.obj");
	MeshData dodgeballGeometry = OBJLoader::LoadOBJ("Dodgeball.obj");
	
	//MeshData dodgeballGeometry = Load3DS("Car_Backfire.3DS");

	//Load Textures
	GLuint dodgeBallTextureID = Texture2D::LoadTexture2D("Dodgeball_Diffuse.raw", 512, 512);
	GLuint courtTextureID = Texture2D::LoadTexture2D("Court_Diffuse.raw", 1200, 1200);

	
	Material dodgeballMaterial = {	
		{ 0.4f, 0.2f, 0.2f, 1.0f },
		{ 0.8f, 0.2f, 0.2f, 1.0f },
		{ 0.4f, 0.4f, 0.4f, 1.0f },
		10.0f 
	};

	Material floorMaterial = {
		{ 0.4f, 0.2f, 0.2f, 1.0f },
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		20.0f
	};

	Transform * transform;
	ParticleModel * particle;
	Vector3D position;
	GameObject * gameObject;

	Appearance * appearance = new Appearance(floorGeometry, floorMaterial, courtTextureID);
	transform = new Transform({ 0.0f,0.0f,0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });

	gameObject = new GameObject(transform, appearance, nullptr);
	mGameObjects.push_back(gameObject);

	appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
	transform = new Transform(position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
	particle = new ParticleModel(10.0f, { 0.0f, 0.0f, 0.0f }, transform, 20.0f);
	gameObject = new Character(transform, appearance, particle);

	mGameObjects.push_back(gameObject);

	for (int i = 0; i < 2505; i++)
	{
		position.x = 800 * (float)rand() / (RAND_MAX) -400;
		position.y = 800 * (float)rand() / (RAND_MAX);
		position.z = 1600 * (float)rand() / (RAND_MAX) -800;
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
		transform = new Transform(position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });
		//particle = new ParticleModel(1000 * (float)rand() / (RAND_MAX), { 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f }, transform, 20.0f);

		particle = new ParticleModel(10, { 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f, 1 * (float)rand() / (RAND_MAX)-0.5f }, transform, 20.0f);
		gameObject = new GameObject(transform, appearance, particle);

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

	mVictorySound = new SoundEffects("SFX/Scream.wav");

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
	mText->DisplayText(mTime, SDL_Colour{ 1,1,1 }, 1632, 972);
	mText->DisplayText(FPS, SDL_Colour{ 1,1,1 }, 96, 1026);
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
		if (GameObject->GetTransform()->GetPosition().y < 0.0f && GameObject->GetParticleModel() != nullptr)
		{
			GameObject->GetTransform()->SetPosition(GameObject->GetTransform()->GetPosition().x, 0.0f, GameObject->GetTransform()->GetPosition().z);
			GameObject->GetParticleModel()->SetVelocity(Vector3D::Reflect(GameObject->GetParticleModel()->GetVelocity(), { 0.0f, -1.0f, 0.0f }));
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
	
	if ((GetAsyncKeyState(VK_RETURN) & 0x80 != 0))
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
}
//--------------------------------------------------------------------------------------------------