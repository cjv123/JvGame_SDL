#ifndef _JVSPRITE_H
#define _JVSPRITE_H

#include "JvObject.h"
#include "JvAnim.h"

#include <SDL.h>
using namespace std;


enum FACEDIRECT{FACELEFT=0,FACERIGHT=1,FACEUP=2,FACEDOWN=3};

/**
*精灵
*实现动画对象
*/
class JvSprite : public JvObject
{
public:
	JvSprite(double X =0,double Y=0,SDL_Texture* Graphic=NULL);
	virtual ~JvSprite();

	/**
	 *载入图像
	 *@param string FileName,图片文件名
	 *@param bool Animated,是否实现动画
	 *@param bool Reverse,是否实现翻转
	 *@param unsigned int Width,精灵宽度
	 *@param unsigned int Height,精灵高度
	 *@param int DisplayMode,参见NGE2的image_load
	 *@return JvSprite*,用于实现链式调用
	 */
	JvSprite* loadGraphic(const string& FileName,bool Animated = false,bool Reverse =false,
			unsigned int Width = 0,unsigned int Height =0);

	/**
	 *载入图像
	 *@param image_p Graphic,图片数据(用image_clone()复制一份数据进入)
	 *@param bool Animated,是否实现动画
	 *@param bool Reverse,是否实现翻转
	 *@param unsigned int Width,精灵宽度
	 *@param unsigned int Height,精灵高度
	 *@param int DisplayMode,参见NGE2的image_load
	 *@return JvSprite*,用于实现链式调用
	 */
	JvSprite* loadGraphic(SDL_Texture* Graphic,bool Animated = false,bool Reverse =false,
		unsigned int Width = 0,unsigned int Height =0);
	

	virtual void create();
	virtual void update();
	virtual void render();
	SDL_Texture* getPixels();
	SDL_Texture* getSDLTexture();

	/**
	 *添加一个动画
	 *@param string Name,动画名
	 *@param vector<int>& Frames,动画帧
	 *@param double FrameRate,帧率
	 *@param bool Looped,是否循环播放
	 *@return void
	 */
	void addAnimation(string Name, vector<int>& Frames, double FrameRate=0, bool Looped=true);
	
	/**
	 *播放一个动画
	 *@param string Name,动画名
	 *@param bool Force,每次调用是否重新开始播放
	 *@return void
	 */
	void play(string Name ,bool Force = false);

	unsigned int getCaf();

	virtual void preCollide(JvObject* ObjectP);
	//缩放
	double getScale();
	void setScale(double Scale);

	virtual void onEmit();

	void clearAnim();

	void createRect(int X,int Y,int Width,int Height,int Color);

	bool isPlayEnd();

	void setMask(int MaskColor);
	int getMask();
	
	JvPoint offset;
	unsigned int frameWidth;
	unsigned int frameHeight;
	FACEDIRECT facing;

	bool finished;
protected:
	void renderSprite();
	void updateAnimation();
	

	//存放原始图
	SDL_Texture* _texure;

	vector<JvAnim*> _animations;
	JvAnim* _curAnim;
	unsigned int _curFrame;
	double _frameTimer;
	
	double _scale;

	int _mask;

	bool _isFillRect;
	int _rectColor;

private:
};

#endif 