#ifndef _JVANIM_H
#define _JVANIM_H

#include <string>
#include <vector>
using namespace std;

/**
*动画
*用于JvSprite里动画的实现,一般外部不需要直接使用
*/
class JvAnim
{
public:
	string name;
	double delay;
	vector<int> frames;
	bool looped;
	
	/**
	 *构造函数
	 *@param string& Name,动画名
	 *@param vector<int>& Frames,设置动画每一帧图片的index(子图序列)
	 *@param double FrameRate=0,播放速率(帧/秒)
	 *@param bool Looped=true,是否循环播放
	 *@return 无
	 */
	JvAnim(string& Name, vector<int>& Frames, double FrameRate=0, bool Looped=true);
protected:
private:
};

#endif