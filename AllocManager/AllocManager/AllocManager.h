#ifndef __ALLOCMANGER_H__
#define __ALLOCMANGER_H__

#include "Common.h"

#include <iostream>
#include <map>
#include <vector>

//申请的内存块信息
typedef struct MemeryBlock
{
	char * data;		// 内存信息
	uint size;			// 内存大小
	bool usedMalloc;	// true：内存池外申请，false：内存池内申请
	bool isRelease;		// 是否可以删除
}MemeryBlock;

/*
* 单例类
* 先申请一块足够大的内存块（池），当每次需要申请内存的时候，如果小于内存池则拿内存池的，否则重新申请。
*/
class AllocManager
{
private:
	AllocManager();

public:
	~AllocManager();

	static AllocManager * instance();
	static void desctory();

	typedef std::map<int, MemeryBlock>				AllocMap;
	typedef std::map<int, MemeryBlock>::iterator	AllocMapIter;
	typedef std::map<int, MemeryBlock>::reverse_iterator	AllocMapRIter;

public:
	/*
	* 功能：申请内存
	* 用于申请一块大小为size的内存块，size必须 >= 0
	* 使用内存对齐
	*/
	void * Alloc(uint size);

	/*
	* 功能：释放内存
	* 传入指向指针的指针，在释放之后将指针置为NULL，防止出现野指针
	*/
	bool Free(void ** pBuf);
	bool Free(char ** pBuf);
	bool Free(uchar ** pBuf);

	uint getMemoryCapity() const;
	uint getAllocation() const { return m_iAllocation; }
	uint getMemoryCount() const { return m_iBlockCount; }

protected:
	/*
	* 提供一对方法用于在内存池外申请和释放内存
	*/
	void * AllocBuff(uint size);
	bool FreeBuff(void ** pBuf);

private:
	char * m_pData;			// 申请的内存
	uint m_iIndex;			// 索引偏移值
	int m_iBlockCount;		// 申请的内存块数量
	uint m_iAllocation;		// 当前所有的内存大小

	/* 
	* 用来记录申请的内存块信息
	*/
	AllocMap m_memoryMap;	

	/*
	* 使用偏移值来维护一个内存池，必须严格遵守先进后出的栈式规则，这样才不会使偏移值错乱
	* 这里使用vector来代替栈，当删除的为栈顶元素时立即删除，否则将该元素标记为可删除，特定时候删除
	*/
	std::vector<int> m_memoryList;

	static AllocManager * mInstance;

	void PrintMapAndList();
};

#endif // !__ALLOCMANGER_H__
