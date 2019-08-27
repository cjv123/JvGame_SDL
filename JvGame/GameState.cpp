#include "GameState.h"
#include "SelectState.h"
#include "Hero.h"
#include "Enemy.h"
#include "Stone.h"
#include "StoneHidden.h"
#include "StoneHiddenShow.h"
#include "StoneMove.h"
#include "StoneMoveD.h"
#include "Stab.h"
#include "StabD.h"
#include "StabL.h"
#include "StabR.h"
#include "StabHidden.h"
#include "BallItem.h"
#include "ClimbItem.h"
#include "ExitDoor.h"
#include "Fan.h"
#include "keyObj.h"
#include "GamePad.h"
#include "FlyObj.h"
#include "HomeState.h"
#include "Coin.h"
#include "QueObj.h"
#include "JvGame/JvH.h"

#include "tinyxml2.h"

#include <fstream>
#include <sstream>
#include <assert.h>

using namespace tinyxml2;

Hero* GameState::heroP = NULL;
int GameState::nowLv = 1;
JvTilemap* GameState::tileMap = NULL;
bool GameState::isGetKey = false;
bool GameState::isGetStar = false;
JvSprite* GameState::hasKeyObj = NULL;
JvSprite* GameState::hasStarObj = NULL;
GamePad* GameState::gamePad = NULL;
GameData* GameState::gameData = NULL;
JvButton* GameState::backButton = NULL;
JvButton* GameState::resButton = NULL;
JvButton* GameState::exitButton = NULL;
JvButton* GameState::nextButton = NULL;
JvSprite* GameState::buttonBg = NULL;
JvButton* GameState::pauseButton = NULL;
JvText* GameState::gameoverTile = NULL;
JvText* GameState::pauseTile = NULL;
JvTextPad* GameState::nowShowTextPad = NULL;
int GameState::_maxPauseMenuIndex = 3;
int GameState::_curPauseMenuIndex = 0;
JvButton* GameState::_pauseMenus[3] = { NULL };
bool GameState::curFramePauseKeyDown = false;
bool GameState::startGame = false;

static void ResButton_callback(int par)
{
	JvG::switchState(new GameState);
	JvG::pause = false;
}

static void NextButton_callback(int par)
{
	
}

static void Exit_callback(int par)
{
	JvG::stopMusic();
	JvG::switchState(new SelectState);
	JvG::pause = false;
}

static void back_callback(int par)
{
	GameState::backButton->visible = false;
	GameState::resButton->visible = false;
	GameState::exitButton->visible = false;
	GameState::buttonBg->visible = false;
	GameState::pauseTile->visible = false;
	JvG::pause = false;
}

static void pause_callback(int par)
{
	if (GameState::resButton->visible == true)
	{
		return;
	}
	JvG::pause = true;
}

GameState::GameState()
{
	for (int i = 0; i < _maxPauseMenuIndex; i++)
	{
		GameState::_pauseMenus[i] = NULL;
	}
}

GameState::~GameState()
{
	GameState::heroP = NULL;
	GameState::tileMap = NULL;
	GameState::isGetKey = false;
	GameState::isGetStar = false;
	GameState::hasKeyObj = NULL;
	GameState::hasStarObj = NULL;
	GameState::gamePad = NULL;
	GameState::gameData;
	GameState::backButton = NULL;
	GameState::resButton = NULL;
	GameState::exitButton = NULL;
	GameState::nextButton = NULL;
	GameState::buttonBg = NULL;
	GameState::pauseButton = NULL;
	GameState::gameoverTile = NULL;
	GameState::pauseTile = NULL;
	GameState::nowShowTextPad = NULL;
}

