#ifndef _STONEHIDDENSHOW_H
#define _STONEHIDDENSHOW_H

#include "Stone.h"

class StoneHiddenShow : public Stone
{
public:
	StoneHiddenShow(double X,double Y);
	virtual void update();
protected:
private:
	int _timer;
};

#endif