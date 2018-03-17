#ifndef _TEXTRENDER_H
#define _TEXTRENDER_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Commons.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include "Constants.h"
enum ALIGNMENT
{
	CENTER = 0,
	RIGHT,
	LEFT
};
class TextRender
{
public:
	TextRender(std::string path, int pointSize);
	~TextRender();

	void LoadFont(std::string path, int pointSize);
	void DisplayText(const char* text, SDL_Colour text_colour, int x, int y, ALIGNMENT alignment);

private:
	TTF_Font * mFont;
};
#endif // !_TEXTRENDER_H