void GameState::create()
{
	JvState::create();

	setBgColor(MAKE_RGBA_8888(168,224,248,255));
	GameState::isGetKey = false;
	GameState::isGetStar = false;

	GameState::hasKeyObj = new JvSprite(JvG::width/2 - 12,4);
	GameState::hasKeyObj->loadGraphic("haskey.png");
	GameState::hasKeyObj->SetFixed(false);
	GameState::hasKeyObj->scrollFactor.x = 0;
	GameState::hasKeyObj->scrollFactor.y = 0;
	GameState::hasKeyObj->setScale(0.5);
	GameState::hasKeyObj->visible = false;

	GameState::hasStarObj = new JvSprite(JvG::width/2 +22,2);
	GameState::hasStarObj->loadGraphic("object_tile.png",true,false,16,16);
	GameState::hasStarObj->SetFixed(false);
	GameState::hasStarObj->scrollFactor.x = 0;
	GameState::hasStarObj->scrollFactor.y = 0;
	GameState::hasStarObj->setScale(0.5);
	GameState::hasStarObj->visible = false;
	vector<int> hasStarAnim;
	hasStarAnim.push_back(11);
	GameState::hasStarObj->addAnimation("nor",hasStarAnim);
	GameState::hasStarObj->play("nor");
	
	gamePad = new GamePad;

	JvSprite* bgP = new JvSprite(0,0);
	bgP->loadGraphic("bg.png");
	bgP->setCollide(false);
	bgP->scrollFactor.x = bgP->scrollFactor.y = 0.2f;
	add(bgP);

	JvGroup* overHeroGroup = new JvGroup;

	char mapfilename[20];
	sprintf(mapfilename,"mapCSV_lv%d.csv",GameState::nowLv);
	GameState::tileMap = new JvTilemap();
	GameState::tileMap->loadMap(mapfilename,"map.png",16,16);
	add(GameState::tileMap);
	
	tinyxml2::XMLDocument doc;

	char xmlfilename[20];
	sprintf(xmlfilename,"Level_lv%d.xml",GameState::nowLv);
	unsigned long s=0;
	unsigned char* xmldata = NULL;
	ifstream file(xmlfilename, ifstream::in);
	if (file.is_open())
	{
		stringstream buffer;
		buffer << file.rdbuf();
		string strTmp(buffer.str());
		xmldata = (unsigned char*)strTmp.c_str();
		assert(xmldata,"fuck");
		doc.Parse((const char*)xmldata);
	}

	XMLElement* rootElement = doc.RootElement();
	
	XMLNode* NodeP = rootElement->FirstChildElement("objects");
	if (NodeP)
	{
		NodeP = NodeP->FirstChildElement();
	}

	for (;NodeP;NodeP=NodeP->NextSiblingElement())
	{
		string classname = NodeP->Value();
		XMLElement* elemet = NodeP->ToElement();
		string xstr=elemet->Attribute("x");
		string ystr=elemet->Attribute("y");
		double x = atof(xstr.c_str());
		double y = atof(ystr.c_str());
	
		int ret = (int)elemet->Attribute("n");
		int n=1;
		if (ret!=0)
		{
			string nstr = elemet->Attribute("n");
			n = atoi(nstr.c_str()); 
			if (n==0)
				n=1;
		}
	
		
	//	printf("%s %f %f\n",classname.c_str(),x,y);
		if(classname == "BallItem")
		{
			BallItem* ballitem = new BallItem(x,y);
			add(ballitem);
		}
		else if (classname == "ClimbItem")
		{
			ClimbItem* climbitem = new ClimbItem(x,y);
			add(climbitem);
		}
		else if (classname == "Enemy")
		{
			Enemy* enemy = new Enemy(x,y);
			add(enemy);
		}
		else if (classname == "ExitDoor")
		{
			ExitDoor* exitDoor = new ExitDoor(x,y);
			add(exitDoor);
		}
		else if (classname == "Fan")
		{
			Fan* fan = new Fan(x,y);
			add(fan);
		}
		else if (classname == "KeyObj")
		{
			KeyObj* keyObj = new KeyObj(x,y);
			add(keyObj);
		}
		else if (classname == "Stab")
		{
			int si=0;
			for (;si<n;si++)
			{
				Stab* stab = new Stab(x+si*16,y);
				add(stab);
			}
			
		}
		else if (classname == "StabD")
		{
			int sdi=0;
			for (;sdi<n;sdi++)
			{
				StabD* stab = new StabD(x+sdi*16,y);
				add(stab);
			}
			
		}
		else if (classname == "StabL")
		{
			int sli=0;
			for (;sli<n;sli++)
			{
				StabL* stab = new StabL(x,y+sli*16);
				add(stab);
			}
			
		}
		else if (classname == "StabR")
		{
			int sbi=0;
			for (;sbi<n;sbi++)
			{
				StabR* stab = new StabR(x,y+sbi*16);
				add(stab);
			}
			
		}
		else if (classname == "StabHidden")
		{
			StabHidden* stab = new StabHidden(x,y);
			add(stab);
		}
		else if (classname =="Stone")
		{
			Stone* stone = new Stone(x,y);
			add(stone);
		}
		else if (classname =="StoneHidden")
		{
			StoneHidden* stone = new StoneHidden(x,y);
			add(stone);
		}
		else if (classname =="StoneHiddenShow")
		{
			StoneHiddenShow* stone = new StoneHiddenShow(x,y);
			add(stone);
		}
		else if (classname =="StoneMove")
		{
			StoneMove* stone = new StoneMove(x,y);
			add(stone);
		}
		else if (classname =="StoneMoveD")
		{
			StoneMoveD* stone = new StoneMoveD(x,y);
			add(stone);
		}
		else if (classname == "FlyObj")
		{
			FlyObj* flyObj = new FlyObj(x,y);
			add(flyObj);
		}
		else if (classname == "Coin")
		{
			Coin* coin = new Coin(x,y);
			add(coin);
		}
		else if (classname == "QueObj")
		{
			string quetxt;
			int ret = (int)elemet->Attribute("text");
			if (ret!=0)
			{
				quetxt = elemet->Attribute("text");
			}
			
			JvSprite* qitem=NULL;
			ret = (int)elemet->Attribute("item");
			if (ret != 0)
			{
				string itemname = elemet->Attribute("item");
				if (itemname == "BallItem")
				{
					qitem = new BallItem(x-5,y-10-32);
				}
				else if (itemname =="ClimbItem")
				{
					qitem = new ClimbItem(x-5,y-10-32);
				}
				overHeroGroup->add(qitem);
			}

			JvTextPad* txtpad = new JvTextPad(JvG::width/2-170/2,JvG::height/2-100/2-20/2,340/2,200/2,
				FONT_NAME,quetxt.c_str());
			QueObj* queobj = new QueObj(x,y,txtpad,qitem);
			add(queobj);
			overHeroGroup->add(txtpad);
		}
		else if (classname == "Hero")
		{
			GameState::heroP = new Hero(x,y);
		}
		
	}
	
	char lvstr[7];
	sprintf(lvstr,"Lv.%d",nowLv);
	JvText* lvtxt = new JvText(0,0,0,0,FONT_NAME,lvstr,11);
	//lvtxt->setSize(8);
	lvtxt->setColor(MAKE_RGBA_8888(0,0,0,255));
	lvtxt->scrollFactor.x = lvtxt->scrollFactor.y =0;
	add(lvtxt);

	add(heroP);
	add(overHeroGroup);
	
	add(GameState::hasKeyObj);
	add(GameState::hasStarObj);

	camera->follow(heroP,2.6f);
	camera->followBounds(0,0,GameState::tileMap->width,GameState::tileMap->height);
	camera->followAdjust(0.6f,0.4f);

	
	add(gamePad);
	gamePad->visible = false;

	JvG::playMusic("bgm.mp3");
	
	/*JvSprite* pauseBSp = new JvSprite;
	JvSprite* pauseBSpH = new JvSprite;
	pauseBSp->loadGraphic("pause.png");
	pauseBSpH->loadGraphic("pause_sel.png");
	pauseButton = new JvButton(JvG::width-pauseBSp->width,0,
		pauseBSp->width,pauseBSp->height);
	pauseButton->loadGraphic(pauseBSp,pauseBSpH);
	pauseButton->setCallback(pause_callback);
	add(pauseButton);*/
	
	SDL_Texture* bimg = JvU::loadTexture("menubutton.png");
	SDL_Texture* bimgh = JvU::loadTexture("menubutton_sel.png");

	JvSprite* spb = new JvSprite(0,0,bimg);
	JvSprite* spbH = new JvSprite(0,0,bimgh);
	int by = JvG::height/2 - spb->height/4;
	resButton = new JvButton(0,by,spb->width,spb->height);
	resButton->loadGraphic(spb,spbH);
	resButton->setTitle("RESTART",FONT_NAME,32,6,12);
	nextButton = new JvButton(100,by+50,spb->width,spb->height);
	spb = new JvSprite(0,0,bimg);
	spbH = new JvSprite(0,0,bimgh);
	nextButton->loadGraphic(spb,spbH);

	exitButton = new JvButton(0,by,spb->width,spb->height);
	spb = new JvSprite(0,0,bimg);
	spbH = new JvSprite(0,0,bimgh);
	exitButton->loadGraphic(spb,spbH);
	exitButton->setTitle("MAIN MENU",FONT_NAME,26,6,12);

	backButton = new JvButton(0,by,spb->width,spb->height);
	spb = new JvSprite(0,0,bimg);
	spbH = new JvSprite(0,0,bimgh);
	backButton->loadGraphic(spb,spbH);
	backButton->setTitle("RESUME GAME",FONT_NAME,14,6,12);

	resButton->setCallback(ResButton_callback);
	nextButton->setCallback(NextButton_callback);
	exitButton->setCallback(Exit_callback);
	backButton->setCallback(back_callback);
	resButton->visible = false;
	nextButton->visible = false;
	exitButton->visible = false;
	backButton->visible = false;
	_isShowMenu = false;

	buttonBg = new JvSprite;
	buttonBg->createRect(0,0,JvG::width,JvG::height,MAKE_RGBA_8888(0,0,0,128));
	add(buttonBg);
	buttonBg->visible = false;
	buttonBg->scrollFactor.x=0;
	buttonBg->scrollFactor.y=0;
	buttonBg->setCollide(false);
	
	gameoverTile = new JvText(0,2,200,30,FONT_NAME,"GAME OVER",16);
	gameoverTile->x = JvG::width/2 - gameoverTile->width/2;
	//gameoverTile->setSize(16);
	gameoverTile->setColor(MAKE_RGBA_8888(255,0,0,255));
	gameoverTile->scrollFactor.x =0;
	gameoverTile->scrollFactor.y =0;
	gameoverTile->visible = false;
	add(gameoverTile);
	add(resButton);
	add(nextButton);
	add(exitButton);
	add(backButton);

	
	pauseTile = new JvText(0,2,200,30,FONT_NAME,"PAUSE",16);
	pauseTile->x = JvG::width/2 - pauseTile->width/2;
	//pauseTile->setSize(16);
	pauseTile->setColor(MAKE_RGBA_8888(255,0,0,255));
	pauseTile->scrollFactor.x=0;
	pauseTile->scrollFactor.y=0;
	pauseTile->visible = false;
	add(pauseTile);

	startGame = true;
}

