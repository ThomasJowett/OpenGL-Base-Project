#ifndef  _TEXTURE2D_H
#define _TEXTURE2D_H
#include <Windows.h>
#include <gl\GLU.h>
#include "Commons.h"


class Texture2D
{
private:
	//const GLsizei num_textures = 50;
	GLuint _ID;
	//GLuint *textures = new GLuint[num_textures];//Texture ID's array
	int _width, _height;

public:

	

	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return _ID; }
	//GLuint GetID() const { return textures[_ID]; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
};


#endif // ! _TEXTURE2D_H