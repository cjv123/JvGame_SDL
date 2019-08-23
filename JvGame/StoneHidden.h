#ifndef _STONEHIDDEN_H
#define _STONEHIDDEN_H

#include "Stone.h"

class StoneHidden : public Stone
{
public:
	StoneHidden(double X,double Y);
	virtual void update();
	virtual void hitBottom(JvObject* Contact,double Velocity);
protected:
private:
};

#endif