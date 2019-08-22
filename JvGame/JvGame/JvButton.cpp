#include "JvSprite.h"
#include "JvButton.h"
#include "JvJoystick.h"
#include "JvText.h"

JvButton::JvButton(double X,double Y,double Width,double Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	_callBackFun = NULL;
	_downCallBackFun = NULL;
	_onP = NULL;
	_offP = NULL;
	_isPress = false;
	_text = NULL;
}

void JvButton::setCallback(BUTTON_CALLBACK Fun,BUTTON_DOWN_CALLBACK DFun /* = NULL */,
						   int ParCallBack/* =0 */,int ParDown /* = 0 */)
{
	_callBackFun = Fun;
	if (DFun!=NULL)
	{
		_downCallBackFun = DFun;
	}
	_parCallBack = ParCallBack;
	_parDown = ParDown;
}

JvButton* JvButton::loadGraphic(JvSprite* ImageP,JvSprite* ImageHighlightP/* =NULL */)
{
	_offP = ImageP;
	add(_offP);
	_offP->x = x;
	_offP->y = y;
	_offP->width = width;
	_offP->height = height;
	_offP->scrollFactor.x = _offP->scrollFactor.y = 0.0f;
	_offP->setCollide(false);

	if (ImageHighlightP != NULL)
	{
		_onP = ImageHighlightP;
		_onP->x = x;
		_onP->y = y;
		_onP->width = width;
		_onP->height = height;
		_onP->scrollFactor.x=_onP->scrollFactor.y = 0.0f;
		_onP->setCollide(false);
		add(_onP);
		_onP->visible = false;
	}
	
	return this;
}

void JvButton::update()
{
	if (this->visible == false)
	{
		return;
	}

	JvGroup::update();
	
	JvRect rect(x,y,width,height);
	if (JvG::joystick->isMouseIn(rect))
	{
		if(_onP!=NULL)
			_onP->visible = true;
		if(_onP!=NULL)
			_offP->visible = false;
		
		if ( _isPress == false)
		{
			_isPress = true;
			if (_downCallBackFun)
			{
				_downCallBackFun(_parDown);
			}
		}
	}
	else
	{
		if (_callBackFun != NULL && _isPress == true)
		{
			_callBackFun(_parCallBack);
			_isPress = false;
		}

		if(_onP!=NULL) 
			_onP->visible = false;

		if(_onP!=NULL) 
			_offP->visible = true;
	}
}

void JvButton::setTitle(const char* Title,const char* FontFilename,
						int X/* =0 */,int Y/* =0 */,int Size/* =8*/)
{
	_text = new JvText(x+X,y+Y,width,height,FontFilename,Title);
	_text->setSize(Size);
	_text->scrollFactor.x = _text->scrollFactor.y =0;
	add(_text);
	_textX = X;
	_textY = Y;
}

void JvButton::setPosition(int X,int Y)
{
	_offP->x = X;
	_offP->y = Y;
	_onP->x = X;
	_onP->y = Y;

	if (_text != NULL)
	{
		_text->x = X + _textX;
		_text->y = Y + _textY;
	}
	x = X;
	y = Y;
}