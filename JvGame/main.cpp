#include <stdio.h>
#include <SDL.h>
#include <map>
#include "JvGame/JvGame.h"
#include "JvGame/JvState.h"
#include "TestState.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
	JvGame jvgame(SCREEN_WIDTH, SCREEN_HEIGHT);
	jvgame.setInitState(new TestState);
	jvgame.run();

	while (!jvgame.quit())
	{
		jvgame.update();
	}
	return 0;
}