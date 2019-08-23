#ifndef _STABR_H
#define _STABR_H

#include "JvGame/JvSprite.h"

class StabR : public JvSprite
{
public:
	StabR(double X,double Y);
	virtual void hitRight(JvObject* Contact,double Velocity);
protected:
private:
};

#endif