#ifndef _STARTSTATE_H
#define _STARTSTATE_H

#include "JvGame/JvState.h"

class JvSprite;
class JvText;

class StartState : public JvState
{
public:
	StartState();
	virtual void create();
	virtual void update();

protected:
	JvSprite* _ui;
	JvText* _txt;
	int _time;
private:
};

#endif
