#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include "JvGame.h"
#include "JvState.h"
#include "JvSave.h"


JvGame::JvGame()
{
	JvG::save = new JvSave;
	JvG::joystick = new JvJoystick;

	_run=false;
	_delState = NULL;
}


JvGame::JvGame(unsigned int GameSizeX,unsigned int GameSizeY)
{
// 	JvG::save = new JvSave;
// 	JvG::joystick = new JvJoystick;

	JvG::setGameData(this,GameSizeX,GameSizeY);
	_run = false;
	_delState = NULL;
	_switchState = NULL;
}

JvGame::~JvGame()
{
	if (JvG::stateP != NULL)
	{
		delete JvG::stateP;
	}

	delete JvG::save;
	delete JvG::joystick;

	if (_SDLRenderer) 
	{
		SDL_DestroyRenderer(_SDLRenderer);
	}
	
	if (_SDLWindow)
	{
		SDL_DestroyWindow(_SDLWindow);
	}

}

void JvGame::setInitState(JvState* initState)
{
	_switchState = initState;
}

void JvGame::setScreenInfo(unsigned int Width,unsigned int Height)
{
	JvG::setGameData(this,Width,Height);
}

void JvGame::run()
{
	create();
	_run = true;
}

void JvGame::stopRun()
{
	_run = false;
}

void JvGame::switchState(JvState* StateP)
{
	
	_switchState = StateP;

}

void JvGame::create()
{
	JvU::setWorldBounds(0,0,JvG::width,JvG::height);	

	bool success = true;
	//Create window
	_SDLWindow = SDL_CreateWindow("JvGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, JvG::width, JvG::height, SDL_WINDOW_SHOWN);
	if (_SDLWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create renderer for window
		_SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_ACCELERATED);
		if (_SDLRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize renderer color
			//SDL_SetRenderDrawColor(_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}

	assert(success);
}

bool JvGame::update()
{
	if (!_run) return false;

	uint32_t last_tick_time = 0;
	uint32_t delta = 0;
	uint32_t tick_time = SDL_GetTicks();
	delta = tick_time - last_tick_time;
	JvG::elapsed = delta;
	last_tick_time = tick_time;

	//Frame timing
	if(JvG::elapsed > JvG::maxElapsed)
	{
		JvG::elapsed = JvG::maxElapsed;
	}
	
//	JvG::elapsed = 1.0f/JvG::frameRate;

	JvG::elapsed *= JvG::timeScale;

	//printf("%f\n",JvG::elapsed);

	if (_switchState!=NULL)
	{
		if(JvG::stateP!=NULL)
			delete JvG::stateP;

		JvG::stateP = _switchState;
		JvG::stateP->loading();
		JvG::stateP->render();
		JvG::stateP->defaultGroup->kill();
		JvG::stateP->defaultGroup->exists = true;
		JvG::stateP->defaultGroup->dead = false;
		JvG::stateP->create();
		_switchState = NULL;
		//JvG::joystick->reSet();
	}

	if (JvG::stateP != NULL)
	{
		JvG::stateP->update();
		JvG::stateP->render();
	}
	//JvG::joystick->update();

	return true;
}

void JvGame::btnDown(KEYCODE keycode)
{
	JvG::joystick->pressDown(keycode);
}


void JvGame::btnUp(KEYCODE keycode)
{
	JvG::joystick->pressUp(keycode);
}

void JvGame::mouseClick(int type,int x,int y)
{
	switch (type) {
	case 0:
		JvG::joystick->mouseUp(x,y);
		break;
	case 1:
		JvG::joystick->mouseDown(x,y);
		break;
	default:
		break;
	}
}

void JvGame::mouseMove(int x,int y)
{
	JvG::joystick->mouseMove(x,y);
}

SDL_Window* JvGame::getSDLWindow()
{
	return _SDLWindow;
}

SDL_Renderer* JvGame::getSDLRenderer()
{
	return _SDLRenderer;
}

void JvGame::exit()
{
	
}
