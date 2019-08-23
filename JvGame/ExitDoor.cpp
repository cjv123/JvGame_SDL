#include "ExitDoor.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "Hero.h"
#include "PassState.h"

ExitDoor::ExitDoor(double X,double Y) : JvSprite(X,Y)
{
	loadGraphic("door.png");
	setCollide(false);
}

void ExitDoor::update()
{
	if(GameState::heroP->x>x && 
		(GameState::heroP->x+GameState::heroP->width)<(x+width) &&
		overlaps(GameState::heroP) && 
		GameState::heroP->onFloor
		){    
		//if(JvG::joystick->isJustPreess(UPCODE)){
			
			if(GameState::isGetKey)
			{
				if(GameState::nowLv<28)
				{
					if (GameState::gameData->level[GameState::nowLv] == LVLOCK)
					{
						GameState::gameData->level[GameState::nowLv] = LVOPEN;
					}
				} 

				if (GameState::gameData->level[GameState::nowLv - 1]!=STARPASS)
				{
					GameState::gameData->level[GameState::nowLv - 1] = LVPASS;
					if (GameState::isGetStar)
					{
						GameState::gameData->level[GameState::nowLv - 1] = STARPASS;
					}
					JvG::save->save(GameState::gameData,sizeof(GameData));
				}
				GameState::isGetKey = false;
				JvG::switchState(new PassState);
			}
			else
			{
				JvG::play("ding.wav",1);
			}
		//}
	}
	JvSprite::update();
}