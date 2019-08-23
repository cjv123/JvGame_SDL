#include "JvState.h"
#include "JvText.h"
#include "JvGame.h"

JvState::JvState() : camera(NULL),defaultGroup(NULL)
{
	_bgColor =0;

	if (NULL == camera)
	{
		camera = new JvCamera;
		JvG::camera = camera;
	}

	if (NULL == defaultGroup)
	{
		defaultGroup = new JvGroup;
	}

}

JvState::~JvState()
{
	if (camera)
		delete camera;

	if (defaultGroup)
		delete defaultGroup;

}

void JvState::create()
{
	camera->init(JvG::width,JvG::height);

}

void JvState::update()
{
	if (JvG::pause)
	{
		pause();
		return;
	}

	defaultGroup->update();
	camera->update();
}

void JvState::render()
{
	
	if (JvG::jvGameP) 
	{
		SDL_Renderer* renderer = JvG::jvGameP->getSDLRenderer();
		if (renderer) 
		{
			//Clear screen
			//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			if (_bgColor != 0)
			{
				//m_ccbglayer->visit();
			}
			defaultGroup->render();
			camera->renderFlash();


			//Update screen
			SDL_RenderPresent(renderer);

		}
	
	}

}

void JvState::collide()
{
	JvU::collide(defaultGroup,defaultGroup);
}

void JvState::add(JvObject* ObjectP)
{
	defaultGroup->add(ObjectP);
}

void JvState::setBgColor(int Color)
{
	_bgColor = Color;
	int r,g,b,a;
	GET_RGBA_8888(Color,r,g,b,a);
}

void JvState::pause()
{

}

void JvState::loading()
{
	JvText* loadtxt = new JvText(25,JvG::height-50,300,50,"Arial","Loading...");
	loadtxt->setSize(20);
	add(loadtxt);
}
