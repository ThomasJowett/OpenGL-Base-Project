#ifndef _GAMESCREENHIGHSCORES_H
#define _GAMESCREENHIGHSCORES_H



#include <SDL.h>
#include "GameScreen.h"
#include "TextRender.h"

class GameScreenHighScores : public GameScreen
{
public:
	GameScreenHighScores();
	~GameScreenHighScores();

	void Render()override;
	void Update(float deltaTime, std::vector<SDL_Event>events)override;
private:
	TextRender* mText;
	std::vector<std::string> LoadHighScores();
protected:
	void HandleInput(std::vector<SDL_Event > events);
	std::vector<std::string> mHighScores;
	std::vector<std::string> mTitles;
};

#endif // !_GAMESCREENHIGHSCORES_H