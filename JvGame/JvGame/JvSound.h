#ifndef _JVSOUND_H_
#define _JVSOUND_H_

#include <string>
#include <map>
#include <SDL_mixer.h>

typedef std::map<std::string, Mix_Chunk*> SoundBufMap;

class JvSound
{
public:
	JvSound();
	~JvSound();

	Mix_Chunk* addSoundBuf(const std::string& filename);
	void removeSoundBuf(const std::string& filename);
	void clearSoundBuf();

	void playSound(const std::string& filename);
	void playMusic(const std::string& filename);
	void stopMusic();

private:
	SoundBufMap _soundBufMap;

	std::string _curMusicName;
	Mix_Music* _musicBuf;
};

#endif
