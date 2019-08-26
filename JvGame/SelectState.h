#ifndef _SELECTSTATE_H
#define _SELECTSTATE_H

#include "JvGame/JvState.h"

JvButton;

class SelectState : public JvState
{
public:
	SelectState(bool isMusic=true);
	virtual void create();
	virtual void update();
protected:
	void updateSelectButton();

	JvSprite* _bg;

	JvGroup* _bgTileGroup;


	
	int _bgTileW;
	int _bgTileWNum;
	int _bgTileHNum;
	int _bgTileNum;

	int _curSelectLv;
	int _curMaxLv;
	JvButton* _curSelectButton;
	JvButton* _selectButtons[28];

	bool _isMusic;
private:
};

#endif