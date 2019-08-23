#include "ClimbItem.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

ClimbItem::ClimbItem(double X,double Y) : JvSprite(X,Y)
{
	setCollide(false);
	loadGraphic("clibitem.png");

	_isPlayAnima = false;
	_frames = 0;
	
	_movey = 0;
	velocity.y = 5;
	_alpha = 255;
	_ox = X + width/2;
	_oy = Y + height/2;
}

void ClimbItem::update()
{
	if (overlaps(GameState::heroP))
	{
		if (!_isPlayAnima)
		{
			_isPlayAnima = true;
			JvG::play("eat.wav",1);
		}
	}

	if (_isPlayAnima)
	{
		if (_frames>=30)
			kill();
		
		setScale(_scale+0.1);
		_alpha-=5;
		setMask(MAKE_RGBA_8888(255,255,255,_alpha));
		x = _ox - width/2;
		y = _oy - height/2;
		
		//printf("%lf,%lf\n",x,y);
		
		_frames++;
		JvSprite::update();
		return;
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

void ClimbItem::kill()
{
	if(dead) 
		return;
	GameState::heroP->hasClib();
	JvSprite::kill();
}