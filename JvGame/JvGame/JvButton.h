#ifndef _JVBUTTON_H
#define _JVBUTTON_H

#include "JvGroup.h"

class JvSprite;
class JvText;

typedef void (*BUTTON_CALLBACK)(int);
typedef void (*BUTTON_DOWN_CALLBACK)(int);

/**
*按钮
*可以在场景内添加的按钮，可以通过鼠标触发事件
*/
class JvButton : public JvGroup
{
public:
	JvButton(double X,double Y,double Width,double Height);

	/**
	 *加载图形
	 *@param JvSprite* ImageP,常态下的sprite
	 *@param JvSprite* ImageHighlightP=NULL,高亮sprite
	 *@return JvButton* 返回this，方便链式调用
	 */
	JvButton* loadGraphic(JvSprite* ImageP,JvSprite* ImageHighlightP=NULL);

	/**
	 *设置回调函数指针
	 *@param BUTTON_CALLBACK Fun,鼠标clickup后触发的函数
	 *@param BUTTON_DOWN_CALLBACK DFun = NULL,鼠标clickdown就触发的函数
	 *@return void
	 */
	void setCallback(BUTTON_CALLBACK Fun,BUTTON_DOWN_CALLBACK DFun = NULL,
		int ParCallBack=0,int ParDown = 0);

	void setTitle(const char* Title,const char* FontFilename,int X=0,int Y=0,
		int Size = 8);

	void setPosition(int X,int Y);

	virtual void  update();
protected:
	JvSprite* _offP;
	JvSprite* _onP;
	bool _isPress;
	BUTTON_CALLBACK _callBackFun;
	BUTTON_DOWN_CALLBACK _downCallBackFun;
	int _parCallBack;
	int _parDown;
	
	JvText* _text;
	int _textX;
	int _textY;
private:
};

#endif