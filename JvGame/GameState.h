#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "JvGame/JvState.h"

#ifdef WIN32
#define FONT_NAME "Nokia Cellphone FC"
#else
#define FONT_NAME "nokiafc22.ttf"
#endif

enum{LVLOCK=0,LVOPEN=1,LVPASS=2,STARPASS=3};

struct GameData 
{
	short int level[50];
	unsigned long score;

	GameData()
	{
		score = 0;
		memset(level,0,sizeof(level));
		level[0]=LVOPEN;
		
		int i=0;
		/*
		for (;i<50;i++)
		{
			level[i]=LVOPEN;
		}
		*/
	}
};

class JvTilemap;
class Hero;
class GamePad;
class JvButton;
class JvText;
class JvTextPad;

class GameState : public JvState
{
public:
	GameState();
	virtual ~GameState();
	virtual void create();
	virtual void update();
	virtual void pause();

	static void fail();
	static void success();

	static JvButton* resButton;
	static JvButton* exitButton;
	static JvButton* nextButton;
	static JvButton* backButton;
	static JvSprite* buttonBg;
	static JvText* gameoverTile;
	static JvText* pauseTile;
	static JvTextPad* nowShowTextPad;

	static JvButton* pauseButton;

	static Hero* heroP;
	static int nowLv;
	static JvTilemap* tileMap;
	static bool isGetKey;
	static bool isGetStar;
	static JvSprite* hasKeyObj;
	static JvSprite* hasStarObj;
	static GamePad* gamePad;
	static GameData* gameData;
	
protected:
	bool _isShowMenu;
private:
};

#endif