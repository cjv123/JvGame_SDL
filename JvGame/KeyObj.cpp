#include "keyObj.h"
#include "JvGame/JvH.h"
#include "Hero.h"
#include "GameState.h"

KeyObj::KeyObj(double X,double Y) : JvSprite(X,Y)
{
	_isPlayAnim = false;
	_animFrame = 0;

	loadGraphic("key.png");
	setCollide(false);

	_em = new JvEmitter;
	JvG::stateP->add(_em);
	//	_em->delay = 3;
	_em->setXSpeed(-280,280);
	_em->setYSpeed(-350,150);
	_em->setSize(5,5);
	_em->createSprites("gibs.png",10,0,true,0);

}

void KeyObj::update()
{
	if(overlaps(GameState::heroP)){
		_isPlayAnim = true;
		GameState::isGetKey=true;
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
			x+=(GameState::hasKeyObj->x - x)*0.07;
			y+=(GameState::hasKeyObj->y - y)*0.07;
		}
		else
		{
			setScale(_scale+0.1);
		}

		
		if (JvU::abs(GameState::hasKeyObj->x - x)<1 
			|| JvU::abs(GameState::hasKeyObj->y - x)<1)
		{
			GameState::hasKeyObj->visible = true;
			_isPlayAnim = false;
			kill();
		}
		_animFrame++;
	}
	
	JvSprite::update();
}