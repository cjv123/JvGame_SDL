#ifndef _JVGAME_H
#define _JVGAME_H

#include "JvJoystick.h"

class JvState;

/**
*入口
*可以定义一个此类型的全局变量
*/
class JvGame
{
public:
	/**
	 *构造函数
	 *@param unsigned int GameSizeX,屏幕宽度
	 *@param unsigned int GameSizeY,屏幕高度
	 *@return void
	 */
	JvGame(unsigned int GameSizeX,unsigned int GameSizeY);

	JvGame();

	virtual ~JvGame();

	void setScreenInfo(unsigned int Width,unsigned int Height);
	
	/**
	 *设置初始场景
	 *@param JvState* initState,初始state的指针
	 *@return void
	 */
	void setInitState(JvState* initState);

	/**
	 *开始运行
	 *@return void
	 */
	void run();

	/**
	 *停止运行
	 *@return void
	 */
	void stopRun();

	/**
	 *退出程序
	 *@return void
	 */
	void exit();

	/**
	 *切换场景
	 *@param JvState* StateP,待切换的state
	 *@return void
	 */
	void switchState(JvState* StateP);

	/**
	 *在主循环里调用update()
	 *@return bool,停止运行时发挥false，否则true
	 */
	bool update();
	
	void create();
	void btnDown(KEYCODE keycode);
	void btnUp(KEYCODE keycode);
	void mouseClick(int type,int x,int y);
	void mouseMove(int x,int y);

	SDL_Window* getSDLWindow();
	SDL_Renderer* getSDLRenderer();

protected:
	bool _run;
	
	double _total;
	double _elapsed;

	JvState* _delState;
	JvState* _switchState;

	SDL_Window* _SDLWindow;
	SDL_Renderer* _SDLRenderer;
};

#endif