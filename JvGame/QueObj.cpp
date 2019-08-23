#include "QueObj.h"
#include "JvGame/JvH.h"
#include "GameState.h"

QueObj::QueObj(double X,double Y,JvTextPad* Text,JvSprite* Item) : JvSprite(X,Y)
{
	_isHit = false;
	_text = NULL;
	_item = NULL;
	
	if(Item !=NULL)
	{
		_item = Item;
		_item->visible = false;
	}

	if (Text!=NULL)
	{
		_text = Text;
		_text->visible = false;
	}

	_y = Y;
	SetFixed(true);
	loadGraphic("object_tile.png",true,false,16,16);
	vector<int> normalAnim;
	normalAnim.push_back(0);
	normalAnim.push_back(1);
	normalAnim.push_back(2);
	normalAnim.push_back(3);
	addAnimation("normal",normalAnim,5);
	vector<int> eatAnim;
	eatAnim.push_back(4);
	addAnimation("eated",eatAnim,0);
}

void QueObj::update()
{
	if (!_isHit)
	{
		play("normal");
	}
	else
	{
		play("eated");
	}

	if (_y-y>8)
	{
		velocity.y = 100;
		if (!_isHit)
		{
			JvG::pause = true;
			_isHit = true;
		}
	}
	if (_y-y<0)
	{
		velocity.y = 0;
		y = _y;
	}

	JvSprite::update();
}

void QueObj::hitBottom(JvObject* Contact,double Velocity)
{
	if (!_isHit)
	{
		//_isHit = true;
		if (_item != NULL)
		{
		//	_item->x = x;
		//	_item->y = y - height - 10;
			_item->visible = true;
		}

		if (_text != NULL)
		{
			_text->show();
			_text->visible = true;
			GameState::nowShowTextPad = _text;
		}
	}

	if (velocity.y == 0)
	{
		velocity.y = -60;
	}

	JvSprite::hitBottom(Contact,Velocity);
}

