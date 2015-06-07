#include "MainLoop.h"

void MainLoop::setAnimationInterval(double interval)
{
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	_animationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

void MainLoop::run()
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;

	QueryPerformanceFrequency(&nFreq);		// 获得机器内部计时器的频率
	QueryPerformanceCounter(&nBeginTime);	// 获得第一次计数

	while (1)	// 游戏死循环
	{
		QueryPerformanceCounter(&nEndTime);	// 获得第二次计数
		if (nEndTime.QuadPart - nBeginTime.QuadPart > _animationInterval.QuadPart)	// 两次计数差大于指定时间间隔则执行
		{
			timeCount++;
			printf("%d\n", timeCount);
			nBeginTime = nEndTime;
		}
	}
}