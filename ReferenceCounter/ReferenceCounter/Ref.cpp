#include "Ref.h"
#include <iostream>
using std::cout;
using std::endl;
#include "AutoreleasePool.h"

Ref::Ref():_referenceCount(1)
{
	cout << "new a ref object, the counter is " << _referenceCount << endl;
}

void Ref::retain()
{
	_referenceCount++;
	cout << "retain a ref object, the counter is " << _referenceCount << endl;
}

void Ref::release()
{
	_referenceCount--;
	cout << "release a ref object, the counter is " << _referenceCount << endl;

	if (_referenceCount<=0)
	{
		delete this;
	}
}

Ref *Ref::autorelease()
{
	PoolManager::getInstance()->getCurPool()->addObject(this);
	cout << "add a ref object to autoreleasepool" << endl;
	return this;
}