#include "AutoreleasePool.h"

AutoreleasePool::AutoreleasePool()
{
	_releasePool.reserve(100);
	PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool()
{
	clear();
	PoolManager::getInstance()->pop();
}

void AutoreleasePool::addObject(Ref *obj)
{
	_releasePool.push_back(obj);
}

void AutoreleasePool::clear()	// ��֮֡����ã�����������ü���Ϊ1�Ķ���
{
	for (const auto &obj : _releasePool)
	{
		obj->release();
	}
	_releasePool.clear();
}

// PoolManager
PoolManager *PoolManager::_instance = nullptr;

PoolManager *PoolManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new PoolManager();
		new AutoreleasePool();		// ����ʵ��ʱ��������һ���Զ��ͷų�
	}
	return _instance;
}

void PoolManager::destroyInstance()
{
	delete _instance;
	_instance = nullptr;
}

PoolManager::PoolManager()
{
	_poolManager.reserve(10);
}

PoolManager::~PoolManager()
{
	while (!_poolManager.empty())
	{
		AutoreleasePool *pool = _poolManager.back();
		delete pool;	// AutoreleasePool����������popջ���ͷų�
	}
}

void PoolManager::push(AutoreleasePool *pool)
{
	_poolManager.push_back(pool);
}

void PoolManager::pop()
{
	_poolManager.pop_back();
}

AutoreleasePool *PoolManager::getCurPool() const
{
	return _poolManager.back();
}