#ifndef _BALLITEM_H
#define _BALLITEM_H

#include "JvGame/JvSprite.h"

class BallItem : public JvSprite
{
public:
	BallItem(double X,double Y);
	virtual void update();
	virtual void kill();
protected:
	bool _isPlayAnima;
	int _frames;
	int _movey;
	int _alpha;
	double _ox;
	double _oy;
};

#endif