#ifndef  _TEXTURE2D_H
#define _TEXTURE2D_H
#include <Windows.h>
#include <gl\GLU.h>
#include "Commons.h"


class Texture2D
{

public:
	Texture2D();
	Texture2D(char* path, int width, int height);
	~Texture2D();

	static GLuint LoadTexture2D(char* path, int width, int height);
};


#endif // ! _TEXTURE2D_H