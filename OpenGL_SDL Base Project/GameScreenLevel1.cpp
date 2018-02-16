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

	//Load Models
	MeshData dodgeballGeometry = OBJLoader::LoadOBJ("Dodgeball.obj");
	MeshData floorGeometry = OBJLoader::LoadOBJ("Floor.obj");

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

	Appearance * appearance;
	Transform * transform;
	Vector3D position;
	GameObject * gameObject;

	appearance = new Appearance(floorGeometry, floorMaterial, courtTextureID);
	transform = new Transform({ 0.0f,0.0f,0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });

	gameObject = new GameObject(transform, appearance, 0.0f);
	mGameObjects.push_back(gameObject);

	for (int i = 0; i < 20; i++)
	{
		position.x = 1000 * (float)rand() / (RAND_MAX)-5;
		position.y = 1000 * (float)rand() / (RAND_MAX)-5;
		position.z = 1000 * (float)rand() / (RAND_MAX)-5;
		appearance = new Appearance(dodgeballGeometry, dodgeballMaterial, dodgeBallTextureID);
		transform = new Transform(position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f,1.0f });

		gameObject = new GameObject(transform, appearance, 20.0f);

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
	OutputLine(5, 85, "WASD to move");
	OutputLine(5, 80, "Scroll mouse wheel to zoom in");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
//--------------------------------------------------------------------------------------------------
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	Camera::GetInstance()->Update(deltaTime, e, mGameObjects[1]->GetTransform()->GetPosition());

	//Detect Input
	if ((GetAsyncKeyState('A') & 0x80 != 0)) 
	{
		mGameObjects[1]->GetTransform()->SetPosition({ mGameObjects[1]->GetTransform()->GetPosition().x + deltaTime * 100.0f,mGameObjects[1]->GetTransform()->GetPosition().y,mGameObjects[1]->GetTransform()->GetPosition().z});
	}
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
			Collision::SphereSphereCollision(mGameObjects[i]->GetBoundingSphere(), mGameObjects[j]->GetBoundingSphere());
			
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