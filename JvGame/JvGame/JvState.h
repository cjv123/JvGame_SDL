#ifndef _JVSTATE_H
#define _JVSTATE_H

#include "JvCamera.h"
#include "JvGroup.h"

class JvText;

/**
*场景
*所有object都add到state里，只能同时存在一个场景
*/
class JvState
{
public:
	JvGroup* defaultGroup;
	JvCamera* camera;

	JvState();
	virtual ~JvState();
	virtual void update();
	virtual void create();
	virtual void loading();
	virtual void pause();
	virtual void render();
	void collide();
	

	/**
	 *添加一个object到场景
	 *@param JvObject* ObjectP,待添加对象的指针
	 *@return void
	 */
	void add(JvObject* ObjectP);

	/**
	 *设置背景颜色
	 *@param int Color,背景颜色,用MAKE_RGBA_8888()生成
	 *@return void
	 */
	void setBgColor(int Color);
protected:
	int _bgColor;

private:
};

#endif