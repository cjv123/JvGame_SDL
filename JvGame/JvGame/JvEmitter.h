#ifndef _JVEMITTER_H
#define _JVEMITTER_H

#include "JvGroup.h"
#include <SDL.h>

/**
*粒子发射器
*使用图片所谓粒子单位，用于实现粒子特效
*/
class JvEmitter : public JvGroup
{
public:
	JvPoint minParticleSpeed;
	JvPoint maxParticleSpeed;
	JvPoint particleDrag;
	double minRotation;
	double maxRotation;
	double gravity;
	bool on;
	double delay;
	unsigned int quantity;
	int scale;

	JvEmitter(double X=0,double Y=0);
	
	/**
	 *创建粒子单位的sprite
	 *@param const char* Filename, 图片文件名
	 *@param unsigned int Quantity=50,sprite个数
	 *@param int BakeRotations=16,sprite初始角度 
	 *@param bool Multiple=true,如果为true,将根据图片高度随机截取子图
	 *@param double Collide=0,0表示粒子不碰撞(效率高),Collide取值在0-1范围控制碰撞概率
	 *@return JvEmitter* 返回this实现链式调用
	 */
	JvEmitter* createSprites(const char* Filename,unsigned int Quantity=50,
				int BakedRotations=16,bool Multiple=true, double Collide=0);

	/**
	 *创建粒子单位的sprite
	 *@param image_p Graphics, 图片数据
	 *@param unsigned int Quantity=50,sprite个数
	 *@param int BakeRotations=16,sprite初始角度 
	 *@param bool Multiple=true,如果为true,将根据图片高度随机截取子图
	 *@param double Collide=0,0表示粒子不碰撞(效率高),Collide取值在0-1范围控制碰撞概率
	 *@return JvEmitter* 返回this实现链式调用
	 */
	JvEmitter* createSprites(SDL_Texture* Graphics,unsigned int Quantity=50,
				int BakedRotations=16,bool Multiple=true, double Collide=0);
	
	/**
	 *设置粒子初始出现范围
	 *@param unsigned int Width, 范围宽
	 *@param unsigned int Height,范围高
	 *@return void
	 */
	void setSize(unsigned int Width,unsigned int Height);
	
	/**
	 *设置x方向粒子速度
	 *@param double Min=0,粒子x方向最小速度
	 *@param double Max=0,粒子x方向最大速度
	 *@return void
	 */
	void setXSpeed(double Min=0,double Max=0);
	
	/**
	 *设置y方向粒子速度
	 *@param double Min=0,粒子y方向最小速度
	 *@param double Max=0,粒子y方向最大速度
	 *@return void
	 */
	void setYSpeed(double Min=0,double Max=0);

	/**
	 *设置粒子角速度
	 *@param double Min=0,粒子最小角速度
	 *@param double Max=0,粒子最大角速度
	 *@return void
	 */
	void setRotation(double Min=0,double Max=0);

	virtual void update();

	/**
	 *设置粒子角速度
	 *@param bool Explode=true,是否一次性爆发
	 *@param double Delay=0,设置延迟爆发(秒)
	 *@param unsigned int Quantity=0,初始爆发数
	 *@return void
	 */
	void start(bool Explode=true,double Delay=0,unsigned int Quantity=0);

	/*updateEmitter()调用,外部不使用*/
	void emitParticle();
	
	/**
	 *停止发射
	 *@param double Delay=3,几秒后kill粒子
	 *@return void
	 */
	void stop(double Delay=3);

	/**
	 *根据某个object设置发射器的位置
	 *@param JvObject* ObjectP,要发射位置的object
	 *@return void
	 */
	void at(JvObject* ObjectP);
	
	/**
	 *kill发射器
	 *@return void
	 */
	virtual void kill();
protected:
	void updateEmitter();

	bool _explode;
	double _timer;
	unsigned int _particle;
	unsigned int _counter;
	
};

#endif