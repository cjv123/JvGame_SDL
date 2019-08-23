#ifndef _PASSSTATE_H
#define _PASSSTATE_H

#include "JvGame/JvState.h"
class JvSprite;
class JvText;
class JvButton;

class PassState : public JvState
{
public:
	virtual void create();
	virtual void update();
protected:

private:
	JvSprite* hero;
	JvSprite* heroFly;
	int time;
	JvText* txt;

	JvButton* exitButton;
	JvButton* nextButton;
	JvSprite* bBg;
	JvText* gameoverTile;
};

#endif

