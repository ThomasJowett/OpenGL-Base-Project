#pragma once
#include "Shader.h"
class IRenderable
{
	virtual void Render(Shader* shader) = 0;
};
