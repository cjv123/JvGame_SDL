#include "Hero.h"
#include "JvGame/JvH.h"
#include "GameState.h"
#include "GamePad.h"


Hero::Hero(double X,double Y) : JvSprite(X,Y)
{
	_jumpPower=225;
	_gv=420;
	_moveSpeed=120;
	_statusModel="man";
	_hitWall=false;
	_changeTimer=0;
	_die=false;
	_stands2Timer=0;
	dietimer=0;
	_canClimb = false;
	_canBall = false;
	_dieBombTime = 0;
	name="hero";
	
	acceleration.y =_gv;
	maxVelocity.x = _moveSpeed;
	maxVelocity.y = _jumpPower*1.2;
	drag.x=_moveSpeed*8;

// 	_manImg = image_load("hero.png",DISPLAY_PIXEL_FORMAT_4444,1);
// 	_ballImg = image_load("heroball.png",DISPLAY_PIXEL_FORMAT_4444,1);
// 	_bombImg = image_load("herobomb.png",DISPLAY_PIXEL_FORMAT_4444,1);
// 	_flymanimg = image_load("flyman2.png",DISPLAY_PIXEL_FORMAT_4444,1);

	emitter = new JvEmitter;
	JvG::stateP->add(emitter);
	emitter->delay = 5;
	emitter->setXSpeed(-250,250);
	emitter->setYSpeed(-500,40);
//	emitter->setRotation(-720,-720);
	emitter->setSize(5,5);
	emitter->createSprites("herobomb.png",50,0,true,0.3f);

	_ywsp = new JvSprite(X,Y);
	_ywsp->loadGraphic("yw.png",true,false,28,28);
	vector<int> ywanimation;
	ywanimation.push_back(0);ywanimation.push_back(1);ywanimation.push_back(2);ywanimation.push_back(3);
	ywanimation.push_back(2);ywanimation.push_back(1);ywanimation.push_back(0);
	_ywsp->addAnimation("yw",ywanimation,15);
	JvG::stateP->add(_ywsp);
	_ywsp->visible = false;
	_ywsp->setCollide(false);

	changeToMan();
}

Hero::~Hero()
{

}

