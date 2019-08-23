#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#include "JvGame/JvGroup.h"

class JvButton;

class GamePad : public JvGroup
{
public:
	GamePad();
	void flyMode();
	void walkMode();
	void hasBall();
protected:
	JvButton* _leftButton;
	JvButton* _rightButton;
	JvButton* _jumpButton;
	JvButton* _ballButton;

	JvButton* _fLeftButton;
	JvButton* _fRightButton;
	JvButton* _fUpButton;
	JvButton* _fDownButton;
private:
};

#endif