#ifndef _STONEMOVED_H
#define _STONEMOVED_H

#include "Stone.h"

class StoneMoveD : public Stone
{
public:
	StoneMoveD(double X, double Y);
	virtual void update();
protected:
private:
	int _mx;
	double _x;
	double _y;
	double _my;
};

#endif