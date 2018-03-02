#include "SoundEffects.h"

SoundEffects::SoundEffects(std::string path)
{
	LoadFromFile(path);
}

SoundEffects::~SoundEffects()
{
	Mix_FreeChunk(mSound);
	mSound = NULL;
}

void SoundEffects::Play(int channel, int repeat)
{
	Mix_PlayChannel(channel, mSound, repeat);
}

void SoundEffects::LoadFromFile(std::string path)
{
	mSound = Mix_LoadWAV(path.c_str());
	if (mSound == NULL)
	{
		std::cerr << "Failed to load Sound Effect! Error: " << Mix_GetError() << std::endl;
	}
}
