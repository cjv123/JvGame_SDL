#include "JvTextPad.h"
#include "JvH.h"

JvTextPad::JvTextPad(double X, double Y,double Width,double Height,
					 const char* FontFilename ,const char* Text)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	_bgColor = MAKE_RGBA_8888(0,0,0,180);
	_isShow = false;
	_text = new JvText(x+15,y+10,Width-10,Height-10,FontFilename,Text);
	_text->setLineHeight(5);
	_text->visible = false;
	_text->scrollFactor.x = _text->scrollFactor.y =0;
	origin.x = x + width/2;
	origin.y = y + height/2;
	_w = 0;
	_h = 0;
	add(_text);
	name = "textpad";
	
}



JvTextPad::~JvTextPad()
{
}


void JvTextPad::update()
{
	JvGroup::update();
	
}

void JvTextPad::render()
{
	if (!_isShow)
		return;
	
	if (((width - _w)<10) || ((height-_h)<10))
	{
		_w = width;
		_h = height;
		_text->visible = true;
	}
	else
	{
		_w+=(width - _w)*0.07;
		_h+=(height - _h)*0.07;
		_x = origin.x - _w/2;
		_y = origin.y - _h/2;
	}
	
	//FillRect(_x,_y,_w,_h,_bgColor,DISPLAY_PIXEL_FORMAT_4444);
	int r, g, b, a;
	GET_RGBA_8888(_bgColor, r, g, b, a);
	SDL_SetRenderDrawColor(JvG::jvGameP->getSDLRenderer(), r, g, b, a);
	SDL_Rect rect{_x,_y,_w,_h};
	SDL_RenderFillRect(JvG::jvGameP->getSDLRenderer(),&rect);

	
	JvGroup::render();
}

void JvTextPad::setText(const char* Text)
{
	string txt = Text;
	_text->setText(txt);
}

void JvTextPad::setTextColor(int Color)
{
	_text->setColor(Color);
}

void JvTextPad::setBgColor(int Color)
{
	_bgColor = Color;
}

void JvTextPad::setFont(const char* FontFilename)
{
	_text->setFont(FontFilename);
}

void JvTextPad::show()
{
	_isShow = true;
}

void JvTextPad::close()
{
	_isShow = false;
	_text->visible = false;
}

void JvTextPad::setLineHight(int LineHight)
{
	_text->setLineHeight(LineHight);
}

void JvTextPad::setTextSize(int Size)
{
	_text->setSize(Size);
}

void JvTextPad::setTextPostion(int TargetX,int TargetY)
{
	_text->x += TargetX;
	_text->y += TargetY;
}