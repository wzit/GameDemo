#ifndef _AUTORELEASEPOOL_H_
#define _AUTORELEASEPOOL_H_

#include <iostream>
#include <vector>
using std::vector;

#include "Ref.h"

// �Զ��ͷų�
class AutoreleasePool
{
public:
	AutoreleasePool();
	~AutoreleasePool();

	void addObject(Ref *obj);
	void clear();

private:
	vector<Ref *> _releasePool;
};

// �ͷųع�����
class PoolManager
{
public:
	static PoolManager *getInstance();
	static void destroyInstance(); 
	
	AutoreleasePool *getCurPool() const;

	friend class AutoreleasePool;
private:
	PoolManager();
	~PoolManager();

	void push(AutoreleasePool *pool);
	void pop();

	static PoolManager* _instance;

	vector<AutoreleasePool *> _poolManager;
};

#endif // !_AUTORELEASEPOOL_H_