void GameState::update()
{
	if (JvG::pause==false 
		&& startGame==true
		&& JvG::joystick->isJustPreess(STARTCODE)
	)
	{
		::pause_callback(0);
		curFramePauseKeyDown = true;
	}

	JvState::collide();
	JvState::update();

	if (exitButton->visible==true)
	{
		if (JvG::joystick->isJustPreess(UPCODE))
		{
			_curPauseMenuIndex--;
			if (_curPauseMenuIndex < 0)
			{
				_curPauseMenuIndex = _maxPauseMenuIndex;
			}
			updatePauseMenu();
		}
		else if (JvG::joystick->isJustPreess(DOWNCODE))
		{
			_curPauseMenuIndex++;
			if (_curPauseMenuIndex > _maxPauseMenuIndex)
			{
				_curPauseMenuIndex = 0;
			}
			updatePauseMenu();
		}
		else if (JvG::joystick->isJustPreess(ACODE))
		{
			if (_pauseMenus[_curPauseMenuIndex])
			{
				JvButton* curMenuButton = _pauseMenus[_curPauseMenuIndex];
				if (curMenuButton == backButton)
				{
					::back_callback(0);
				}
				else if (curMenuButton == resButton)
				{
					::ResButton_callback(0);
				}
				else if (curMenuButton == exitButton)
				{
					::Exit_callback(0);
				}
				else if (curMenuButton == nextButton)
				{
					::NextButton_callback(0);
				}
			}
		}

	}

	curFramePauseKeyDown = false;
}

