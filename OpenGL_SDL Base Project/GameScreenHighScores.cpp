#include "GameScreenHighScores.h"

GameScreenHighScores::GameScreenHighScores()
{
	//srand(time(NULL));

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
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	mText= new TextRender("Fonts/Calibri.ttf", 20);
	//mHighScores = LoadHighScores();



	//sprintf(mDisplayTime, "Score: %fs", (100 - (gWinningTime * gBallsHit)));
}

GameScreenHighScores::~GameScreenHighScores()
{
}

void GameScreenHighScores::Render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	
	mText->DisplayText(mDisplayTime, { 0, 0, 0 }, 960, 540, CENTER);
}

void GameScreenHighScores::Update(float deltaTime, std::vector<SDL_Event> events)
{
	HandleInput(events);
}

std::vector<std::string> GameScreenHighScores::LoadHighScores()
{
	return std::vector<std::string>();
}

void GameScreenHighScores::HandleInput(std::vector<SDL_Event> events)
{
	SDL_PumpEvents();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_ESCAPE]) { GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU); return; }
	if (currentKeyStates[SDL_SCANCODE_RETURN]) { GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL2); return; }
	
	for (SDL_Event e : events)
	{
		if (e.type == SDL_CONTROLLERBUTTONDOWN)
		{
			switch (e.cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_A:
				GameScreenManager::GetInstance()->ChangeScreen(SCREEN_LEVEL2); 
				return;
				break;
			case SDL_CONTROLLER_BUTTON_B:
				GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
				return;
				break;
			}
		}
	}
}
