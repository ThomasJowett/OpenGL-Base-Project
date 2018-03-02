#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu() : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000000.0f);

	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	glShadeModel(GL_SMOOTH);

	//glPolygonMode(GL_FRONT, GL_FILL);


	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	splashscreenTextureID = Texture2D::LoadTexture2D("LogoDodgeball.raw", 2048, 2048);

	mControlsText = new TextRender("Fonts/Tabasco.ttf", 16);
}

GameScreenMenu::~GameScreenMenu()
{
}

void GameScreenMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, splashscreenTextureID);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 1, 0, 0);
	glScalef(20.0f, 20.0f, 2.0f);
	DrawTextured2DSquare();
	glPopMatrix();

	mControlsText->DisplayText("WASD to move", SDL_Colour{ 40,10,125 }, 1500, 900);
	mControlsText->DisplayText("R to restart", SDL_Colour{ 62,0,125 }, 1500, 880);
	mControlsText->DisplayText("Get to the far side of the court", SDL_Colour{ 62,0,125 }, 1500, 860);
	mControlsText->DisplayText("You can only be hit by three balls or less", SDL_Colour{ 62,0,125 }, 1500, 840);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	if ((GetAsyncKeyState(VK_RETURN) & 0x80 != 0))
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL1);
}

void GameScreenMenu::DrawTextured2DSquare()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glEnd();
}