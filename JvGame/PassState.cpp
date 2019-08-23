#include "JvGame/JvH.h"
#include "PassState.h"
#include "GameState.h"
#include "SelectState.h"


static void NextButton_callback_ps(int par)
{
	GameState::nowLv++;
	JvG::switchState(new GameState);
}

static void Exit_callback_ps(int par)
{
	JvG::switchState(new SelectState);
}

void PassState::create()
{
	JvState::create();
	setBgColor(MAKE_RGBA_8888(87,196,247,255));

	JvG::stopMusic();

	JvSprite* bg = new JvSprite(0,-100);
	bg->loadGraphic("bg.png");
	add(bg);

// 	JvTilemap* map = new JvTilemap;
// 	map->loadMap("pass.csv","map.png",16,16);
// 	add(map);

	hero = new JvSprite(113,130);
	hero->loadGraphic("hero.png",true,false,16,31);
	vector<int> standAnima;
	standAnima.push_back(1);
	hero->addAnimation("stand",standAnima,0);
	hero->play("stand");
	add(hero);

	heroFly = new JvSprite(113,129);
	heroFly->loadGraphic("flyup.png");

	txt = new JvText(270,140,200,50,FONT_NAME,"Pass");
	txt->setSize(20);
	txt->setColor(MAKE_RGBA_8888(255,0,0,255));
	txt->visible = false;
	add(txt);


	JvSprite* spb = new JvSprite(0,0);
	JvSprite* spbH = new JvSprite(0,0);
	spb->loadGraphic("menubutton.png");
	spbH->loadGraphic("menubutton_sel.png");
	
	nextButton = new JvButton(JvG::width/2-spb->width/2,60,spb->width,spb->height);
	nextButton->loadGraphic(spb,spbH);
	nextButton->setTitle("NEXT LEVEL",FONT_NAME,0,0,12);
	
	spb = new JvSprite(0,0);
	spbH = new JvSprite(0,0);
	spb->loadGraphic("menubutton.png");
	spbH->loadGraphic("menubutton_sel.png");

	exitButton = new JvButton(JvG::width/2-spb->width/2,102,spb->width,spb->height);
	exitButton ->loadGraphic(spb,spbH);
	exitButton->setTitle("MAIN MENU",FONT_NAME,0,0,12);

	nextButton->setCallback(NextButton_callback_ps);
	exitButton->setCallback(Exit_callback_ps);

	bBg = new JvSprite;
	bBg->createRect(0,0,JvG::width,JvG::height,MAKE_RGBA_8888(0,0,0,128));
	add(bBg);

	gameoverTile = new JvText(0,10,300,30,FONT_NAME,"Level Complete");
	gameoverTile->x = JvG::width/2 - gameoverTile->width/2;
	gameoverTile->setSize(20);
	gameoverTile->setColor(MAKE_RGBA_8888(255,0,0,255));
	gameoverTile->scrollFactor.x =0;
	gameoverTile->scrollFactor.y =0;
	gameoverTile->visible = false;
	add(gameoverTile);

	add(exitButton);
	add(nextButton);
	bBg->visible = false;
	exitButton->visible = false;
	nextButton->visible = false;

	camera->flash(MAKE_RGBA_8888(255,255,255,255),1);
	
	
	time = 0;
}

void PassState::update()
{
	if (time >=0 )
	{
		time++;
	}

	if (time>=100)
	{
		hero->visible = false;
		time = -1;
		heroFly->velocity.y = -170;
		add(heroFly);
		txt->visible  = true;
	}

	if (!heroFly->onScreen())
	{
		if (bBg->visible == false)
		{
			bBg->visible = true;
			exitButton->visible = true;
			if(GameState::nowLv<28)
				nextButton->visible = true;
			gameoverTile->visible = true;
		}
		
	}

	JvState::update();
}

