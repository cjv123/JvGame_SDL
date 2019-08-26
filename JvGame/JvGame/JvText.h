#ifndef _JVTEXT_H
#define _JVTEXT_H

#include <SDL.h>
#include "JvState.h"
#include <string>
#include "JvSprite.h"
using namespace std;

/**
*文本
*实现文本显示,支持\n换行
*/
class JvText : public JvSprite
{
public:
	JvText(double X, double Y, double Width,double Height,const char* fontname,
		const char* Text="",unsigned int size=8);
	virtual ~JvText();
	void setText(string& Text);
	string& getText();
	void setFont(const char* fontname);
	void setSize(int Size);
	int getSize();
	void setColor(int color);
	void setLineHeight(int Height);
	int getLineHeight();
	void make();

	virtual void render();

protected:

	string _text;
	int _size;
	int _color;
	int _lineHeight;
	string _fontname;
	string _aname;
	string _cname;
private:
};
#endif
