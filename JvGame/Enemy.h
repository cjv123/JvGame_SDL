#ifndef _ENEMY_H
#define _ENEMY_H

#include "JvGame/JvSprite.h"

class JvEmitter;

class Enemy : public JvSprite
{
public:
	Enemy(double X,double Y);
	virtual void update();
	virtual void kill();
	virtual void hitLeft(JvObject* Contact,double Velocity);
	virtual void hitRight(JvObject* Contact,double Velocity);
	virtual void hitTop(JvObject* Contact,double Velocity);
	virtual void hitBottom(JvObject* Contact,double Velocity);
protected:
	JvEmitter* emitter_em;
private:
};

#endif