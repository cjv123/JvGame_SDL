#include "CreateState.h"
#include "JvGame/JvH.h"
#include "HomeState.h"
#include "GameState.h"

static void create_back_callback(int par)
{
	JvG::switchState(new HomeState(false));
}

void CreateState::create()
{
	setBgColor(MAKE_RGBA_8888(87,196,247,255));
	_bg = new JvSprite(40,-100);
	_bg->loadGraphic("bg_non.png");
	add(_bg);
	_bg->velocity.x = -30;
	
	JvSprite* buttonSprite = new JvSprite;
	buttonSprite->loadGraphic("homebutton.png");
	JvSprite* buttonSpSel = new JvSprite;
	buttonSpSel->loadGraphic("homebutton_sel.png");
	JvButton* startButton = new JvButton(JvG::width/2-buttonSprite->width/2,JvG::height-JvG::height/4,
		buttonSprite->width,buttonSprite->height);
	startButton->loadGraphic(buttonSprite,buttonSpSel);
	startButton->setTitle("MAIN MENU",FONT_NAME);
	startButton->setCallback(create_back_callback);
	add(startButton);
	

	JvTextPad* text = new JvTextPad(JvG::width/2-160/2,10,160,90,FONT_NAME,"               CREATES\n\
Game designer: Jianwei Chen\nProgrammer: Jianwei Chen\nArt: Chu He\nGame engine: JvGame\n\Power by ZF stdio 2012.");
	text->setTextSize(8);
	text->setLineHight(8);
	//text->setTextPostion(5,0);
	text->show();
	add(text);
}

void CreateState::update()
{
	if (_bg->x<=-_bg->width+20)
	{
		_bg->x = JvG::width;
	}
	JvState::update();
}
