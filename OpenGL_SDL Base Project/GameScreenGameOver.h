#ifndef _GAMESCREENGAMEOVER_H
#define _GAMESCREENGAMEOVER_H

#include "GameScreen.h"
#include "TextRender.h"

class GameScreenGameOver : public GameScreen
{
public:
	GameScreenGameOver();
	~GameScreenGameOver();

	void Render() override;
	void Update(float deltaTime, std::vector<SDL_Event> events) override;
private:
	TextRender* mText;
	float mTimer;
};

#endif // !_GAMESCREENGAMEOVER_H