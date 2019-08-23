#ifndef _STABD_H
#define _STABD_H

#include "JvGame/JvSprite.h"

class StabD : public JvSprite
{
public:
	StabD(double X,double Y);
	virtual void hitBottom(JvObject* Contact,double Velocity);
protected:
private:
};

#endif