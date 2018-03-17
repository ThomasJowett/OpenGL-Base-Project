#ifndef _IMAGERENDER_H
#define _IMAGERENDER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Commons.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include "Constants.h"

class ImageRender
{
public:
	ImageRender(std::string path);
	~ImageRender();

	void LoadImage(std::string path);
	void DrawImage(int positionX, int positionY, float sizeX, float sizeY);
private:
	SDL_Surface* mSurface;
};

#endif // !_IMAGERENDER_H