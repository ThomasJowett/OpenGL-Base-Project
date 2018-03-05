#pragma once

class iInput
{
	virtual void MoveRight(float deltaTime) = 0;
	virtual void MoveLeft(float deltaTime) = 0;
	virtual void MoveForward(float deltaTime) = 0;
	virtual void MoveBackward(float deltaTime) = 0;
};