void Hero::update()
{

	acceleration.x = 0;
						
	if(_die){
		play("die");
		dietimer++;
		if(dietimer>=180){
			dietimer=0;
			//JvG::switchState(new GameState);
			GameState::fail();
		}
		JvSprite::update();
		return;
	}
	
	if(!onScreen() && velocity.y>0){
		die();
	}

//	printf("%lf,%lf\n",x,y);
	
	if(_statusModel=="flyman"){
		acceleration.y=0;
		drag.x=drag.y=_moveSpeed;
		
		//play("stand_f");
		
		if(JvG::joystick->isPress(LEFTCODE)){
		//	play("move_f");
			facing = FACELEFT;
			acceleration.x -= _moveSpeed;
		}else if(JvG::joystick->isPress(RIGHTCODE)){
		//	play("move_f");
			facing = FACERIGHT;
			acceleration.x += _moveSpeed;
		}
		
		if(JvG::joystick->isPress(UPCODE)){
			acceleration.y -= _moveSpeed;
		}else if(JvG::joystick->isPress(DOWNCODE)){
			acceleration.y += _moveSpeed;
		}

		if (velocity.x !=0 || velocity.y!=0)
		{
			play("move_f");
		}
		else
		{
			play("stand_f");
		}
		
		if (_ywsp->visible == true)
		{
			if (_ywsp->isPlayEnd())
			{
				visible = true;
				_ywsp->visible = false;
			}
			else
			{
				return;
			}
		}

		JvSprite::update();
		return;
	}
	
	
	offset.x=0;
	if(JvG::joystick->isPress(LEFTCODE)){
		facing = FACELEFT;
		
		if(_curAnim){
			if(_statusModel=="man" && _curAnim->name=="hitwall")
				offset.x=2;
			if(_statusModel=="ball") offset.x=-1;
		}
		
		acceleration.x -= drag.x;
	}else if(JvG::joystick->isPress(RIGHTCODE)){
		facing = FACERIGHT;
		acceleration.x += drag.x;
		
		if(_curAnim){
			offset.x=-1;
		
			if(_statusModel=="man" && this->_curAnim->name=="hitwall")
			{
				offset.x=-2;
			}
			if(_statusModel=="ball") offset.x=0;
		}
	}
	
	//Ìø
	if(JvG::joystick->isJustPreess(ACODE))
	{
		if( _hitWall || onFloor){
			velocity.y = -_jumpPower;
			JvG::play("jump.wav",1);
			if(_hitWall){
				velocity.y = -_jumpPower*2;
				if(facing == FACELEFT){
					velocity.x=130*2;
				}else{
					velocity.x=-130*2;
				}
			}
		}
		
	}
	
	
	if(JvG::joystick->isJustPreess(BCODE) && _canBall == true){
		if(_statusModel=="man"){
			if(onFloor){
				_changeTimer=8;
			}else{
				changeToBall();
				_statusModel="ball";
			}
		}else{
			if(GameState::tileMap->getTile(JvU::floor(x/16),JvU::floor(y/16)-1)>0 ||
				GameState::tileMap->getTile(JvU::floor((x+7)/16),JvU::floor(y/16)-1)>0
			)
			{
				return;
			}
			
			if(
				GameState::tileMap->getTile(JvU::floor(x/16)+1,JvU::floor(y/16))>0 &&
				GameState::tileMap->getTile(JvU::floor(x/16)-1,JvU::floor(y/16))>0
			){
				return;
			}
			
			if(_statusModel=="ball" && facing==FACERIGHT && 
				GameState::tileMap->getTile(JvU::floor(x/16)+1,JvU::floor(y/16))>0){
				x-=1;
			}
			changeToMan();
			if(onFloor){
				_changeTimer=8;
			}else{
				_statusModel="man";
			} 
			
		}
	}
	
	

	if(_hitWall){
		velocity.y*=0.6f;
	}

	
	if(_changeTimer>0){
		_changeTimer--;
		play("jump_down");
		if(_changeTimer==0 ){
			if(_statusModel=="man"){
				changeToBall();
			   _statusModel="ball";
			}else{
				_statusModel="man";
			} 
		}
	}
	

	//¶¯×÷
	if(velocity.y != 0 && _changeTimer<=0 && !onFloor)
	{
		
		if(_hitWall){
			play("hitwall");
		}else{
			if(velocity.y<0){
				if(_statusModel=="man"){
					play("jump_up");
				}else{
					play("jump_up_b");
				}
			}else{
				if(_statusModel=="man"){
					play("jump_down");
				}else{
					play("jump_down_b");
				}
			}
		}
		
	}
	else if(velocity.x == 0 && _changeTimer<=0)
	{
		if(_statusModel=="man"){
			play("stand");
		}else{
			play("stand_b");
		}
	}
	else if(_changeTimer<=0)
	{
		
		if(_statusModel=="man"){
			play("move");
		}else{
			play("move_b");
		}
	}
	
	_stands2Timer++;
	if(_curAnim!=NULL && _curAnim->name!="stand") 
		_stands2Timer=0;
	if(_curAnim!=NULL && _curAnim->name=="stand" && _stands2Timer>60){
		play("stand2");
	}

	
	_hitWall=false;
	JvSprite::update();
}

void Hero::kill()
{
	JvSprite::kill();
}

void Hero::hitLeft(JvObject* Contact,double Velocity)
{
	if(_statusModel=="flyman"){
		_statusModel="man";
		changeToMan();
	}
	
	if(_statusModel=="man" && _canClimb){
		_hitWall=true;
	}
	JvSprite::hitLeft(Contact,Velocity);
	//printf("hitleft\n");
}

void Hero::hitRight(JvObject* Contact,double Velocity)
{
	if(_statusModel=="flyman"){
		_statusModel="man";
		changeToMan();
	}
	
	if(_statusModel=="man" && _canClimb){
		_hitWall=true;
	}
	
	/*
	printf("herox:%f,heroy:%f,herox+herowidth:%f\n",x,y,x+width);
	int i=0;
	for (;i<Contact->colOffsets.size();i++)
	{
		printf("objx:%f,objy:%f\n",Contact->colOffsets[i].x,Contact->colOffsets[i].y);
	
	}
	printf("-----------\n");
	*/
//	printf("htiright\n");

	JvSprite::hitRight(Contact,Velocity);
}

void Hero::hitTop(JvObject* Contact,double Velocity)
{
	if(_statusModel=="flyman"){
		_statusModel="man";
		changeToMan();
	}
	JvSprite::hitTop(Contact,Velocity);
//	printf("hittop\n");
}

