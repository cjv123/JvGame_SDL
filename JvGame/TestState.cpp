#include "TestState.h"
#include "JvGame/JvSprite.h"

void TestState::create()
{
	JvSprite* sp = new JvSprite();
	sp->loadGraphic("hero.png",true,false,16,31);
	add(sp);
	sp->velocity.x = 100;
}

void TestState::update()
{
	JvState::update();
}
