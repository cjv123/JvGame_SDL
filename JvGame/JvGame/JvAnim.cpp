#include "JvAnim.h"
#include "JvG.h"

JvAnim::JvAnim(string& Name, vector<int>& Frames, double FrameRate/* =0 */, 
			   bool Looped/* =true */)
{
	name = Name;
	delay = 0;
	if(FrameRate > 0)
		delay = 1.0f/FrameRate;
	frames = Frames;
	looped = Looped;
}
