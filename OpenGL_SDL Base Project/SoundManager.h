#ifndef _SOUNDMANAGER_H
#define	_SOUNDMANAGER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Vector.h"

class SoundManager
{
public:
	~SoundManager();

	static SoundManager * GetInstance()
	{
		if (instance == 0)
		{
			instance = new SoundManager();
		}
		return instance;
	}

	void PlayMusic(const std::string& filename);
	void PauseMusic();
	void StopMusic();
	bool PlaySoundEffect(const std::string filename, int channel, int repeat );
	bool PlaySoundAtLocation(const std::string filename, int channel, int repeat, Vector3D location);
	void LoadMusic(std::string filename);
	bool LoadSoundEffect(std::string filename);

private:
	static std::string mCurrentMusicFilename;
	Mix_Music* mMusic;

	static SoundManager * instance;

	struct soundEffect
	{
		std::string filename;
		Mix_Chunk* sound;
	};

	std::map<std::string, Mix_Chunk* > mSoundEffects;

	static void InitAudioDevice();

	SoundManager();
	
};
#endif