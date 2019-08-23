#include "Stone.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"

Stone::Stone(double X,double Y) : JvSprite(X,Y)
{
	SetFixed(true);
	loadGraphic("stone.png");

	emitter=new JvEmitter;
	JvG::stateP->add(emitter);
	emitter->delay = 3;
	emitter->setXSpeed(-80,80);
	emitter->setYSpeed(-200,0);
	emitter->setRotation(-360,-360);
	emitter->setSize(5,5);
	emitter->createSprites("stone_gibs.png",4,4,true,0);
}

void Stone::update()
{
	JvSprite::update();
}

void Stone::kill()
{
	if(dead)
		return;
	JvSprite::kill();
	
	emitter->at(this);
	emitter->start();
	
	JvG::play("dingstone.wav",1);
}

void Stone::hitLeft(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="ball")
		kill();
}

void Stone::hitRight(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="ball")
		kill();
}

void Stone::hitTop(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="ball")
		kill();
}

void Stone::hitBottom(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP && GameState::heroP->getStatusModel()=="ball")
		kill();
}