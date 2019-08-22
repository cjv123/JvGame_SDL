#include <stdio.h>
#include <SDL.h>
#include "JvGame/JvGame.h"
#include "JvGame/JvState.h"
#include "TestState.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		JvGame jvgame(SCREEN_WIDTH,SCREEN_HEIGHT);
		jvgame.setInitState(new TestState);
		jvgame.run();

		bool quit = false;
		SDL_Event e;

		const unsigned int FPS = 1000 / 60;
		unsigned int _FPS_Timer=0;

		while (!quit)
		{
			if (SDL_GetTicks() - _FPS_Timer < FPS) {
				SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
			}
			_FPS_Timer = SDL_GetTicks();

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

			}
			jvgame.update();
		}
	}

	return 0;
}