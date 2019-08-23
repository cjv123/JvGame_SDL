#include "Stab.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

Stab::Stab(double X,double Y) : JvSprite(X,Y)
{
	_timer=0;
	_isHide=false;
	SetFixed(true);
	loadGraphic("stab_tile.png");
}

void Stab::update()
{
	if(_isHide)
	{
		_timer++;
		if(_timer>120){
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
	JvSprite::update();
}


void Stab::hitTop(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="man"){
		GameState::heroP->dieBomb();
		
	}
	
	JvSprite::hitTop(Contact,Velocity);
}