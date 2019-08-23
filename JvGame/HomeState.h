#ifndef _HOMESTATE_H
#define _HOMESTATE_H

#include "JvGame/JvState.h"
class JvSprite;
class JvGroup;

class HomeState : public JvState
{
public:
	HomeState(bool isMusic=true);
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