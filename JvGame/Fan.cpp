#include "Fan.h"
#include "GameState.h"
#include "Hero.h"

Fan::Fan(double X,double Y) : JvSprite(X,Y)
{
	loadGraphic("fan.png",true,true,32,32);

	vector<int> frames;
	frames.push_back(0);
	frames.push_back(1);
	frames.push_back(2);
	frames.push_back(3);
	addAnimation("do",frames,50);
	play("do");
	SetFixed(true);
}

void Fan::update()
{
	JvSprite::update();
	
	if(GameState::heroP->x+GameState::heroP->width>x && GameState::heroP->x<x+width && 
		GameState::heroP->y+GameState::heroP->width<y &&
		y-GameState::heroP->y <210*2
		)
	{
		GameState::heroP->velocity.y-=20*2;
	}
}