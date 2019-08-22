#ifndef _JVTEXTPAD_H
#define _JVTEXTPAD_H

#include "JvGroup.h"

class JvText;

class JvTextPad : public JvGroup
{
public:
	JvTextPad(double X, double Y,double Width,double Height,
		const char* FontFilename ,const char* Text);
	~JvTextPad();
	void setText(const char* Text);
	void setTextColor(int Color);
	void setBgColor(int Color);
	void setTextSize(int Size);
	void setLineHight(int LineHight);
	void setFont(const char* FontFilename);
	void setTextPostion(int TargetX,int TargetY);
	void show();
	void close();
	virtual void update();
	virtual void render();
protected:
	JvText* _text;
	int _bgColor;
	bool _isShow;

	
	double _w;
	double _h;
	double _x;
	double _y;
private:
};

#endif