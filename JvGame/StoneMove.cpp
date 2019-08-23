#include "StoneMove.h"
#include "JvGame/JvH.h"

StoneMove::StoneMove(double X,double Y) : Stone(X,Y)
{
	_mx = 50*2;
	_my = 0;
	velocity.x=20*2;
	velocity.y=0;
	_x=X;
	_y=Y;
}

void StoneMove::update()
{
	if(x-_x>_mx)
	{
		x=_x+_mx;
		velocity.x=-velocity.x;
	}
	else if(x<_x)
	{
		x=_x;
		velocity.x=-velocity.x;
	}
	
	if(_y-y>_my)
	{
		y=_y-_my;
		velocity.y=-velocity.y;
	}
	else if(y>_y)
	{
		y=_y;
		velocity.y=-velocity.y;
	}
	Stone::update();
}