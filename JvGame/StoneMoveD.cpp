#include "StoneMoveD.h"
#include "JvGame/JvH.h"

StoneMoveD::StoneMoveD(double X,double Y) : Stone(X,Y)
{
	_mx = 0;
	_my = 70*2;
	velocity.x=0;
	velocity.y=20*2;
	_x=X;
	_y=Y;
}

void StoneMoveD::update()
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