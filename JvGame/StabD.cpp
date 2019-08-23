#include "StabD.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

StabD::StabD(double X,double Y) : JvSprite(X,Y)
{
	SetFixed(true);
	loadGraphic("stab_d.png");
}


void StabD::hitBottom(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="man"){
		GameState::heroP->dieBomb();
		
	}
	
	JvSprite::hitBottom(Contact,Velocity);
}