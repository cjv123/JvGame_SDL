#include "TestState.h"
#include "JvGame/JvSprite.h"
#include "JvGame/JvText.h"
#include "JvGame/JvEmitter.h"
#include "JvGame/JvJoystick.h"

static JvEmitter* emitter=NULL;

void TestState::create()
{
	/*JvSprite* sp = new JvSprite();
	sp->loadGraphic("hero.png",true,false,16,31);
	add(sp);
	sp->velocity.x = 100;

	std::vector<int> frames{2,3,4,5};
	sp->addAnimation("walk",frames,4);
	sp->play("walk");*/

	//JvText* text = new JvText(50,50,0,0,"nokiafc22.ttf","hehe,test");
	//add(text);

	//JvG::playMusic("bgm.mp3");
	//JvG::play("nintendo.wav");

	emitter = new JvEmitter();
	emitter->x = 150;
	emitter->y = 160;
	//emitter->delay = 3;
	emitter->setXSpeed(-80, 80);
	emitter->setYSpeed(-200, 0);
	emitter->setRotation(-360, -360);
	emitter->setSize(5, 5);
	emitter->createSprites("stone_gibs.png", 4, 4, true, 0);
	add(emitter);
}

void TestState::update()
{
	if (JvG::joystick->isJustPreess(ACODE))
	{
		emitter->start();
	}

	JvState::update();
}
