#include "TextRender.h"



TextRender::TextRender(std::string path, int pointSize)
{
	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
	}

	LoadFont(path, pointSize);
}


TextRender::~TextRender()
{
}

void TextRender::LoadFont(std::string path, int pointSize)
{
	mFont = TTF_OpenFont(path.c_str(), pointSize);
	if (mFont == NULL)
	{
		std::cerr << "TTF_OpenFont()Failed: " << TTF_GetError() << std::endl;
	}
}

void TextRender::DisplayText(const char* text, SDL_Colour text_colour, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SDL_Surface * surface;
	surface = TTF_RenderText_Blended(mFont, text, text_colour);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1); glVertex2f(x, y);
		glTexCoord2f(1, 1); glVertex2f(x + surface->w, y);
		glTexCoord2f(1, 0); glVertex2f(x + surface->w, y + surface->h);
		glTexCoord2f(0, 0); glVertex2f(x, y + surface->h);
	}
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDeleteTextures(1, &texture);
	SDL_FreeSurface(surface);
}

