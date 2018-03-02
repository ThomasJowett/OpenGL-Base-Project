#ifndef _SOUNDEFFECTS_H
#define _SOUNDEFFECTS_H

#include <SDL_mixer.h>
#include <SDL.h>
#include <string>
#include <iostream>

class SoundEffects
{
public:
	SoundEffects(std::string path);
	~SoundEffects();

	void Play(int channel, int repeat);
	void LoadFromFile(std::string path);

private:
	Mix_Chunk* mSound;

};

#endif // !_SOUNDEFFECTS_H