/*************************************************************/
//							Audio.h
/*************************************************************/
#include "Globals.h"
#pragma once;

class SDLAudio
{
private:
public:
	bool initAudio();
	Mix_Chunk* loadWaveFiles(Mix_Chunk* , char *);
	Mix_Music* loadMusicFiles(Mix_Music* , char *);
	void playMusic(Mix_Music *);
	void playWave(Mix_Chunk *);
	void stopPlayingMusic();
};