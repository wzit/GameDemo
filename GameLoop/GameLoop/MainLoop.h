#ifndef _MAINLOOP_H_
#define _MAINLOOP_H_

#include <windows.h>
#include <stdio.h>

class MainLoop
{
public:
	MainLoop():timeCount(0){}
	void setAnimationInterval(double interval);		// 设置时间间隔
	void run();

private:
	LARGE_INTEGER _animationInterval;
	unsigned timeCount;
};

#endif // !_MAINLOOP_H_
