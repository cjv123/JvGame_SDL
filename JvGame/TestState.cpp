#include "TestState.h"
#include "JvGame/JvSprite.h"
#include "JvGame/JvText.h"

void TestState::create()
{
	/*JvSprite* sp = new JvSprite();
	sp->loadGraphic("hero.png",true,false,16,31);
	add(sp);
	sp->velocity.x = 100;

	std::vector<int> frames{2,3,4,5};
	sp->addAnimation("walk",frames,4);
	sp->play("walk");*/

	JvText* text = new JvText(50,50,0,0,"nokiafc22.ttf","hehe,test");
	add(text);

	//JvG::playMusic("bgm.mp3");
	//JvG::play("nintendo.wav");
}

void TestState::update()
{
	JvState::update();
}
