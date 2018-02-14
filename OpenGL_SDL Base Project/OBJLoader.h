#ifndef _OBJLOADER_H
#define _OBJLOADER_H

#include "Commons.h"

class OBJLoader
{
public:
	static MeshData LoadOBJ(char *filename);
};
//extern MeshData LoadOBJ(char *filename);

#endif