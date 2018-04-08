#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Constants.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "SoundManager.h"

using namespace::std;

//-----------------------------------------------------------------------------------------------------
//Local function prototypes.
bool InitSDL();
SDL_Surface* LoadSurface(string path);
void CloseSDL();

void Render();
bool Update();

//-----------------------------------------------------------------------------------------------------
//Globals.
SDL_Window*   gWindow    = NULL;
SDL_GLContext gGLContext = NULL;
SDL_Surface*  gSurface   = NULL;
Uint32		  gOldTime;
SDL_GameController* gGameController = NULL;
float gWinningTime = FLT_MAX;
int gNull;
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
		cout << "SDL did not initialise. Error: " << SDL_GetError();
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
		gWindow = SDL_CreateWindow("Advanced Game Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		gGLContext = SDL_GL_CreateContext(gWindow);
		//Did the window get created?
		if(gWindow != NULL)
		{
			//Initialise the Mixer.
			if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
			{
				cout << "Mixer could not initialise. Error: " << Mix_GetError();
				return false;
			}
		}
		else
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		//check for number of joysticks
		if (SDL_NumJoysticks() < 1)
		{
			cout << "Warning: No joysticks connected!\n";
		}
		else
		{
			//load game controllers
			gGameController = SDL_GameControllerOpen(0);
			if (gGameController == NULL)
			{
				cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError();
			}
		}
	}

	return true;
}

//-----------------------------------------------------------------------------------------------------

SDL_Surface* LoadSurface(string path)
{
	SDL_Surface* pLoadedSurface = NULL;
	SDL_Surface* pOptimizedSurface = NULL;

	//Load the image.
	pLoadedSurface = IMG_Load(path.c_str());
	if(pLoadedSurface == NULL)
	{
		cout << "Failed to load image. Error: " << SDL_GetError();
		return NULL;
	}
	else
	{
		//Convert the surface to the screen format.
		pOptimizedSurface = SDL_ConvertSurface( pLoadedSurface, gSurface->format, NULL);
		if(pOptimizedSurface == NULL)
		{
			cout << "Unable to optimize the surface. Error: " << SDL_GetError();
			return NULL;
		}

		//Free the memory used for the loaded surface.
		SDL_FreeSurface(pLoadedSurface);
	}

	return pOptimizedSurface;
}

//-----------------------------------------------------------------------------------------------------

void CloseSDL()
{
	//Destroy the game screen manager.
	delete GameScreenManager::GetInstance();

	//Close game controller
	SDL_GameControllerClose(gGameController);
	gGameController = NULL;

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
	GameScreenManager::GetInstance()->Render();

	//Update the screen.
	SDL_GL_SwapWindow(gWindow);
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