#include "StartState.h"
#include "GameState.h"
#include "JvGame/JvH.h"

StartState::StartState()
{
	_time = 0;
	_ui = NULL;
	_txt = NULL;
}

void StartState::create()
{
	setBgColor(MAKE_RGBA_8888(87,196,247,255));

	JvSprite* bg = new JvSprite(0,0);
	bg->loadGraphic("bg.png");
	add(bg);

	_ui = new JvSprite(-87,150);
	_ui->loadGraphic("start.png");
	_ui->x = JvG::width/2 - _ui->width/2;
	_ui->y = JvG::height;
	add(_ui);
	
	char lvstr[10];
	sprintf(lvstr,"Level%d",GameState::nowLv);
	_txt = new JvText(0,0,200,30,FONT_NAME,lvstr);
	_txt->x = JvG::width/2 - _txt->width/2;
	_txt->y = _ui->y+90;
	_txt->setColor(MAKE_RGBA_8888(255,0,0,255));
	_txt->setSize(20);
	add(_txt);
	
	_ui->velocity.y = -160;
	_txt->velocity.y = -160;

	JvG::stopMusic();
}

void StartState::update()
{
	int d = -_ui->height/5;

	JvRect rect(_ui->x,_ui->y,
			_ui->width,_ui->height);
	if (_ui->y>0 && JvG::joystick->isMouseDown(rect))
	{
		_ui->y=d;
		_txt->y=_ui->y+90;
	}

	if (_ui->y<=d)
	{
		_ui->velocity.y=0;
		_txt->velocity.y=0;
		_time++;
		if (_time>=120)
		{
			JvG::switchState(new GameState);
		}
	}

	JvState::update();
}

