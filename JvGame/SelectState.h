#ifndef _SELECTSTATE_H
#define _SELECTSTATE_H

#include "JvGame/JvState.h"

class SelectState : public JvState
{
public:
	SelectState(bool isMusic=true);
	virtual void create();
	virtual void update();
protected:
	JvSprite* _bg;

	JvGroup* _bgTileGroup;
	
	int _bgTileW;
	int _bgTileWNum;
	int _bgTileHNum;
	int _bgTileNum;

	bool _isMusic;
private:
};

#endif