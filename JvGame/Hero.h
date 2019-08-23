#ifndef _HERO_H
#define _HERO_H
#include "JvGame/JvSprite.h"

class JvEmitter;

class Hero : public JvSprite
{
public:
	Hero(double X,double Y);
	virtual ~Hero();
	virtual void update();
	virtual void kill();
	virtual void hitLeft(JvObject* Contact,double Velocity);
	virtual void hitRight(JvObject* Contact,double Velocity);
	virtual void hitTop(JvObject* Contact,double Velocity);
	virtual void hitBottom(JvObject* Contact,double Velocity);
	void die();
	void dieBomb();
	void hasBall();
	void hasClib();
	void changeToFlyMan();
	string getStatusModel();
	bool isCanBall();
protected:
	void changeToMan();
	void changeToBall();

	virtual void render();


	JvEmitter* emitter;

	double  _jumpPower;
	double _gv;
	double _moveSpeed;

	string _statusModel;
	bool _hitWall;

	int _changeTimer;
	bool _die;

	int _stands2Timer;

	int dietimer;

	bool _canClimb;

	bool _canBall;

	int _dieBombTime;


	JvSprite* _ywsp;
private:
};

#endif