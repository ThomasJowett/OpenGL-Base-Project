#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Camera.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	//pyramid = new Pyramid();
	//rotation = 0.0f;

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
	m_p3DSModel = new GameObject(Vector3D(0.0f, 50.0f, 0.0f), "Car_Backfire.3DS","3DS");

	m_pOBJTracks = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "Tracks.obj", "OBJ");
	m_pOBJTracks->LoadTexture("Tracks_Diffuse.raw", 1024, 1024);

	m_pOBJCabin = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "Cabin.obj", "OBJ");
	m_pOBJCabin->LoadTexture("Cabin_Diffuse.raw", 1024, 1024);

	m_pOBJBoom = new GameObject(Vector3D(0.0f, 0.0f, 60.0f), "Boom.obj", "OBJ");
	m_pOBJBoom->LoadTexture("Boom_Diffuse.raw", 1024, 1024);

	m_pOBJStick = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "Stick.obj", "OBJ");
	m_pOBJStick->LoadTexture("Stick_Diffuse.raw", 1024, 1024);
	
	m_pOBJBucket = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "Bucket.obj", "OBJ");
	m_pOBJBucket->LoadTexture("Bucket_Diffuse.raw", 1024, 1024);

	m_pOBJGround = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "Ground.obj", "OBJ");
	m_pOBJGround->LoadTexture("Grass_Diffuse.raw", 1024, 1024);

	m_pOBJTreeTrunk = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "TreeTrunk.obj", "OBJ");
	m_pOBJTreeTrunk->LoadTexture("Bark_Diffuse.raw", 1024, 1024);

	m_pOBJTreeLeaves = new GameObject(Vector3D(0.0f, 0.0f, 0.0f), "TreeLeaves.obj", "OBJ");
	m_pOBJTreeLeaves->LoadTexture("Leaves_Diffuse.raw", 1024, 1024);

	//Initialise Transformations
	m_pTracksTrans = new Transformation;
	m_pCabinTrans = new Transformation;
	m_pBoomTrans = new Transformation;
	m_pStickTrans = new Transformation;
	m_pBucketTrans = new Transformation;	
	m_pTreeTrans = new Transformation;
	m_pTreeLeavesTrans = new Transformation;

	m_pTreeTrans->SetValue(TRANSLATION, 1000, -100, 1000, 1);
	m_pTreeLeavesTrans->SetValue(TRANSLATION, 0, 0, 0, 1);

	//Set the objects transforms
	m_pOBJTracks->SetTransform(m_pTracksTrans);
	m_pOBJCabin->SetTransform(m_pCabinTrans);
	m_pOBJBoom->SetTransform(m_pBoomTrans);
	m_pOBJStick->SetTransform(m_pStickTrans);
	m_pOBJBucket->SetTransform(m_pBucketTrans);
	m_pOBJTreeTrunk->SetTransform(m_pTreeTrans);
	m_pOBJTreeLeaves->SetTransform(m_pTreeLeavesTrans);

	//Set the Relationships
	m_pOBJTracks->AddChild(m_pOBJCabin);
	m_pOBJCabin->AddChild(m_pOBJBoom);
	m_pOBJBoom->AddChild(m_pOBJStick);
	m_pOBJStick->AddChild(m_pOBJBucket);

	m_pOBJTreeTrunk->AddChild(m_pOBJTreeLeaves);

	//Initialise Root Node
	Root = new SceneNode;

	Root->AddChild(m_pOBJTracks);
	Root->AddChild(m_pOBJTreeTrunk);

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
	
	mCabinRotation = 0.0f;
	mBoomRotation = 0.0f;
	mStickRotation = 0.0f;
	mBucketRotation = 0.0f;
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

void GameScreenLevel1::SetMaterial() {
	Material material = {
		{ 0.20f, 0.2f, 0.2f, 1.0f },
		{ 0.40f, 0.40f, 0.4f, 1.0f },
		{ 0.8f, 0.8f, 0.8f, 1.0f },
		50.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}


GameScreenLevel1::~GameScreenLevel1()
{	
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

void GameScreenLevel1::OutputLine(float x, float y, string text)
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
	/*gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);*/
		
	Camera::GetInstance()->Render();
	SetLight();
	SetMaterial();
	/*
	//Render a Pyramid
	glPushMatrix();
	glRotatef(rotation, 1, 1, 1);
	glScalef(5.0f, 5.0f, 5.0f);
	pyramid->Draw();
	glPopMatrix();
	*/

	m_pOBJGround->Render();

	//glutSolidSphere(40,100,100);

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
	Camera::GetInstance()->Update(deltaTime, e, m_pOBJCabin->GetPosition());

	//Detect Input
	if ((GetAsyncKeyState('A') & 0x80 != 0))
		mCabinRotation += mMoveSpeed;
	if ((GetAsyncKeyState('D') & 0x80 != 0))
		mCabinRotation -= mMoveSpeed;
	if ((GetAsyncKeyState('W') & 0x80 != 0))
		mStickRotation -= mMoveSpeed;
	if ((GetAsyncKeyState('S') & 0x80 != 0))
		mStickRotation += mMoveSpeed;
	if ((GetAsyncKeyState('Q') & 0x80 != 0))
		mBoomRotation -= mMoveSpeed;
	if ((GetAsyncKeyState('E') & 0x80 != 0)) 
		mBoomRotation += mMoveSpeed;
	if ((GetAsyncKeyState('R') & 0x80 != 0))
		mBucketRotation -= mMoveSpeed;
	if ((GetAsyncKeyState('F') & 0x80 != 0))
		mBucketRotation += mMoveSpeed;

	//Clamp Values
	if (mCabinRotation > 360 || mCabinRotation < -360)
		mCabinRotation = 0;

	if (mBoomRotation < -25)
		mBoomRotation = -25;
	if (mBoomRotation > 80)
		mBoomRotation = 80;

	if (mStickRotation > 20) 
		mStickRotation = 20;
	if (mStickRotation < -100)
		mStickRotation = -100;

	if (mBucketRotation > 90)
		mBucketRotation = 90;
	if (mBucketRotation < -90)
		mBucketRotation = -90;


	//Update the Transforms
	m_pTracksTrans->SetValue(ROTATION, 0, 0, 0, 0, 0);
	m_pTracksTrans->SetValue(TRANSLATION, 0, 0, 0, 1);

	m_pCabinTrans->SetValue(ROTATION, mCabinRotation, 0, 1, 0, 0);
	m_pCabinTrans->SetValue(TRANSLATION, 0, 100, 0, 1);

	m_pBoomTrans->SetValue(ROTATION, mBoomRotation, 1, 0, 0, 0);
	m_pBoomTrans->SetValue(TRANSLATION, 0, -50, 60, 1);

	m_pStickTrans->SetValue(ROTATION, mStickRotation, 1, 0, 0, 0);
	m_pStickTrans->SetValue(TRANSLATION, 8, 280, 360, 1);

	m_pBucketTrans->SetValue(ROTATION, mBucketRotation, 1, 0, 0, 0);
	m_pBucketTrans->SetValue(TRANSLATION, -8, -280, -60, 1);


	//Display FPS
	mFrameCount++;
	mFinalTime = time(NULL);
	if (mFinalTime - mInitialTime >= 1)
	{
		
		FPS = "FPS: " + std::to_string(mFrameCount / (mFinalTime - mInitialTime));
		mFrameCount = 0;
		mInitialTime = mFinalTime;
	}

	mCurrentTime += deltaTime;
	//rotation += 1.0f;
}
//--------------------------------------------------------------------------------------------------