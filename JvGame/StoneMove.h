#ifndef _STONEMOVE_H
#define _STONEMOVE_H

#include "Stone.h"

class StoneMove : public Stone
{
public:
	StoneMove(double X,double Y);
	virtual void update();
protected:
private:
	int _mx;
	double _x;
	double _y;
	double _my;
};

#endif