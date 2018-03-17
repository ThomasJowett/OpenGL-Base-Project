#include "ImageRender.h"

ImageRender::ImageRender(std::string path)
{
	LoadImage(path);
}

ImageRender::~ImageRender()
{
	SDL_FreeSurface(mSurface);
}

void ImageRender::LoadImage(std::string path)
{
	//SDL_FreeSurface(mSurface);

	mSurface = IMG_Load(path.c_str());

	if (mSurface != NULL)
	{
		SDL_SetColorKey(mSurface, SDL_TRUE, SDL_MapRGB(mSurface->format, 0, 0xFF, 0xFF));
	}
	else
	{
		mSurface = IMG_Load("Images/NULL.png");
		std::cerr << "Unable to create Image. Error: " << SDL_GetError() << std::endl;
	}
}

void ImageRender::DrawImage(int x, int y, float sizeX, float sizeY)
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSurface->w, mSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mSurface->pixels);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1); glVertex2f(x, y);
		glTexCoord2f(1, 1); glVertex2f(x + sizeX, y);
		glTexCoord2f(1, 0); glVertex2f(x + sizeX, y + sizeY);
		glTexCoord2f(0, 0); glVertex2f(x, y + sizeY);
	}
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDeleteTextures(1, &texture);
}
