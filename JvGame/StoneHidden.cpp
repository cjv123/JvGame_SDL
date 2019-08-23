#include "StoneHidden.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

StoneHidden::StoneHidden(double X,double Y) : Stone(X,Y)
{
	visible = false;
	SetFixed(true);
	collideLeft = collideRight = collideTop = false;

}

void StoneHidden::update()
{
	if (JvU::collide((JvObject*)GameState::heroP,this) && GameState::heroP->getStatusModel()=="ball" 
		&& visible==true)
	{
		kill();
	}
	Stone::update();
}

void StoneHidden::hitBottom(JvObject* Contact,double Velocity)
{
	if (visible == true)
	{
		return;
	}
	visible = true;
	collideLeft = collideRight = collideTop = true;
	
	JvG::play("ding.wav",1);
}