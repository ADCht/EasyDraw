#include "audio.h"

Mix_Music *ED_Audio::bgm = 0;
int ED_Audio::se_channel = 0;

void ED_Audio::bgm_play(const char* filename, int volume, int pitch, int pos)
{
	bgm = Mix_LoadMUS(filename);
	Mix_VolumeMusic(volume * 1.28);
	Mix_PlayMusic(bgm, -1);
}

void ED_Audio::bgm_stop()
{
	Mix_FreeMusic(bgm);
}

void ED_Audio::bgm_fade(int time)
{
	Mix_FadeOutMusic(time);
}

void ED_Audio::bgs_play(const char* filename, int volume, int pitch, int pos)
{

}

void ED_Audio::bgs_stop()
{

}

void ED_Audio::bgs_fade(int time)
{

}

void ED_Audio::me_play(const char* filename, int volume, int pitch)
{

}

void ED_Audio::me_stop()
{

}

void ED_Audio::me_fade(int time)
{

}

void ED_Audio::se_play(const char* filename, int volume, int pitch)
{
	se_channel = Mix_PlayChannel(-1, Mix_LoadWAV(filename), 0);
	Mix_Volume(se_channel, volume * 1.28);
}

void ED_Audio::se_stop()
{
	if (se_channel)
		Mix_HaltChannel(se_channel);
}
