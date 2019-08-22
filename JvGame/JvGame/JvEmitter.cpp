#include "JvEmitter.h"
#include "JvSprite.h"

JvEmitter::JvEmitter(double X/* =0 */,double Y/* =0 */)
{
	x = X;
	y = Y;
	width = 0;
	height = 0;
	
	minParticleSpeed.x = minParticleSpeed.y = -100;
	maxParticleSpeed.x = maxParticleSpeed.y = 100;
	minRotation = -360;
	maxRotation = 360;
	gravity = 400;
	delay = 0;
	quantity = 0;
	_counter = 0;
	_explode = true;
	exists = false;
	on = false;
	scale = 1;
}

JvEmitter* JvEmitter::createSprites(const char* Filename,unsigned int Quantity/* =50 */, 
									int BakedRotations/* =16 */,bool Multiple/* =true */, double Collide/* =0 */)
{
	SDL_Texture* Graphics = JvU::loadTexture(Filename);
	
	createSprites(Graphics,Quantity,BakedRotations,Multiple,Collide);

	return this;
}

JvEmitter* JvEmitter::createSprites(SDL_Texture* Graphics,unsigned int Quantity/* =50 */, int BakedRotations/* =16 */,bool Multiple/* =true */, double Collide/* =0 */)
{
	unsigned int r;
	JvSprite* sP = NULL;
	unsigned int tf = 1;
	double sw;
	double sh;

	int textureW = 0, textureH = 0;
	SDL_QueryTexture(Graphics, NULL, NULL, &textureW, &textureH);
	
	if(Multiple)
	{

		tf = textureW/textureH;
	}
	
	for(int i = 0; i < Quantity; i++)
	{
		sP = new JvSprite();
		sP->angle = BakedRotations;
		sP->loadGraphic(Graphics,true,false, textureW,textureH);

		if(Multiple)
		{
			r = JvU::random()*tf;
		}
		else
		{
			r=0;
		}
		
		vector<int> frames;
		frames.push_back(r);
		sP->addAnimation("emitter",frames);
		sP->play("emitter");
		sP->setScale(scale);
		
		if(Collide > 0)
		{
			sw = sP->width;
			sh = sP->height;
			sP->width *= Collide;
			sP->height *= Collide;
			sP->offset.x = (sw-sP->width)/2;
			sP->offset.y = (sh-sP->height)/2;
			sP->SetSolid(true);
		}
		else
		{
			sP->SetSolid(false);
		}
		sP->exists = false;
		//sP->scrollFactor = scrollFactor;
		add(sP);
	}
	
	return this;
}

void JvEmitter::setSize(unsigned int Width,unsigned int Height)
{
	width = Width;
	height = Height;
}

void JvEmitter::setXSpeed(double Min/*=0*/,double Max/*=0*/)
{
	minParticleSpeed.x = Min;
	maxParticleSpeed.x = Max;
}

void JvEmitter::setYSpeed(double Min/*=0*/,double Max/*=0*/)
{
	minParticleSpeed.y = Min;
	maxParticleSpeed.y = Max;
}

void JvEmitter::setRotation(double Min/*=0*/,double Max/*=0*/)
{
	minRotation = Min;
	maxRotation = Max;
}

/*virtual */void JvEmitter::update()
{
	JvGroup::update();
	updateEmitter();
}

void JvEmitter::start(bool Explode/* =true */,double Delay/* =0 */,unsigned int Quantity/* =0 */)
{
	if(members.size() <= 0)
	{
		printf("WARNING: there are no sprites loaded in your emitter.\n");
		return;
	}
	_explode = Explode;
	if(!_explode)
		_counter = 0;
	if(!exists)
		_particle = 0;
	exists = true;
	visible = true;
	active = true;
	dead = false;
	on = true;
	_timer = 0;
	if(quantity == 0)
	{
		quantity = Quantity;
	}
	if(Delay != 0)
	{
		delay = Delay;
	}
	if(delay < 0)
	{
		delay = -delay;
	}
	if(delay == 0)
	{
		if(Explode)
		{
			delay = 3.0f;	
		}
		else
		{
			delay = 0.1f;
		}
	}
}

void JvEmitter::emitParticle()
{
	_counter++;
	JvSprite* sP = (JvSprite*)members[_particle];
	sP->visible = true;
	sP->exists = true;
	sP->active = true;
	sP->x = x - ((int)sP->width>>1) + JvU::random()*width;
	sP->y = y - ((int)sP->height>>1) + JvU::random()*height;
	sP->velocity.x = minParticleSpeed.x;

	if(minParticleSpeed.x != maxParticleSpeed.x) 
	{
		sP->velocity.x +=JvU::random()*(maxParticleSpeed.x-minParticleSpeed.x);
	}

	sP->velocity.y = minParticleSpeed.y;
	if(minParticleSpeed.y != maxParticleSpeed.y) 
	{
		sP->velocity.y +=JvU::random()*(maxParticleSpeed.y-minParticleSpeed.y);
	}

	sP->acceleration.y = gravity;
	sP->angularVelocity = minRotation;
	if(minRotation != maxRotation)
	{
		sP->angularVelocity += JvU::random()*(maxRotation-minRotation);
	}
	
	if(sP->angularVelocity != 0)
	{
		sP->angle = JvU::random()*360-180;
	}

	sP->drag.x = particleDrag.x;
	sP->drag.y = particleDrag.y;
	sP->visible = true;
	_particle++;

	if(_particle >= members.size())
	{
		_particle = 0;
	}

	sP->onEmit();
}

void JvEmitter::stop(double Delay/*=3*/)
{
	_explode = true;
	delay = Delay;
	if(delay < 0)
	{
		delay = -Delay;
	}
	on = false;
}

void JvEmitter::at(JvObject* ObjectP)
{
	x = ObjectP->x + ObjectP->origin.x;
	y = ObjectP->y + ObjectP->origin.y;
}

/*virtual */void JvEmitter::kill()
{
	JvGroup::kill();
	on = false;
}

/*protected:*/
void JvEmitter::updateEmitter()
{
	if(_explode)
	{
		unsigned int i;
		unsigned int l;
		_timer += JvG::elapsed;
		if((delay > 0) && (_timer > delay))
		{
			kill();
			return;
		}

		if(on)
		{
			on = false;
			l = members.size();
			if(quantity > 0)
			{
				l = quantity;
			}
			l += _particle;
			for(i = _particle; i < l; i++)
			{
				emitParticle();
			}
		}
		return;
	}

	if(!on)
	{
		return;
	}

	_timer += JvG::elapsed;
	while((_timer > delay) && ((quantity <= 0) || (_counter < quantity)))
	{
		_timer -= delay;
		emitParticle();
	}
}
