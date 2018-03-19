#include "GameScreenLevel2.h"



GameScreenLevel2::GameScreenLevel2()
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

	mCamera = new Camera({ 0,0,0 }, 90.0f, -30.0f, 1300.0f);

	//clear background colour.
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);

	//Initialise Root Node
	Root = new SceneNode;
}


GameScreenLevel2::~GameScreenLevel2()
{
	if (Root)  delete Root;
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glEnable(GL_LIGHTING);

	mCamera->Render();
	Root->Traverse();
}

void GameScreenLevel2::Update(float deltaTime, std::vector<SDL_Event> events)
{
	for (auto playerController : mPlayerControllers)
	{
		playerController->Update(deltaTime, events);
	}

	for (auto gameObject : mGameObjects)
	{
		gameObject->Update(deltaTime);
	}

	if ((GetAsyncKeyState(VK_ESCAPE) & 0x80 != 0))
		GameScreenManager::GetInstance()->ChangeScreen(SCREEN_MENU);
}
