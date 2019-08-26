#include <SDL_image.h>
#include "JvSprite.h"
#include "JvState.h"
#include "JvGame.h"

JvSprite::JvSprite(double X /* =0 */,double Y/* =0 */,
	SDL_Texture* SimpleGraphic /* = NULL */) : JvObject(X,Y)
{
	_texure = NULL;
	_scale = 1;
	if (SimpleGraphic != NULL)
	{
		loadGraphic(SimpleGraphic);
	}

	_frameTimer =0;
	_curAnim = NULL;
	_curFrame = 0;
	facing = FACERIGHT;
	_isFillRect = false;
	_mask = 0;

}

JvSprite::~JvSprite()
{
	if (_texure != NULL)
	{
		SDL_DestroyTexture(_texure);
		_texure = NULL;
	}

	//Çå³ý¶¯»­
	clearAnim();
}


JvSprite* JvSprite::loadGraphic(const string& FileName,bool Animated /* = false */,bool Reverse /* =false */,
								unsigned int Width /* = 0 */,unsigned int Height /* =0 */)
{
	if (_texure != NULL)
	{
		SDL_DestroyTexture(_texure);
		_texure = NULL;
	}
	
	_texure = JvU::loadTexture(FileName);

	if (_texure ==NULL)
	{
		printf("no this file: %s\n",FileName.c_str());
		return this;
	}


	if (!Animated)
	{
		int textureW = 0, textureH = 0;
		SDL_QueryTexture(_texure, NULL, NULL, &textureW, &textureH);

		frameWidth = textureW;
		frameHeight = textureH;
		width =textureW*_scale;
		height = textureH*_scale;
	}
	else
	{
		frameWidth = Width;
		frameHeight = Height;
		width = Width*_scale;
		height = Height*_scale;
	}
	origin.x = frameWidth/2;
	origin.y = frameHeight/2;
	return this;
}

JvSprite* JvSprite::loadGraphic(SDL_Texture* Graphic,bool Animated /* = false */,bool Reverse /* =false */,
								unsigned int Width /* = 0 */,unsigned int Height /* =0 */)
{
	if (_texure != NULL)
	{
		SDL_DestroyTexture(_texure);
		_texure = NULL;
	}

	_texure = Graphic;

	if (!Animated)
	{
		int textureW = 0, textureH = 0;
		SDL_QueryTexture(_texure, NULL, NULL, &textureW, &textureH);

		frameWidth = textureW;
		frameHeight = textureH;
		width = textureW * _scale;
		height = textureH * _scale;

	}
	else
	{
		frameWidth = Width;
		frameHeight = Height;
		width = Width*_scale;
		height = Height*_scale;
	}
	origin.x = frameWidth/2;
	origin.y = frameHeight/2;
	return this;
}

void JvSprite::create()
{

}

void JvSprite::update()
{
	JvObject::update();
	updateAnimation();
}

void JvSprite::render()
{
	renderSprite();

	if (_isFillRect)
	{
		int r, g, b, a;
		GET_RGBA_8888(_rectColor, r, g, b, a);
		SDL_SetRenderDrawBlendMode(JvG::jvGameP->getSDLRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(JvG::jvGameP->getSDLRenderer(), r, g, b, a);
		SDL_Rect rect{ x,y,width,height };
		SDL_RenderFillRect(JvG::jvGameP->getSDLRenderer(), &rect);
	}
}

SDL_Texture* JvSprite::getPixels()
{
	return _texure;
}

SDL_Texture* JvSprite::getSDLTexture()
{
	return _texure;
}



void JvSprite::renderSprite()
{
	JvG::stateP->camera->render(this);
	//printf("rendersprite");
}

void JvSprite::addAnimation(string Name, vector<int>& Frames,
							double FrameRate/* =0 */, bool Looped/* =true */)
{
	_animations.push_back(new JvAnim(Name,Frames,FrameRate,Looped));
}

void JvSprite::play(string Name ,bool Force /* = false */)
{
	if (!Force && (_curAnim != NULL))
	{
		if (Name == _curAnim->name)
		{
			return;
		}
	}

	_curFrame = 0;
	
	vector<JvAnim*>::iterator it = _animations.begin();
	for (;it!=_animations.end();it++)
	{
		if ((*it)->name == Name)
		{
			_curAnim = (*it);
		}
	}
}

void JvSprite::updateAnimation()
{
	if (_curAnim != NULL && (_curAnim->delay > 0) && (_curAnim->looped || !finished))
	{
		_frameTimer+=JvG::elapsed;
		if (_frameTimer > _curAnim->delay)
		{
			_frameTimer -= _curAnim->delay;
			if (_curFrame>=_curAnim->frames.size() - 1)
			{
				if(_curAnim->looped) _curFrame = 0;
				finished = true;
			}
			else
			{
				_curFrame++;
			}
		}
	}
}

unsigned int JvSprite::getCaf()
{
	if (_curAnim != NULL)
	{
		return _curAnim->frames[_curFrame];
	}
	else
	{
		return 0;
	}
}

void JvSprite::preCollide(JvObject* ObjectP)
{
	
}

void JvSprite::setScale(double Scale)
{
	_scale = Scale;
	width =_scale*frameWidth;
	height=_scale*frameHeight;

//	printf("scale:%lf,width:%lf,height:%lf\n",_scale,width,height);
	origin.x = x + width/2;
	origin.y = y + height/2;
}

double JvSprite::getScale()
{
	return _scale;
}

void JvSprite::clearAnim()
{
	vector<JvAnim*>::iterator it = _animations.begin();
	for (;it!=_animations.end();it++)
	{
		delete (*it);
	}
	_animations.clear();
	_curAnim = NULL;
}

void JvSprite::createRect(int X,int Y,int Width,int Height,int Color)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	_rectColor = Color;
	_isFillRect = true;
}

bool JvSprite::isPlayEnd()
{
	if (_curAnim != NULL)
	{
		if(_curFrame>=_curAnim->frames.size()-1)
			return true;
	}
	return false;
}

void JvSprite::setMask(int MaskColor)
{
	_mask = MaskColor;
}

int JvSprite::getMask()
{
	return _mask;
}

/*virtual*/
void JvSprite::onEmit()
{

}