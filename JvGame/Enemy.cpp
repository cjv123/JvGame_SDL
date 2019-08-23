#include "Enemy.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"



Enemy::Enemy(double X,double Y) : JvSprite(X,Y)
{
	emitter_em = new JvEmitter;
	JvG::stateP->add(emitter_em);
	emitter_em->delay = 3;
	emitter_em->setXSpeed(-80,80);
	emitter_em->setYSpeed(-200,0);
	emitter_em->setRotation(-360,-360);
	emitter_em->setSize(5,5);
	emitter_em->createSprites("gibs.png",25,16,true,0);

	velocity.x = 50;
	acceleration.y = 200;
	
	loadGraphic("enemy1.png",true,true,16,16);
	vector<int> moveframes;
	moveframes.push_back(0);
	moveframes.push_back(1);
	addAnimation("move",moveframes,6);

}

void Enemy::update()
{
	if(!onFloor)
	{
		JvSprite::update();
		return;
	}
	
	play("move");
	
	if(velocity.x>0)
	{
		facing=FACERIGHT;
		
		
		if(GameState::tileMap->getTile(JvU::floor(x/GameState::tileMap->getTileWidth())+1,
			JvU::floor((y+height+2)/GameState::tileMap->getTileHeight()))==0 ){
			velocity.x=-velocity.x;
		}
		
	}
	else
	{
		facing=FACELEFT;
		
		if(GameState::tileMap->getTile(JvU::floor(x/GameState::tileMap->getTileWidth()),
			JvU::floor((y+height+2)/GameState::tileMap->getTileHeight()))==0 ){
			velocity.x=-velocity.x;
		}
		
	}
	
	if(JvU::collide(this,(JvObject*)GameState::heroP)){
		if(GameState::heroP->getStatusModel()=="man"){
			GameState::heroP->dieBomb();
		}else{
			kill();
		}
	}
	
	JvSprite::update();
}

void Enemy::kill()
{
	if(dead) return;
	JvSprite::kill();
	
	JvG::camera->shake(0.02f,0.2f);
	
	emitter_em->at(this);
	emitter_em->start();
	
	JvG::play("cai.wav",1);
}

void Enemy::hitLeft(JvObject* Contact,double Velocity)
{
	if(Contact->name =="hero"){
		Hero* herop = (Hero*)Contact;
		if(herop->getStatusModel()=="man"){
			herop->dieBomb();
		}else{
			kill();
		}
		return;
	}
	velocity.x=-velocity.x;
}

void Enemy::hitRight(JvObject* Contact,double Velocity)
{
	if(Contact->name =="hero"){
		Hero* herop = (Hero*)Contact;
		if(herop->getStatusModel()=="man"){
			herop->dieBomb();
		}else{
			kill();
		}
		return;
	}
   velocity.x=-velocity.x;
}

void Enemy::hitTop(JvObject* Contact,double Velocity)
{
	if(Contact->name =="hero"){
		Hero* herop = (Hero*)Contact;
		if(herop->getStatusModel()=="man"){
			herop->dieBomb();
		}else{
			kill();
		}
		return;
	}
	JvSprite::hitTop(Contact,Velocity);
}

void Enemy::hitBottom(JvObject* Contact,double Velocity)
{
	if(Contact==GameState::heroP){
		Hero* herop = (Hero*)Contact;
		if(herop->getStatusModel()=="man"){
			herop->dieBomb();
		}else{
			kill();
		}
		return;
	}
	JvSprite::hitBottom(Contact,Velocity);
}