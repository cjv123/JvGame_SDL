#ifndef _JOYSTICK_H
#define _JOYSTICK_H
#include <map>
using namespace std;

#include "JvGroup.h"

enum KEYCODE{NONE,UPCODE,DOWNCODE,LEFTCODE,RIGHTCODE,ACODE,BCODE,XCODE,YCODE};
enum KEYSTATUS{NOPRESS,JUSTPRESS,PRESS};
enum MOUSESTATUS{MOUSENONE,MOUSEDOWN,MOUSEUP,MOUSEMOVE};

typedef map<KEYCODE,KEYSTATUS> KeyMapType;

struct MousePoint
{
	int x;
	int y;
	MOUSESTATUS status;
	int id;

	MousePoint()
	{
		x = y = -1;
		status = MOUSENONE;
		id = -1;
	}
};

/**
*输入设备
*提供一些输入的判定函数
*/
class JvJoystick : public JvGroup
{
public:
	JvJoystick();
	virtual ~JvJoystick();
	void pressDown(KEYCODE keycode);
	void pressUp(KEYCODE keycode);
	void mouseDown(int x, int y,int id = 0);
	void mouseUp(int x,int y,int id = 0);
	void mouseMove(int x,int y,int id =0);
	MousePoint* getMousePoint();
	void reSet();
	
	/**
	 *判断是否按键被按下
	 *@param KEYCODE keycode,哪个按键
	 *@return bool
	 */
	bool isPress(KEYCODE keycode);

	/**
	 *判断是否按键正被按下(长按只能响应一次)
	 *@param KEYCODE keycode,哪个按键
	 *@return bool
	 */
	bool isJustPreess(KEYCODE keycode);

	/**
	 *判断鼠标被按下
	 *@return bool
	 */
	bool isMouseDown();

	/**
	 *判断鼠标在某矩形区域按下
	 *@param JvRect Rect,矩形
	 *@return bool
	 */
	bool isMouseDown(JvRect Rect);

	/**
	 *判断鼠标是否clickup
	 *@return bool
	 */
	bool isMouseUp();

	/**
	 *判断鼠标在某矩形区域clickup
	 *@param JvRect Rect,矩形
	 *@return bool
	 */
	bool isMouseUp(JvRect Rect);


	/**
	 *判断是否有某点正在点击(触摸)屏幕上
	 *@param JvRect Rect,矩形
	 *@return bool
	 */
	bool isMouseIn(JvRect Rect);

	void updatePoints(int index,int id,int x, int y);

	void clearPoints();
	
	virtual void update();
protected:
//	pointf _mousePoint;
//	MOUSESTATUS _mouseStatus;
	MousePoint _mousePoint[5];
	int _pointIndex;

	KeyMapType _keyMap;
private:
};

#endif