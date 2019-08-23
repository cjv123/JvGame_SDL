#include "JvGame/JvH.h"
#include "FlyObj.h"
#include "GameState.h"
#include "Hero.h"

FlyObj::FlyObj(double X,double Y) : JvSprite(X,Y)
{
	setCollide(false);
	loadGraphic("flyobj.png");

	_movey = 0;
	velocity.y = 5;
}

void FlyObj::update()
{
	if(overlaps(GameState::heroP)){
		kill();
		GameState::heroP->changeToFlyMan();
		JvG::play("eat.wav",1);
	}

	if (velocity.y>0)
	{
		_movey++;
		if (_movey>50)
		{
			velocity.y = -5;
		}
	}
	else if (velocity.y<0)
	{
		_movey--;
		if (_movey<=0)
		{
			velocity.y = 5;
		}
	}
	
	JvSprite::update();
}