#include "JvG.h"
#include "JvJoystick.h"
#include "JvState.h"
#include "JvSave.h"
#include "JvGame.h"
#include "JvSound.h"

JvGame* JvG::jvGameP = NULL;
unsigned int JvG::width;
unsigned int JvG::height;
JvState* JvG::stateP = NULL;
unsigned int JvG::frameRate;
double JvG::elapsed;
double JvG::maxElapsed;
double JvG::timeScale;
JvJoystick* JvG::joystick=NULL;
JvCamera* JvG::camera = NULL;
JvSave* JvG::save=NULL;
bool JvG::pause = false;
JvSound* JvG::sound = NULL;
mINI::INIStructure JvG::ini;

void JvG::setGameData(JvGame* JvGameP,unsigned int Width,
					  unsigned int Height)
{
	JvG::jvGameP = JvGameP;
	width = Width;
	height = Height;

	JvG::frameRate = 60;
	JvG::maxElapsed = 0.0333333f;
	JvG::elapsed = 0;
	timeScale = 1;
	//JvU::roundingError = 0.00001;
}

void JvG::switchState(JvState* StateP)
{
	jvGameP->switchState(StateP);
}

void JvG::playMusic( const char* filename,float Volume/*=1.0f*/ )
{
	sound->playMusic(filename);
}

void JvG::play( const char* filename,float Volume/*=1.0f*/,bool Looped/*=false*/ )
{
	sound->playSound(filename);
}

void JvG::stopMusic()
{
	sound->stopMusic();
}

