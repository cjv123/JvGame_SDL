#include <stdio.h>
#include <SDL.h>
#include <map>
#include "JvGame/JvGame.h"
#include "JvGame/JvState.h"
#include "LogoState.h"
#include "GameState.h"
#include "TestState.h"


int main(int argc, char* argv[])
{
	JvGame jvgame(320, 240,2);
	jvgame.setInitState(new GameState);
	jvgame.run();

	while (!jvgame.quit())
	{
		jvgame.update();
	}
	return 0;
}