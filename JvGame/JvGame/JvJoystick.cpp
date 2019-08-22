#include "JvJoystick.h"

JvJoystick::JvJoystick()
{
	_keyMap.insert(KeyMapType::value_type(UPCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(DOWNCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(LEFTCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(RIGHTCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(ACODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(BCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(XCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(YCODE,NOPRESS));
	
	_pointIndex = 0;
}

JvJoystick::~JvJoystick()
{

}


void JvJoystick::pressDown(KEYCODE keycode)
{
	if(_keyMap.find(keycode)==_keyMap.end())
		return;

	if(_keyMap[keycode] == NOPRESS)
	{
		_keyMap[keycode] = JUSTPRESS;
	//	printf("justpress\n");
	}
	else if (_keyMap[keycode] == JUSTPRESS)
	{
		_keyMap[keycode] = PRESS;
	//	printf("press\n");
	}
}

void JvJoystick::pressUp(KEYCODE keycode)
{
	if(_keyMap.find(keycode)==_keyMap.end())
		return;
	_keyMap[keycode] = NOPRESS;
}

bool JvJoystick::isPress(KEYCODE keycode)
{
	if(_keyMap.find(keycode)==_keyMap.end())
		return false;

	if (_keyMap[keycode] == JUSTPRESS || _keyMap[keycode] == PRESS)
	{
		return true;
	}
	return false;
}

bool JvJoystick::isJustPreess(KEYCODE keycode)
{
	if(_keyMap.find(keycode)==_keyMap.end())
		return false;

	if (_keyMap[keycode] == JUSTPRESS)
	{
		_keyMap[keycode] = PRESS;
		return true;
	}
	return false;
}

void JvJoystick::mouseDown(int x, int y, int id)
{
	//printf("mousedown x=%d,y=%d\n",x,y);

	for (int i=0;i<5;i++)
	{
		if (_mousePoint[i].id == id)
		{
			_mousePoint[i].x = x;
			_mousePoint[i].y = y;
			_mousePoint[i].status = MOUSEDOWN;
			return;
		}
	}
	
	for (int i=0;i<5;i++)
	{
		if (_mousePoint[i].status == MOUSENONE)
		{
			_mousePoint[i].x = x;
			_mousePoint[i].y = y;
			_mousePoint[i].id = id;
			_mousePoint[i].status = MOUSEDOWN;
			break;
		}
	}
}

void JvJoystick::mouseUp(int x,int y, int id)
{
	//printf("mouseup x=%d,y=%d\n",x,y);
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].id == id || (_mousePoint[i].x == x && _mousePoint[i].y==y))
		{
			_mousePoint[i].x = x;
			_mousePoint[i].y = y;
			_mousePoint[i].status = MOUSEUP;
			break;
		}
	}
}

void JvJoystick::mouseMove(int x,int y,int id)
{
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].id == id)
		{
			//printf("mousemove x=%d,y=%d\n",x,y);
			_mousePoint[i].x = x;
			_mousePoint[i].y = y;
			_mousePoint[i].status = MOUSEMOVE;
			if (_mousePoint[i].x<=0 || _mousePoint[i].y<=0 || _mousePoint[i].x>=JvG::width || _mousePoint[i].y>=JvG::height)
			{
				_mousePoint[i].status = MOUSEUP;
			}
			break;
		}
	}

}


/*vitrual*/
void JvJoystick::update()
{
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].status == MOUSEUP)
		{
			_mousePoint[i].x = -1;
			_mousePoint[i].y = -1;
			_mousePoint[i].status = MOUSENONE;
		}

	}

}

MousePoint* JvJoystick::getMousePoint()
{
	return _mousePoint;
}

bool JvJoystick::isMouseDown()
{
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].status == MOUSEDOWN)
		{
			return true;
		}
	}
	return false;
}

bool JvJoystick::isMouseDown(JvRect Rect)
{
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].status == MOUSEDOWN && Rect.checkPointIn(_mousePoint[i].x,_mousePoint[i].y))
		{
			return true;
		}
	}

	return false;
}

bool JvJoystick::isMouseUp()
{
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].status == MOUSEUP)
		{
			return true;
		}
	}
	return false;
}

bool JvJoystick::isMouseUp(JvRect Rect)
{
	int i=0;
	for (;i<5;i++)
	{
		if (_mousePoint[i].status == MOUSEUP && Rect.checkPointIn(_mousePoint[i].x,_mousePoint[i].y)
				)
		{
			return true;
		}
	}
	return false;

}

bool JvJoystick::isMouseIn(JvRect Rect)
{
	int i=0;
	for (;i<5;i++)
	{
		if (Rect.checkPointIn(_mousePoint[i].x,_mousePoint[i].y))
		{
			return true;
		}
	}
	return false;

}

void JvJoystick::reSet()
{
	int i=0;
	for (;i<5;i++)
	{
		_mousePoint[i].x=-1;
		_mousePoint[i].y=-1;
		_mousePoint[i].status = MOUSENONE;
		_mousePoint[i].id = -1;
	}

	KeyMapType::iterator it = _keyMap.begin();
	for (;it!=_keyMap.end();it++)
	{
		it->second = NOPRESS;
	}
}

void JvJoystick::updatePoints(int index,int id,int x, int y)
{
	_mousePoint[index].x=x;
	_mousePoint[index].y=y;
	if(x<0 || y<0)
	{
		_mousePoint[index].status = MOUSENONE;
		_mousePoint[index].id = -1;
		return;
	}
	if (_mousePoint[index].status == MOUSENONE)
	{
		_mousePoint[index].status = MOUSEDOWN;
	}
	else
	{
		_mousePoint[index].status = MOUSEMOVE;
	}
	_mousePoint[index].id = id;
}

void JvJoystick::clearPoints()
{
	int i=0;
	for (;i<5;i++)
	{
		_mousePoint[i].x=-1;
		_mousePoint[i].y=-1;
		_mousePoint[i].status = MOUSENONE;
		_mousePoint[i].id = -1;
	}
}
