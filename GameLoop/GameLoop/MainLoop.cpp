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

	QueryPerformanceFrequency(&nFreq);		// ��û����ڲ���ʱ����Ƶ��
	QueryPerformanceCounter(&nBeginTime);	// ��õ�һ�μ���

	while (1)	// ��Ϸ��ѭ��
	{
		QueryPerformanceCounter(&nEndTime);	// ��õڶ��μ���
		if (nEndTime.QuadPart - nBeginTime.QuadPart > _animationInterval.QuadPart)	// ���μ��������ָ��ʱ������ִ��
		{
			timeCount++;
			printf("%d\n", timeCount);
			nBeginTime = nEndTime;
		}
	}
}