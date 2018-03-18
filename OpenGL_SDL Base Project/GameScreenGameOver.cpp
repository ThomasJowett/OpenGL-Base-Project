#include "GameScreenGameOver.h"

GameScreenGameOver::GameScreenGameOver()
{
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

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	mText = new TextRender("Fonts/Dimbo regular.ttf", 72);

	mTimer = 3.0f;
}


GameScreenGameOver::~GameScreenGameOver()
{
}

void GameScreenGameOver::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	mText->DisplayText("GAME OVER", SDL_Colour{ 255, 255, 255 }, 960, 540, CENTER);
}

void GameScreenGameOver::Update(float deltaTime, std::vector<SDL_Event> events)
{
	mTimer -= deltaTime;
	if (mTimer <0.0f)
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
}
