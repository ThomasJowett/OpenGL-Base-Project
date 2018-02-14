#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu() : GameScreen()
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

	//clear background colour.
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

GameScreenMenu::~GameScreenMenu()
{
	std::cout << "MenuDestructor\n";
}

void GameScreenMenu::Render()
{
	//std::cout << "Rendering in Menu\n";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glColor3f(0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(50, 50, "Main Menu");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	//std::cout << "Updating in Menu\n";
	if ((GetAsyncKeyState(VK_RETURN) & 0x80 != 0))
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL1);
}

void GameScreenMenu::OutputLine(float x, float y, std::string text)
{
	glRasterPos2f(x, y); //where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}