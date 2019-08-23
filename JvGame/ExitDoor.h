#ifndef _EXITDOOR_H
#define _EXITDOOR_H

#include "JvGame/JvSprite.h"

class ExitDoor : public JvSprite
{
public:
	ExitDoor(double X,double Y);
	virtual void update();
protected:
private:
};

#endif