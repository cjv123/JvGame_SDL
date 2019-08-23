#ifndef _STAB_H
#define _STAB_H

#include "JvGame/JvSprite.h"

class Stab : public JvSprite
{
public:
	Stab(double X,double Y);
	virtual void update();
	virtual void hitTop(JvObject* Contact,double Velocity);
protected:
	int _timer;
	bool _isHide;
private:
	
};

#endif