#include <stdio.h>
#include <SDL.h>
#include <map>
#include "JvGame/JvGame.h"
#include "JvGame/JvState.h"
#include "LogoState.h"
#include "GameState.h"
#include "HomeState.h"
#include "TestState.h"
#include "ini.h"

int main(int argc, char* argv[])
{
    mINI::INIFile file("config.ini");
    mINI::INIStructure  ini;
    file.read(ini);
    std::string width = ini["display"]["width"];
    std::string height = ini["display"]["height"];
    std::string scale = ini["display"]["scale"];

	JvGame jvgame(atoi(width.c_str()), atoi(height.c_str()),atof(scale.c_str()));
	jvgame.setInitState(new LogoState);
	jvgame.run();

	while (!jvgame.quit())
	{
		jvgame.update();
	}
	return 0;
}