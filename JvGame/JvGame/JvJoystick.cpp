#include "JvJoystick.h"

JvJoystick::JvJoystick() : _mouseEnable(false)
{
	_keyMap.insert(KeyMapType::value_type(UPCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(DOWNCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(LEFTCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(RIGHTCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(ACODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(BCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(XCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(YCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(STARTCODE,NOPRESS));
	_keyMap.insert(KeyMapType::value_type(SELECTCODE,NOPRESS));
	
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

void JvJoystick::pressDownOrUp(KEYCODE keycode, bool down)
{
	if (down)
	{
		pressDown(keycode);
	}
	else
	{
		pressUp(keycode);
	}
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
		//_keyMap[keycode] = PRESS;
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
	for (; i < 5; i++)
	{
		if (_mousePoint[i].status == MOUSEUP)
		{
			_mousePoint[i].x = -1;
			_mousePoint[i].y = -1;
			_mousePoint[i].status = MOUSENONE;
		}

	}

	KeyMapType::iterator it = _keyMap.begin();
	for (; it != _keyMap.end(); it++)
	{
		if (it->second == JUSTPRESS)
		{
			it->second = PRESS;
		}
	}

}

void JvJoystick::updateSDLInput(SDL_Event& e)
{
	//reSet();
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
		bool down = (e.type == SDL_KEYDOWN);
		//Select surfaces based on key press
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			pressDownOrUp(UPCODE,down);
			break;

		case SDLK_DOWN:
			pressDownOrUp(DOWNCODE,down);
			break;

		case SDLK_LEFT:
			pressDownOrUp(LEFTCODE,down);
			break;

		case SDLK_RIGHT:
			pressDownOrUp(RIGHTCODE,down);
			break;
		
		case SDLK_k:
			pressDownOrUp(ACODE,down);
			break;
		case SDLK_j:
			pressDownOrUp(BCODE,down);
			break;
		case SDLK_i:
			pressDownOrUp(XCODE,down);
			break;
		case SDLK_u:
			pressDownOrUp(YCODE,down);
			break;
		case SDLK_RETURN:
			pressDownOrUp(STARTCODE,down);
			break;
		case SDLK_SPACE:
			pressDownOrUp(SELECTCODE,down);
			break;
		case SDLK_ESCAPE:
			exit(0);
			break;

		default:
			break;
		}
	}
	else if(e.type == SDL_JOYBUTTONDOWN || e.type == SDL_JOYBUTTONUP)
	{
//	    printf("button %d\n",e.jbutton.button);
	    bool down = (e.type == SDL_JOYBUTTONDOWN);
	    if(e.jbutton.button==atoi(JvG::ini["joystick"]["a"].c_str()) || e.jbutton.button==0){
            pressDownOrUp(ACODE,down);
	    }else if(e.jbutton.button==atoi(JvG::ini["joystick"]["b"].c_str()) || e.jbutton.button==1){
            pressDownOrUp(BCODE,down);
	    }else if(e.jbutton.button==atoi(JvG::ini["joystick"]["x"].c_str()) || e.jbutton.button==2){
            pressDownOrUp(XCODE,down);
	    }else if(e.jbutton.button==atoi(JvG::ini["joystick"]["y"].c_str()) || e.jbutton.button==3){
            pressDownOrUp(YCODE,down);
	    }else if(e.jbutton.button==atoi(JvG::ini["joystick"]["start"].c_str()) || e.jbutton.button==6){
            pressDownOrUp(STARTCODE,down);
	    }else if(e.jbutton.button==atoi(JvG::ini["joystick"]["select"].c_str()) || e.jbutton.button==7){
            pressDownOrUp(SELECTCODE,down);
	    }else if(e.jbutton.button==atoi(JvG::ini["joystick"]["exit"].c_str()) || e.jbutton.button==9){
	        exit(0);
        }
	}
	else if(e.type == SDL_JOYHATMOTION)
	{
//	    printf("joyhat:%d\n",e.jhat.value);
        bool down = (e.jhat.value != 0);
        if(down){
            switch(e.jhat.value)
            {
                case SDL_HAT_UP:
                    pressDownOrUp(UPCODE,down);
                    break;
                case SDL_HAT_DOWN:
                    pressDownOrUp(DOWNCODE,down);
                    break;
                case SDL_HAT_LEFT:
                    pressDownOrUp(LEFTCODE,down);
                    break;
                case SDL_HAT_RIGHT:
                    pressDownOrUp(RIGHTCODE,down);
                    break;
            }
        }else{
            pressDownOrUp(UPCODE,down);
            pressDownOrUp(DOWNCODE,down);
            pressDownOrUp(LEFTCODE,down);
            pressDownOrUp(RIGHTCODE,down);
        }

	}
	else if(e.type == SDL_JOYAXISMOTION)
	{
	    const int JOYSTICK_DEAD_ZONE = 8000;
	    int xDir=0;
	    int yDir=0;
	    if(e.jaxis.which==0){
	        //X axis motion
	        if( e.jaxis.axis == 0 )
	        {
	            //Left of dead zone
	            if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
	            {
	                xDir = -1;
	            }
	            //Right of dead zone
	            else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
	            {
	                xDir =  1;
	            }
	            else
	            {
	                xDir = 0;
	            }
	        }
	        //Y axis motion
	        else if( e.jaxis.axis == 1 )
	        {
	            //Below of dead zone
	            if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
	            {
	                yDir = -1;
	            }
	            //Above of dead zone
	            else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
	            {
	                yDir =  1;
	            }
	            else
	            {
	                yDir = 0;
	            }
	        }
	    }
	    if(xDir==0){
            pressDownOrUp(LEFTCODE,false);
            pressDownOrUp(RIGHTCODE,false);
        }else{
            pressDownOrUp((xDir>0)?RIGHTCODE:LEFTCODE,true);
        }
	    if(yDir==0){
            pressDownOrUp(UPCODE,false);
            pressDownOrUp(DOWNCODE,false);
        }else{
            pressDownOrUp((yDir>0)?UPCODE:DOWNCODE,true);
        }
    }
}

bool JvJoystick::isMouseEnable()
{
	return _mouseEnable;
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
