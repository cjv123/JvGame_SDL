#include "JvSound.h"

JvSound::JvSound() : _musicBuf(NULL)
{

}

JvSound::~JvSound()
{
}

Mix_Chunk* JvSound::addSoundBuf(const std::string& filename)
{
	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
	if (sound == NULL)
	{
		printf("load sound file:%s fail!,SDL_mixer Error: %s\n",filename.c_str(),Mix_GetError());
	}
	else
	{
		_soundBufMap.insert(SoundBufMap::value_type(filename,sound));
	}

	return sound;
}

void JvSound::removeSoundBuf(const std::string& filename)
{
	SoundBufMap::iterator it = _soundBufMap.find(filename);
	if (it != _soundBufMap.end())
	{
		Mix_FreeChunk(it->second);
		_soundBufMap.erase(it);
	}
}

void JvSound::clearSoundBuf()
{
	for (SoundBufMap::iterator it = _soundBufMap.begin(); it != _soundBufMap.end();it++) 
	{
		Mix_FreeChunk(it->second);
	}

	_soundBufMap.clear();
}

void JvSound::playSound(const std::string& filename)
{
	Mix_Chunk* sound=NULL;
	SoundBufMap::iterator it = _soundBufMap.find(filename);
	if (it==_soundBufMap.end())
	{
		sound = addSoundBuf(filename);
	}
	else 
	{
		sound = it->second;
	}

	if (sound != NULL)
	{
		Mix_PlayChannel(-1, sound, 0);
	}
}

void JvSound::playMusic(const std::string& filename)
{
	if (_musicBuf != NULL)
	{
		Mix_FreeMusic(_musicBuf);
		_musicBuf = NULL;
	}

	_musicBuf = Mix_LoadMUS(filename.c_str());
	if (_musicBuf == NULL)
	{
		printf("Failed to load music:%s! SDL_mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}
	else 
	{
		Mix_PlayMusic(_musicBuf,-1);
	}
}

void JvSound::stopMusic()
{
	if (_musicBuf != NULL)
	{
		Mix_HaltMusic();
	}
}



