#include "StabR.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

StabR::StabR(double X,double Y) : JvSprite(X,Y)
{
	SetFixed(true);
	loadGraphic("stab_tile_r.png");
}


void StabR::hitRight(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="man"){
		GameState::heroP->dieBomb();
		
	}
	
	JvSprite::hitRight(Contact,Velocity);
}