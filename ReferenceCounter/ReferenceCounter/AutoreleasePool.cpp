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

void AutoreleasePool::clear()	// 两帧之间调用，用于清除引用计数为1的对象
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
		new AutoreleasePool();		// 生成实例时，创建第一个自动释放池
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
		delete pool;	// AutoreleasePool析构函数会pop栈顶释放池
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