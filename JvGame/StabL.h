#ifndef _STABL_H
#define _STABL_H

#include "JvGame/JvSprite.h"

class StabL : public JvSprite
{
public:
	StabL(double X,double Y);
	virtual void hitLeft(JvObject* Contact,double Velocity);
	virtual void hitRight(JvObject* Contact,double Velocity);
protected:
private:
};

#endif