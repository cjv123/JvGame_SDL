#ifndef _KEYOBJ_H
#define _KEYOBJ_H

#include "JvGame/JvSprite.h"

class JvEmitter;

class KeyObj : public JvSprite
{
public:
	KeyObj(double X,double Y);
	virtual void update();

protected:
	bool _isPlayAnim;
	int _animFrame;

	JvEmitter* _em;
private:
};

#endif