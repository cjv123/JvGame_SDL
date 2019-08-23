#ifndef _CREATESTATE_H
#define _CREATESTATE_H

#include "JvGame/JvState.h"

class CreateState : public JvState
{
public:
	virtual void create();
	virtual void update();

protected:
	JvSprite* _bg;
private:
};

#endif