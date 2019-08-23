#include "StoneHiddenShow.h"
#include "JvGame/JvH.h"

StoneHiddenShow::StoneHiddenShow(double X,double Y) : Stone(X,Y)
{
	_timer = 0;
}

void StoneHiddenShow::update()
{
	if(!dead)
	{
		_timer++;
		if(_timer>120)
		{
			_timer=0;
			if(visible)
			{
				visible=false;	
				SetSolid(false);
			}
			else
			{
				visible=true;	
				SetSolid(true);
			}
		}
	}
	Stone::update();
}