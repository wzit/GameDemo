#include <iostream>
#include "MainLoop.h"

int main()
{
	MainLoop loop;
	loop.setAnimationInterval(1);
	loop.run();

	system("pause");
	return 0;
}