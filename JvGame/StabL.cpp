#include "StabL.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

StabL::StabL(double X,double Y) : JvSprite(X,Y)
{
	SetFixed(true);
	loadGraphic("stab_tile_l.png");
}


void StabL::hitLeft(JvObject* Contact,double Velocity)
{

	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="man"){
		GameState::heroP->dieBomb();
		
	}
	//printf("hitLeft\n");
	
	JvSprite::hitLeft(Contact,Velocity);
}

void StabL::hitRight(JvObject* Contact,double Velocity)
{
	//printf("hitRight\n");
	JvSprite::hitRight(Contact,Velocity);
}