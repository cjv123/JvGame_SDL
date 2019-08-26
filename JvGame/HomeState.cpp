#include "HomeState.h"
#include "GameState.h"
#include "SelectState.h"
#include "CreateState.h"
#include "JvGame/JvH.h"

static void start_game_callback(int par)
{
	JvG::switchState(new SelectState(false));
}

static void gotocreate_callback(int par)
{
	JvG::switchState(new CreateState);
}

HomeState::HomeState(bool isMusic)
{
	_bgTileGroup = NULL;
	_arrow = NULL;
	_startButton = NULL;
	_createButton = NULL;

	_isMusic = isMusic;

	_curSelectIndex = 0;
}

void HomeState::create()
{
	setBgColor(MAKE_RGBA_8888(87,196,247,255));
	JvState::create();
	camera->flash(MAKE_RGBA_8888(255,255,255,255),1);
	/*
	_bgTileGroup = new JvGroup;
	_bgTileW=50;
	_bgTileWNum = JvU::ceil(JvG::width/_bgTileW)+3;
	_bgTileHNum = JvU::ceil(JvG::height/_bgTileW)+3;
	_bgTileNum = _bgTileHNum*_bgTileWNum;
	
	int i=0,w=0,h=0,color=0,row=0,col=0;
	for (;i<_bgTileNum;i++)
	{
		col = i%_bgTileWNum;
		row = (int)(i/_bgTileWNum);
		w = col*_bgTileW;
		h = row*_bgTileW;
		JvSprite* bgTile = new JvSprite;
		if (row%2==0)
		{
			if (col%2==0)
				color = MAKE_RGBA_8888(240,206,180,255);
			else
				color = MAKE_RGBA_8888(244,222,204,255);
		}
		else
		{
			if (col%2!=0)
				color = MAKE_RGBA_8888(240,206,180,255);
			else
				color = MAKE_RGBA_8888(244,222,204,255);
		}
		bgTile->createRect(w,h,_bgTileW,_bgTileW,color);
		_bgTileGroup->add(bgTile);
		//bgTile->velocity.x =-30;
		//bgTile->velocity.y =-30;
	}
	JvSprite* lrBgTile = new JvSprite;
	lrBgTile->createRect(JvG::width-_bgTileW,JvG::height-_bgTileW,
		_bgTileW,_bgTileW,MAKE_RGBA_8888(244,222,204,255));
	add(lrBgTile);
	add(_bgTileGroup);
	*/
	_bg = new JvSprite(40,-100);
	_bg->loadGraphic("bg_non.png");
	_bg->x = JvG::width/2 - _bg->width/2;
	
// 	JvSprite* rainbow = new JvSprite(0,0);
// 	rainbow->loadGraphic("bg_ch.png");
// 	add(rainbow);
	add(_bg);
	_bg->velocity.x = -30;

	JvSprite* titsp = new JvSprite(-81,-10);
	titsp->loadGraphic("home_en.png");
	//titsp->setScale(1.3);
	titsp->x = JvG::width/2 - titsp->width/2;
	add(titsp);
	
	JvSprite* buttonSprite = new JvSprite;
	buttonSprite->loadGraphic("homebutton.png");
	JvSprite* buttonSpSel = new JvSprite;
	buttonSpSel->loadGraphic("homebutton_sel.png");
	JvButton* startButton = new JvButton(JvG::width/2-buttonSprite->width/2,JvG::height-JvG::height/2+10,
		buttonSprite->width,buttonSprite->height);
	startButton->loadGraphic(buttonSprite,buttonSpSel);
	startButton->setTitle("START GAME",FONT_NAME,15,3);
	startButton->setCallback(start_game_callback);
	add(startButton);
	_startButton = startButton;

	buttonSprite = new JvSprite;
	buttonSprite->loadGraphic("homebutton.png");
	buttonSpSel = new JvSprite;
	buttonSpSel->loadGraphic("homebutton_sel.png");
	JvButton* createButton = new JvButton(JvG::width/2-buttonSprite->width/2,JvG::height-JvG::height/3,
		buttonSprite->width,buttonSprite->height);
	createButton->loadGraphic(buttonSprite,buttonSpSel);
	createButton->setTitle("CREATES",FONT_NAME,22,4);
	createButton->setCallback(gotocreate_callback);
	add(createButton);
	_createButton = createButton;


	JvSprite* arrowSp = new JvSprite(startButton->x-5,startButton->y+startButton->height/2);
	arrowSp->loadGraphic("arrow.png");
	arrowSp->offset.x = arrowSp->width;
	arrowSp->offset.y = arrowSp->height / 2;
	add(arrowSp);
	_arrow = arrowSp;

	JvText* powertxt = new JvText(10,JvG::height,0,0,FONT_NAME,
		"Power By ZF Studio 2019.Dirve by JvGame.",11);
	powertxt->x = JvG::width/2 - powertxt->width/2;
	powertxt->y = powertxt->y - powertxt->height-8;
	add(powertxt);
	
	if (_isMusic)
	{
		JvG::playMusic("home.mp3");
	}
	
}



void HomeState::update()
{
	/*
	if (_bgTileGroup!=NULL)
	{
		vector<JvObject*>::iterator it =_bgTileGroup->members.begin();
		for (;it!=_bgTileGroup->members.end();it++)
		{
			(*it)->x -=0.5f;
			(*it)->y -=0.5f;
			if(!(*it)->onScreen() && 
				(*it)->x<=JvG::width && (*it)->y<=JvG::height)
			{

				if ((*it)->x<0)
				{
					(*it)->x+=(_bgTileWNum)*_bgTileW;
				//	(*it)->y-=_bgTileW;
				}
				else if((*it)->y<0)
				{
					(*it)->y+=(_bgTileHNum)*_bgTileW;
					(*it)->x-=_bgTileW;
				}
			}
		}
	}
	*/
	if (_bg->x<=-_bg->width+20)
	{
		_bg->x = JvG::width;
	}

	updateArrow();


	JvState::update();
}

void HomeState::updateArrow()
{
	if (_arrow && _startButton && _createButton) 
	{

		if (JvG::joystick->isJustPreess(DOWNCODE))
		{
			_curSelectIndex++;
		}
		else if (JvG::joystick->isJustPreess(UPCODE))
		{
			_curSelectIndex--;
		}
		else if (JvG::joystick->isJustPreess(ACODE))
		{
			if (_curSelectIndex == 0)
			{
				JvG::switchState(new SelectState(false));
			}
			else
			{
				JvG::switchState(new CreateState);
			}
			return;
		}

		if (_curSelectIndex > 1) _curSelectIndex = 0;
		if (_curSelectIndex < 0) _curSelectIndex = 1;


		if (_curSelectIndex == 0) 
		{
			_arrow->x = _startButton->x - 5;
			_arrow->y = _startButton->y + _startButton->height / 2;
		}
		else
		{
			_arrow->x = _createButton->x - 5;
			_arrow->y = _createButton->y + _createButton->height / 2;
		}
	}
}