void Hero::hitBottom(JvObject* Contact,double Velocity)
{
	if(_statusModel=="flyman"){
		_statusModel="man";
		changeToMan();
	}
		
	if(_statusModel=="ball" && velocity.y>80){
		velocity.y=-0.5*velocity.y;
	}else{
		JvSprite::hitBottom(Contact,Velocity);
	}
	
	/*
	printf("herox:%f,heroy:%f,herox+herowidth:%f\n",x,y,x+width);
	int i=0;
	for (;i<Contact->colOffsets.size();i++)
	{
		printf("objx:%f,objy:%f\n",Contact->colOffsets[i].x,Contact->colOffsets[i].y);
		
	}
	printf("-----------\n");
	*/
	//printf("hitbottom\n");
}

void Hero::die()
{
	if(_die)
		return;
	if(_statusModel=="ball" || _statusModel=="flyman"){
		_statusModel="man";
		changeToMan();
	}
	_die=true;
	velocity.y = -_jumpPower;
	JvG::stopMusic();
	JvG::play("dead.wav",1);
	
	setCollide(false);
}

void Hero::dieBomb()
{
	if(_die)
		return;
	_die=true;
	visible = false;
	
	JvG::stopMusic();
	JvG::play("dead.wav",1);
	
	JvG::camera->shake(0.05f,0.4f);
	
	_dieBombTime = 5;
	
	emitter->at(this);
	emitter->start();
}

void Hero::hasBall()
{
	_canBall = true;
}

void Hero::hasClib()
{
	_canClimb = true;
}

void Hero::changeToFlyMan()
{
	_statusModel="flyman";
	clearAnim();
	vector<int> moveframes;
	moveframes.push_back(0);
	moveframes.push_back(1);
	addAnimation("move_f",moveframes,20);
	
	vector<int> standframes;
	standframes.push_back(2);
	standframes.push_back(3);
	addAnimation("stand_f",standframes,10);
	loadGraphic("flyman2.png",true,true,24,20);
	
	velocity.x = velocity.y = 0;
	
	JvG::joystick->reSet();
	GameState::gamePad->flyMode();
	
	visible = false;
	_ywsp->x = x;
	_ywsp->y = y;
	_ywsp->visible = true;
	_ywsp->play("yw");
}

string Hero::getStatusModel()
{
	return _statusModel;
}

/*protected:*/
void Hero::changeToMan()
{
	acceleration.y =_gv;
	maxVelocity.x = _moveSpeed;
	maxVelocity.y = _jumpPower*1.2;
	drag.x=_moveSpeed*8;

	clearAnim();
	loadGraphic("hero.png",true,true,16,31);

	vector<int> walkframes;
	walkframes.push_back(2);
	walkframes.push_back(3);
	walkframes.push_back(4);
	walkframes.push_back(5);
	addAnimation("move",walkframes,5);

	vector<int> standframes;
	standframes.push_back(0);
	addAnimation("stand",standframes,0);

	vector<int> stand2frames;
	stand2frames.push_back(1);
	addAnimation("stand2",stand2frames,0);

	vector<int> jumpdownframes;
	jumpdownframes.push_back(7);
	addAnimation("jump_down",jumpdownframes,0);

	vector<int> jumpupframes;
	jumpupframes.push_back(6);
	addAnimation("jump_up",jumpupframes,0);

	vector<int> hitwallframes;
	hitwallframes.push_back(8);
	addAnimation("hitwall",hitwallframes,0);

	vector<int> dieframes;
	dieframes.push_back(9);
	dieframes.push_back(10);
	addAnimation("die",dieframes,8);

	y-=31-16;
	width=16;

	GameState::gamePad->walkMode();
}

void Hero::changeToBall()
{
	clearAnim();
	
	loadGraphic("heroball.png",true,true,16,16);

	vector<int> standframes;
	standframes.push_back(0);
	addAnimation("stand_b",standframes,0);

	vector<int> moveframes;
	moveframes.push_back(3);
	moveframes.push_back(2);
	moveframes.push_back(1);
	moveframes.push_back(0);
	addAnimation("move_b",moveframes,16);
	addAnimation("jump_up_b",moveframes,16);
	addAnimation("jump_down_b",moveframes,16);

	y+=31-16;
	width=15;
}

bool Hero::isCanBall()
{
	return _canBall;
}

void Hero::render()
{
	JvSprite::render();
}
