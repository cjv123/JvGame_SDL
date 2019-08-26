#include <stdio.h>
#include <SDL.h>
#include <map>
#include "JvGame/JvGame.h"
#include "JvGame/JvState.h"
#include "LogoState.h"
#include "GameState.h"
#include "HomeState.h"
#include "TestState.h"


int main(int argc, char* argv[])
{
	JvGame jvgame(320, 240,1);
	jvgame.setInitState(new LogoState);
	jvgame.run();

	while (!jvgame.quit())
	{
		jvgame.update();
	}
	return 0;
}