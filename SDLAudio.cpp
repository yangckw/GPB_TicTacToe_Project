#include "SDLAudio.h"

bool SDLAudio::initAudio()
{
	int success = true;

	// Audio initalilize
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: \n", Mix_GetError();
		success = false;
	}
	return success;
}

 Mix_Chunk* SDLAudio::loadWaveFiles(Mix_Chunk *wave, char *name)
{
	wave = Mix_LoadWAV(name);
	return wave;
}

Mix_Music* SDLAudio::loadMusicFiles(Mix_Music* music, char *name)
{
	music = Mix_LoadMUS(name);
	return music;
}

void SDLAudio::playMusic(Mix_Music *music)
{
	if (Mix_PlayingMusic() == 0) { Mix_PlayMusic(music, -1); }
}

void SDLAudio::playWave(Mix_Chunk *wave)
{
	Mix_PlayChannel(-1, wave, 0);
}

void SDLAudio::stopPlayingMusic() { Mix_HaltMusic(); }