void GameState::fail()
{
	startGame = false;
	resButton->visible = true;
	exitButton->visible = true;
	buttonBg->visible = true;
	gameoverTile->visible = true;
	resButton->setPosition(JvG::width/2-resButton->width/2,40);
	exitButton->setPosition(JvG::width/2-exitButton->width/2,82);
	
	_pauseMenus[0] = resButton;
	_pauseMenus[1] = exitButton;
	_maxPauseMenuIndex = 1;
	_curPauseMenuIndex = 0;
	updatePauseMenu();
}

void GameState::success()
{
	startGame = false;
	nextButton->visible = true;
	exitButton->visible = true;
	nextButton->y = 70;
	exitButton->y = 125;

	_pauseMenus[0] = nextButton;
	_pauseMenus[1] = exitButton;
	_maxPauseMenuIndex = 1;
	_curPauseMenuIndex = 0;
	updatePauseMenu();
}

void GameState::updatePauseMenu()
{
	for (int i = 0; i <= _maxPauseMenuIndex; i++)
	{
		if (i == _curPauseMenuIndex)
		{
			_pauseMenus[i]->selectMode();
		}
		else
		{
			_pauseMenus[i]->normalMode();
		}
	}
}

void GameState::pause()
{
	if (nowShowTextPad != NULL)
	{
		JvRect rect(nowShowTextPad->x,nowShowTextPad->y,
			nowShowTextPad->width,nowShowTextPad->height);

		//nge_print("rect:x:%lf,y:%lf,w:%lf,h:%lf\n",nowShowTextPad->x,nowShowTextPad->y,
		//		nowShowTextPad->width,nowShowTextPad->height);
		if (JvG::joystick->isMouseIn(rect)
			|| JvG::joystick->isJustPreess(ACODE)
			|| JvG::joystick->isJustPreess(BCODE)
			)
		{
			nowShowTextPad->close();
			JvG::pause = false;
			nowShowTextPad = NULL;
		}
	
		return;
	}

	if (backButton->visible == false)
	{
		backButton->visible = true;
		resButton->visible = true;
		exitButton->visible = true;
		buttonBg->visible = true;
		pauseTile->visible = true;
		backButton->setPosition(JvG::width/2-resButton->width/2,JvG::height/6);
		resButton->setPosition(JvG::width/2-resButton->width/2,JvG::height/6 + 50);
		exitButton->setPosition(JvG::width/2-exitButton->width/2,JvG::height/6 + 100);

		_pauseMenus[0] = backButton;
		_pauseMenus[1] = resButton;
		_pauseMenus[2] = exitButton;
		_maxPauseMenuIndex = 2;
		_curPauseMenuIndex = 0;
		updatePauseMenu();
	}
	backButton->update();
	resButton->update();
	exitButton->update();

	if (curFramePauseKeyDown == false 
		&& (JvG::joystick->isJustPreess(STARTCODE)
			|| JvG::joystick->isJustPreess(BCODE)
			)
		)
	{
		::back_callback(0);
		curFramePauseKeyDown = true;
	}

}
