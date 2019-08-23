#ifndef _FLYOBJ_H
#define _FLYOBJ_H

#include "JvGame/JvSprite.h"

class FlyObj : public JvSprite
{
public:
	FlyObj(double X,double Y);
	virtual void update();
protected:
	int _movey;
private:
};

#endif