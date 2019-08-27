#include "JvGame/JvH.h"
#include "SelectState.h"
#include "GameState.h"
#include "StartState.h"
#include "HomeState.h"

static void selectLvButton(int par)
{
	GameState::nowLv = par;
	JvG::switchState(new StartState);
}

static void back_button_callback(int par)
{
	JvG::switchState(new HomeState(false));
}

SelectState::SelectState(bool isMusic)
{
	_isMusic = isMusic;
	_curSelectLv = 1;
	_curMaxLv = 1;
	_curSelectButton = NULL;

	for (int i = 0; i < 28; i++)
	{
		_selectButtons[i] = NULL;
	}
}

void SelectState::create()
{
//	setBgColor(MAKE_RGBA_8888(87,196,247,255));
	JvState::create();
	camera->flash(MAKE_RGBA_8888(255,255,255,255),1);

	_bgTileGroup = new JvGroup;
	_bgTileW=35;
	_bgTileWNum = JvU::ceil(JvG::width/_bgTileW)+5;
	_bgTileHNum = JvU::ceil(JvG::height/_bgTileW)+5;
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

//	GameState::gameData->level[1] = 2;
	
/*
	char titleStr[20]="Select Level";
	int titleFontSize = 20;
	JvText* title = new JvText(JvG::width/2-strlen(titleStr)*titleFontSize/2+15,10,
			strlen(titleStr)*titleFontSize,25,FONT_NAME,titleStr);
	title->setSize(titleFontSize);
	add(title);*/

	JvSprite* title  = new JvSprite;
	title->loadGraphic("sel_title_en.png");
	title->x = JvG::width/2 - title->width/2;
	title->y = 17;
	add(title);
	
	JvButton* lvButton=NULL;
	col=0;row=0;
	int bx=0,by=0;
	JvSprite* bImgSp = NULL;
	JvSprite* bHighImgSp = NULL;

	SDL_Texture* bImg = JvU::loadTexture("lv.png");
	SDL_Texture* bHighImg = JvU::loadTexture("lv_sel.png");
	SDL_Texture* bLockImg = JvU::loadTexture("lv_lock.png");

	JvText* txt = NULL;
	i=0;
	char str[5];
	int interval = 0;
	for (;i<28;i++)
	{
		col = i % 7;
		row = (unsigned int)(i / 7);

		if (GameState::gameData->level[i]==LVOPEN ||
			GameState::gameData->level[i]==LVPASS ||
			GameState::gameData->level[i]==STARPASS
			)
		{
			bImgSp = new JvSprite(0,0,bImg);
			bHighImgSp =new JvSprite(0,0,bHighImg);
			lvButton = new JvButton(0,0,bImgSp->width,bHighImgSp->height);
			int tarx = JvG::width/2-7*((int)lvButton->width+interval)/2;
			lvButton->x = col * (lvButton->width+interval)+tarx;
			lvButton->y = row * (lvButton->height+interval)+JvG::height/5+20;

			lvButton->loadGraphic(bImgSp,bHighImgSp);
			add(lvButton);
			lvButton->setCallback(selectLvButton,NULL,i+1);
			
			if (GameState::gameData->level[i]==LVOPEN)
			{
				sprintf(str,"%d",i+1);
				txt = new JvText(lvButton->x,lvButton->y,lvButton->width,
					lvButton->height,FONT_NAME,str,16);
				txt->x = lvButton->x + lvButton->width/2 - txt->width / 2;
				txt->y = lvButton->y + lvButton->height/2 - txt->height / 2+2;
				add(txt);
			}
			else
			{
				txt = new JvText(lvButton->x,lvButton->y,lvButton->width,
					lvButton->height,FONT_NAME,"Pass");
				txt->x = lvButton->x + lvButton->width/2 - txt->width / 2;
				txt->y = lvButton->y + lvButton->height/2 - txt->height / 2;
				//txt->setColor(MAKE_RGBA_8888(255,0,0,255));
				add(txt);

				if (GameState::gameData->level[i]==STARPASS)
				{
					JvSprite* star = new JvSprite(lvButton->x+17,lvButton->y+17);
					star->loadGraphic("object_tile.png",true,false,16,16);
					vector<int> staranim;
					staranim.push_back(11);
					star->addAnimation("nor",staranim);
					star->play("nor");
					add(star);
				}
			}

			_curMaxLv = i + 1;
		}
		else if(GameState::gameData->level[i]==LVLOCK)
		{
			bImgSp = new JvSprite(0,0,bLockImg);
			bImgSp->x = col * (lvButton->width+interval)+JvG::width/2-7*((int)lvButton->width+interval)/2;
			bImgSp->y = row * (lvButton->height+interval)+JvG::height/5+20;
			add(bImgSp);
		}

		if (lvButton)
		{
			_selectButtons[i] = lvButton;
		}
	}

	
	_curSelectLv = _curMaxLv;
	_curSelectButton = _selectButtons[_curMaxLv - 1];
	updateSelectButton();

	/*JvSprite* backBSp = new JvSprite;
	JvSprite* backBSpH = new JvSprite;
	backBSp->loadGraphic("back.png");
	backBSpH->loadGraphic("back_sel.png");
	JvButton* backButton = new JvButton(JvG::width-backBSp->width,0,
		backBSp->width,backBSp->height);
	backButton->loadGraphic(backBSp,backBSpH);
	backButton->setCallback(back_button_callback);
	add(backButton);*/
	
	
	if (_isMusic)
	{
		JvG::playMusic("home.mp3");
	}
}

void SelectState::update()
{
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

	if (JvG::joystick->isJustPreess(BCODE))
	{
		JvG::switchState(new HomeState);
	}
	else if (JvG::joystick->isJustPreess(ACODE))
	{
		GameState::nowLv = _curSelectLv;
		JvG::switchState(new GameState);
	}
	else if (JvG::joystick->isJustPreess(UPCODE))
	{
		if (_curSelectLv - 7 > 0)
		{
			_curSelectLv-=7;
			updateSelectButton();

			JvG::play("shoot.wav");
		}
	}
	else if (JvG::joystick->isJustPreess(DOWNCODE))
	{
		if (_curSelectLv + 7 <= _curMaxLv)
		{
			_curSelectLv+=7;
			updateSelectButton();
			JvG::play("shoot.wav");
		}
	}
	else if (JvG::joystick->isJustPreess(LEFTCODE))
	{
		_curSelectLv--;
		if (_curSelectLv < 1)
			_curSelectLv = _curMaxLv;
		updateSelectButton();

		JvG::play("shoot.wav");
	}
	else if (JvG::joystick->isJustPreess(RIGHTCODE))
	{
		_curSelectLv++;
		if (_curSelectLv > _curMaxLv)
			_curSelectLv = 1;

		updateSelectButton();

		JvG::play("shoot.wav");
	}

	

	JvState::update();
}

void SelectState::updateSelectButton()
{
	if (_curSelectButton)
	{
		_curSelectButton->normalMode();
		if (_selectButtons[_curSelectLv - 1])
		{
			_selectButtons[_curSelectLv - 1]->selectMode();
			_curSelectButton = _selectButtons[_curSelectLv - 1];
		}

	}
}
