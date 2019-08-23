#include "JvGame/JvH.h"
#include "Coin.h"
#include "GameState.h"
#include "Hero.h"

Coin::Coin(double X,double Y) : JvSprite(X,Y)
{
	_isPlayAnim = false;
	_animFrame = 0;

	setCollide(false);
	loadGraphic("object_tile.png",true,false,16,16);
	vector<int> norAnim;
	norAnim.push_back(11);
	norAnim.push_back(12);
	addAnimation("nor",norAnim,7);
	play("nor");

	_em = new JvEmitter;
	JvG::stateP->add(_em);
	_em->scale = 2;
//	_em->delay = 3;
	_em->setXSpeed(-280,280);
	_em->setYSpeed(-350,150);
	_em->setSize(5,5);
	_em->createSprites("gibs.png",10,0,true,0);
}

void Coin::update()
{
	if (overlaps(GameState::heroP))
	{
		_isPlayAnim = true;
		GameState::isGetStar = true;
		JvG::play("eat.wav",1);
		_em->at(this);
		_em->start();
	}

	if (_isPlayAnim)
	{
		if (_animFrame==0)
		{
			JvPoint point(x,y);
			JvPoint spoint = JvG::camera->toScreenPoint(point);
			x = spoint.x;
			y = spoint.y;
			scrollFactor.x = 0;
			scrollFactor.y = 0;
		}

		if (_animFrame>=40)
		{
			if (_scale!=1)
				setScale(1);
			x+=(GameState::hasStarObj->x - x)*0.07;
			y+=(GameState::hasStarObj->y - y)*0.07;
		}
		else
		{
			setScale(_scale+0.1);
		}

		if (JvU::abs(GameState::hasStarObj->x - x)<1 
			|| JvU::abs(GameState::hasStarObj->y - y)<1)
		{
			GameState::hasStarObj->visible = true;
			_isPlayAnim = false;
			kill();
		}
		_animFrame++;
	}

	JvSprite::update();
}

