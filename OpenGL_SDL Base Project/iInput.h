#pragma once

class iInput
{
public:
	virtual void MoveRight(float scale) = 0;
	virtual void MoveForward(float scale) = 0;

	virtual void Yaw(float scale) = 0;
	virtual void Pitch(float scale) = 0;
	virtual void Roll(float scale) = 0;

	virtual void Interact() = 0;
};
