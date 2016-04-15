#ifndef __ALLOCMANGER_H__
#define __ALLOCMANGER_H__

#include "Common.h"

#include <iostream>
#include <map>
#include <vector>

//������ڴ����Ϣ
typedef struct MemeryBlock
{
	char * data;		// �ڴ���Ϣ
	uint size;			// �ڴ��С
	bool usedMalloc;	// true���ڴ�������룬false���ڴ��������
	bool isRelease;		// �Ƿ����ɾ��
}MemeryBlock;

/*
* ������
* ������һ���㹻����ڴ�飨�أ�����ÿ����Ҫ�����ڴ��ʱ�����С���ڴ�������ڴ�صģ������������롣
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
	* ���ܣ������ڴ�
	* ��������һ���СΪsize���ڴ�飬size���� >= 0
	* ʹ���ڴ����
	*/
	void * Alloc(uint size);

	/*
	* ���ܣ��ͷ��ڴ�
	* ����ָ��ָ���ָ�룬���ͷ�֮��ָ����ΪNULL����ֹ����Ұָ��
	*/
	bool Free(void ** pBuf);
	bool Free(char ** pBuf);
	bool Free(uchar ** pBuf);

	uint getMemoryCapity() const;
	uint getAllocation() const { return m_iAllocation; }
	uint getMemoryCount() const { return m_iBlockCount; }

protected:
	/*
	* �ṩһ�Է����������ڴ����������ͷ��ڴ�
	*/
	void * AllocBuff(uint size);
	bool FreeBuff(void ** pBuf);

private:
	char * m_pData;			// ������ڴ�
	uint m_iIndex;			// ����ƫ��ֵ
	int m_iBlockCount;		// ������ڴ������
	uint m_iAllocation;		// ��ǰ���е��ڴ��С

	/* 
	* ������¼������ڴ����Ϣ
	*/
	AllocMap m_memoryMap;	

	/*
	* ʹ��ƫ��ֵ��ά��һ���ڴ�أ������ϸ������Ƚ������ջʽ���������Ų���ʹƫ��ֵ����
	* ����ʹ��vector������ջ����ɾ����Ϊջ��Ԫ��ʱ����ɾ�������򽫸�Ԫ�ر��Ϊ��ɾ�����ض�ʱ��ɾ��
	*/
	std::vector<int> m_memoryList;

	static AllocManager * mInstance;

	void PrintMapAndList();
};

#endif // !__ALLOCMANGER_H__
