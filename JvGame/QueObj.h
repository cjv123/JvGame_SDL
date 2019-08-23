#ifndef _QUEOBJ_H
#define _QUEOBJ_H

#include "JvGame/JvSprite.h"
class JvTextPad;

class QueObj : public JvSprite
{
public:
	QueObj(double X,double Y,JvTextPad* Text = NULL,JvSprite* Item=NULL);
	virtual void update();
	virtual void hitBottom(JvObject* Contact,double Velocity);
protected:
	JvTextPad* _text;
	JvSprite* _item;
	bool _isHit;
	double _y;
private:
};

#endif