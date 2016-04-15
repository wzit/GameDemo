#include <iostream>
#include "AllocManager.h"

int main(void)
{

	char* data1 = (char*)AllocManager::instance()->Alloc(10);
	char* data2 = (char*)AllocManager::instance()->Alloc(15);
	char* data3 = (char*)AllocManager::instance()->Alloc(21);

	AllocManager::instance()->Free(&data3);
	AllocManager::instance()->Free(&data1);
	AllocManager::instance()->Free(&data2);

	system("pause");
	return 0;
}