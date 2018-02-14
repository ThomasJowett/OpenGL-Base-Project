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

	//clear background colour.
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);

	//Load models and textures
	MeshData dodgeballGeometry = OBJLoader::LoadOBJ("Dodgeball.obj");

	//std::cout << test;
	
	//MeshData floorGeometry = OBJLoader::LoadOBJ("Floor.obj");

	Texture2D * texture = new Texture2D("Dodgeball_Diffuse.raw", 512, 512);
	GLuint dodgeBallTextureID = texture->GetID();

	//texture = new Texture2D("LogoDodgeball.raw.raw", 512, 512);
	//GLuint courtTextureID = texture->GetID();

	
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

	Appearance * appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
	//Appearance * appearance = new Appearance(floorGeometry, floorMaterial, courtTextureID);
	Transform * transform = new Transform();

	Vector3D position;

	GameObject * gameObject = new GameObject(transform,appearance);
	for (int i = 0; i < 5; i++)
	{
		position = { 1000 * (float)rand() / (RAND_MAX)-5,  1000 * (float)rand() / (RAND_MAX)-5, 1000 * (float)rand() / (RAND_MAX)-5 };
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
		transform = new Transform(position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });

		gameObject = new GameObject(transform, appearance);

		mGameObjects.push_back(gameObject);
	}
	
	//Set the Relationships


	//Initialise Root Node
	Root = new SceneNode;


	//FPS Counter
	mInitialTime = time(NULL);
	mFrameCount = 0;

	//glutTimerFunc();

	//enable Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	//Enable the Texture2D
	glEnable(GL_TEXTURE_2D);

	//Set some parameters so it renders correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
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

void GameScreenLevel1::SetMaterial(Material material) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.specularPower);
}


GameScreenLevel1::~GameScreenLevel1()
{	
	if (Root)  delete Root;
}

//--------------------------------------------------------------------------------------------------
void DrawTextured2DSquare()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glEnd();
}

void GameScreenLevel1::OutputLine(float x, float y, std::string text)
{
	glRasterPos2f(x, y); //where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
		
	Camera::GetInstance()->Render();
	SetLight();

	Root->Traverse();
	
	for (auto GameObject : mGameObjects)
	{
		/*
		if (GameObject->GetBoundingSphere()->GetCollided())
		{
			GameObject->GetAppearance->SetMaterial({
				{ 1.0f, 0.2f, 0.2f, 1.0f },
				{ 0.40f, 0.40f, 0.4f, 1.0f },
				{ 0.8f, 0.8f, 0.8f, 1.0f },
				50.0f });
		}
		else
			GameObject->GetAppearance->SetMaterial({
				{ 0.2f, 0.2f, 0.2f, 1.0f },
				{ 0.40f, 0.40f, 0.4f, 1.0f },
				{ 0.8f, 0.8f, 0.8f, 1.0f },
				50.0f });*/
		GameObject->Render();
	}
	
	//Render text
	glColor3f(0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(5, 95, FPS);
	OutputLine(5, 90, "Click and drag to orbit Camera");
	OutputLine(5, 85, "A & D Rotate Cabin");
	OutputLine(5, 80, "W & S Rotate Stick");
	OutputLine(5, 75, "Q & E Rotate Boom");
	OutputLine(5, 70, "R & F Rotate Bucket");
	OutputLine(5, 65, "Scroll mouse wheel to zoom in");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
//--------------------------------------------------------------------------------------------------
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	Camera::GetInstance()->Update(deltaTime, e, Vector3D{ 0.0f, 100.0f, 0.0f });

	//Detect Input
	if ((GetAsyncKeyState('A') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('D') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('W') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('S') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('Q') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('E') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('R') & 0x80 != 0)) {}
	if ((GetAsyncKeyState('F') & 0x80 != 0)) {}


	//Update the Transforms
	
	for (auto GameObject : mGameObjects)
	{
		GameObject->Update(deltaTime);
	}

	// check for collisions
	for (int i = 0; i < mGameObjects.size() - 1; i++) {
		for (int j = i + 1; j < mGameObjects.size(); j++) {
			//Collision::SphereSphereCollision(mGameObjects[i]->GetBoundingSphere(), mGameObjects[j]->GetBoundingSphere());
			
		}
	}
	
	//Update FPS
	mFrameCount++;
	mFinalTime = time(NULL);
	if (mFinalTime - mInitialTime >= 1)
	{
		FPS = "FPS: " + std::to_string(mFrameCount / (mFinalTime - mInitialTime));
		mFrameCount = 0;
		mInitialTime = mFinalTime;
	}
}
//--------------------------------------------------------------------------------------------------