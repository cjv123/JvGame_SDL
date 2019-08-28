#include "JvText.h"
#include "JvU.h"
#include "JvGame.h"
#include <SDL_ttf.h>

JvText::JvText(double X,double Y, double Width,double Height,const char* fontname,
			   const char* Text,unsigned int size)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	frameWidth = width;
	frameHeight = height;
	scrollFactor.x = scrollFactor.y = 0;
	_text = Text;
	_size = size;
	_lineHeight = 1;
	setCollide(false);
	_fontname = fontname; 
	_texure = NULL;
	_color = MAKE_RGBA_8888(255,255,255,255);

	make();
}

JvText::~JvText()
{
	if (_texure)
	{
		SDL_DestroyTexture(_texure);
		_texure = NULL;
	}
}

void JvText::setText(string& Text)
{
	_text = Text;
}

string& JvText::getText()
{
	return _text;
}

void JvText::setFont(const char* fontname)
{
	_fontname = fontname;
}

void JvText::setSize(int Size)
{
	_size = Size;
}

int JvText::getSize()
{
	return _size;
}

void JvText::setColor(int color)
{
	_color = color;
	int r,g,b,a;
	GET_RGBA_8888(_color,r,g,b,a);
}

void JvText::setLineHeight(int Height)
{
	_lineHeight = Height;

}

int JvText::getLineHeight()
{
	return _lineHeight;
}

void JvText::make()
{
	TTF_Font* Sans = TTF_OpenFont(_fontname.c_str(), _size); 
	if (Sans == NULL) {
		printf("load fontfile:%s fail:%s\n",_fontname.c_str(), TTF_GetError());
		return;
	}

	int r, g, b,a;
	GET_RGBA_8888(_color,r,g,b,a);
	SDL_Color White = { r, g, b }; 
	SDL_Surface* surfaceMessage = NULL;
	if (width == 0)
	{
		surfaceMessage = TTF_RenderText_Solid(Sans,_text.c_str(), White);
	}
	else
	{
		surfaceMessage = TTF_RenderText_Blended_Wrapped(Sans,_text.c_str(), White,width);
	}

	if (_texure)
	{
		SDL_DestroyTexture(_texure);
		_texure = NULL;
	}
	_texure = SDL_CreateTextureFromSurface(JvG::jvGameP->getSDLRenderer(), surfaceMessage); 
	SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(Sans);

	int textureW = 0, textureH = 0;
	SDL_QueryTexture(_texure, NULL, NULL, &textureW, &textureH);
	width = textureW;
	height = textureH;
	frameWidth = width;
	frameHeight = height;
}

void JvText::render()
{
	if (_texure) 
	{
		//JvG::camera->draw(_texure,0,0,width,height,x,y,1,1,0,NGE_FLIP_NONE);
		JvG::camera->render(this);
	}
}
