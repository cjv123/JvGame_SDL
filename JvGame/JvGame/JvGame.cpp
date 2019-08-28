#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <assert.h>
#include "JvGame.h"
#include "JvState.h"
#include "JvSave.h"
#include "JvSound.h"

JvGame::JvGame()
{
	JvG::save = new JvSave;
	JvG::joystick = new JvJoystick;
	JvG::sound = new JvSound;

	_run=false;
	_quit = false;

	_delState = NULL;
	_switchState = NULL;
	_SDLRenderer = NULL;
	_SDLWindow = NULL;
	_gameScale = 1;
}


JvGame::JvGame(unsigned int GameSizeX, unsigned int GameSizeY, float gameScale) :JvGame()
{
	_gameScale = gameScale;
	JvG::setGameData(this,GameSizeX,GameSizeY);
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		_SDLWindow = SDL_CreateWindow("JvGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			JvG::width*_gameScale, JvG::height*_gameScale, SDL_WINDOW_SHOWN);
		if (_SDLWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
			//Create renderer for window
			_SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (_SDLRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				//SDL_SetRenderDrawColor(_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_Rect rendererRect{0,0,JvG::width*_gameScale,JvG::height*_gameScale};
				SDL_RenderSetViewport(_SDLRenderer,&rendererRect);
				SDL_RenderSetLogicalSize(_SDLRenderer, JvG::width,JvG::height);
				SDL_RenderSetScale(_SDLRenderer,_gameScale,_gameScale);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() < 0)
				{
					printf("sdl_ttf init fail:%s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}


	assert(success);

}

static SDL_Event e;
static const unsigned int FPS = 1000 / 60;
static unsigned int _FPS_Timer = 0;

static uint32_t last_tick_time = 0;

bool JvGame::update()
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
			_quit = true;
		}

		if (JvG::joystick)
		{
			JvG::joystick->updateSDLInput(e);
		}
	}


	if (!_run) return false;

	uint32_t delta = 0;
	uint32_t tick_time = SDL_GetTicks();
	delta = tick_time - last_tick_time;
	JvG::elapsed = delta/1000.0f;
	//Frame timing
	if(JvG::elapsed > JvG::maxElapsed)
	{
		JvG::elapsed = JvG::maxElapsed;
	}
	last_tick_time = tick_time;

	
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
		JvG::joystick->reSet();
	}

	if (JvG::stateP != NULL)
	{
		JvG::stateP->update();
		JvG::stateP->render();
	}
	JvG::joystick->update();

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

bool JvGame::quit()
{
	return _quit;
}

float JvGame::getGameScale()
{
	return _gameScale;
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
