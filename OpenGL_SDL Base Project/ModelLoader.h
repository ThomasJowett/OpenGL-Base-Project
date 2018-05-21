#pragma once

#include "Mesh.h"

class ModelLoader
{
public:
	static IndexedModel LoadStaticMesh(const char* filename);
};

