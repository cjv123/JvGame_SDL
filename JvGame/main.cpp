#include <stdio.h>
#include <SDL.h>
#include <map>
#include "JvGame/JvGame.h"
#include "JvGame/JvState.h"
#include "LogoState.h"
#include "GameState.h"
#include "HomeState.h"
#include "TestState.h"
#include "JvGame/ini.h"

int main(int argc, char* argv[])
{
    mINI::INIFile configFile("config.ini");
    configFile.read(JvG::ini);
    int width = atoi(JvG::ini["display"]["width"].c_str());
    int height = atoi(JvG::ini["display"]["height"].c_str());
    float scale = atof(JvG::ini["display"]["scale"].c_str());
    width=width?width:320;
    height=height?height:240;
    scale=scale?scale:2;

	JvGame jvgame(width,height,scale);
	jvgame.setInitState(new LogoState);
	jvgame.run();

	while (!jvgame.quit())
	{
		jvgame.update();
	}
	return 0;
}