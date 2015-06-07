#include <iostream>
#include "Node.h"
#include "AutoreleasePool.h"

int main()
{
	Ref *node = new Node;
	node->autorelease();
	PoolManager::getInstance()->getCurPool()->clear();

	system("pause");
	return 0;
}