#include "Commons.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


#include "Constants.h"
#include "GameScreenManager.h"
#include "SoundManager.h"



using namespace::std;

//-----------------------------------------------------------------------------------------------------
//Local function prototypes.
bool InitSDL();
void CloseSDL();

void Render();
bool Update();

//-----------------------------------------------------------------------------------------------------
//Globals.
SDL_Window*   gWindow    = NULL;
SDL_GLContext gGLContext = NULL;
Uint32		  gOldTime;
SDL_GameController* gGameControllers[4];

//-----------------------------------------------------------------------------------------------------

int main(int argc, char* args[])
{

	//Initialise SDL.
	if(InitSDL())
	{	
		//Load the music.
		SoundManager::GetInstance()->LoadMusic("Music/HolFix - Stephen Page.mp3");
		
		bool quit = false;
		gOldTime = SDL_GetTicks();

		
		//Game Loop.
		while(!quit)
		{
			quit = Update();
			Render();
		}	
	}

	//Close Window and free resources.
	CloseSDL();

	return 0;
}

//-----------------------------------------------------------------------------------------------------

bool InitSDL()
{	
	//Setup SDL.
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL did not initialise. ERROR: " << SDL_GetError();
		return false;
	}
	else
	{
		//Attempt to set texture filtering to linear.
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not available";
		}

		//All good, so attempt to create the window.
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		gWindow = SDL_CreateWindow("Advanced Game Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		gGLContext = SDL_GL_CreateContext(gWindow);
		//Did the window get created?
		if(gWindow != NULL)
		{
			//Initialise the Mixer.
			if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
			{
				cout << "Mixer could not initialise. ERROR: " << Mix_GetError();
				return false;
			}

			//Setup OpenGL
			GLint GlewInitResult = glewInit();
			if (GLEW_OK != GlewInitResult)
			{
				cerr << "Glew Setup failed. ERROR: " << glewGetErrorString(GlewInitResult) << endl;
				return false;
			}

			glDepthFunc(GL_LEQUAL);
			glDepthRange(0.0f, 1000.0f);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glShadeModel(GL_SMOOTH);
			glPolygonMode(GL_FRONT, GL_FILL);


			//check for number of joysticks
			if (SDL_NumJoysticks() < 1)
			{
				cout << "Warning: No joysticks connected!\n";
			}
			else
			{
				//load game controllers
				for (int i = 0; i < SDL_NumJoysticks(); i++)
				{
					gGameControllers[i] = SDL_GameControllerOpen(i);
					if (gGameControllers[i] == NULL)
					{
						std::cerr << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError();
					}
				}
			}
		}
		else
		{
			//Nope.
			cerr << "Window was not created. ERROR: " << SDL_GetError();
			return false;
		}
		
	}

	return true;
}

//-----------------------------------------------------------------------------------------------------

void CloseSDL()
{
	//Destroy the game screen manager.
	delete GameScreenManager::GetInstance();
	delete SoundManager::GetInstance();

	//Close game controllers
	for (auto controller : gGameControllers)
	{
		SDL_GameControllerClose(controller);
	}

	//Destroy the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_GL_DeleteContext(gGLContext);
	gGLContext = NULL;

	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

//-----------------------------------------------------------------------------------------------------

void Render()
{
	glClearColor(0, 0, 0, 1);
	GameScreenManager::GetInstance()->Render();

	//Update the screen.
	SDL_GL_SwapWindow(gWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-----------------------------------------------------------------------------------------------------

bool Update()
{
	//Get the new time.
	Uint32 newTime = SDL_GetTicks();

	//Event Handler.
	SDL_Event e;

	vector<SDL_Event>events;

	//Get the events.
	while (SDL_PollEvent(&e) != 0)
	{
		events.push_back(e);
	}

	GameScreenManager::GetInstance()->Update((float)(newTime - gOldTime) / 1000.0f, events);

	//Handle quiting.
	for (auto e : events)
	{
		if (e.type == SDL_QUIT)
			return true;

		//play music with m key
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_m)
				SoundManager::GetInstance()->PlayMusic("Music/HolFix - Stephen Page.mp3");				
		}
	}
	

	//Set the current time to be the old time.
	gOldTime = newTime;

	return false;
}

//-----------------------------------------------------------------------------------------------------