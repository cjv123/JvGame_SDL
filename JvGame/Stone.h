#ifndef _STONE_H
#define _STONE_H

#include "JvGame/JvSprite.h"

class JvEmitter;

class Stone : public JvSprite
{
public:
	Stone(double X,double Y);
	virtual void update();
	virtual void kill();
	virtual void hitLeft(JvObject* Contact,double Velocity);
	virtual void hitRight(JvObject* Contact,double Velocity);
	virtual void hitTop(JvObject* Contact,double Velocity);
	virtual void hitBottom(JvObject* Contact,double Velocity);
protected:
	JvEmitter* emitter;
private:
};
#endif