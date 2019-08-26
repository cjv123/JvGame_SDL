#ifndef _HOMESTATE_H
#define _HOMESTATE_H

#include "JvGame/JvState.h"
class JvSprite;
class JvGroup;
class JvButton;

class HomeState : public JvState
{
public:
	HomeState(bool isMusic=true);
	virtual void create();
	virtual void update();

	void updateArrow();
protected:
	JvSprite* _bg;
	JvSprite* _arrow;
	JvButton* _startButton;
	JvButton* _createButton;

	JvGroup* _bgTileGroup;


	int _curSelectIndex;

	int _bgTileW;
	int _bgTileWNum;
	int _bgTileHNum;
	int _bgTileNum;
	
	bool _isMusic;
private:
};

#endif