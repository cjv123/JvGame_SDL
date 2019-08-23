#ifndef _CLIMBITEM
#define _CLIMBITEM

#include "JvGame/JvSprite.h"

class ClimbItem : public JvSprite
{
public:
	ClimbItem(double X,double Y);
	virtual void update();
	virtual void kill();
protected:
	bool _isPlayAnima;
	int _frames;
	int _movey;
	int _alpha;
	double _ox;
	double _oy;
private:
};

#endif