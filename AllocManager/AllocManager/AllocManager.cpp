#include "AllocManager.h"

static uint G_SizeToK = 2 * 1024;
static uint G_SizeToB = 2 * 1024 * 1024;	// �̶��ڴ���С

static uint G_MallocCount = 0;
static uint G_FreeCount = 0;

AllocManager * AllocManager::mInstance = nullptr;

AllocManager * AllocManager::instance()
{
	if (nullptr == mInstance)
	{
		mInstance = new AllocManager();
	}
	return mInstance;
}

void AllocManager::desctory()
{
	delete mInstance;
	mInstance = nullptr;
}

AllocManager::AllocManager()
:m_pData(nullptr)
,m_iIndex(0)
,m_iBlockCount(0)
,m_iAllocation(0)
{
	m_pData = (char *)malloc(G_SizeToB);
	if (nullptr == m_pData)
	{
		printf("\n----- alloc memory failed!!! -----\n");
		exit(-1);
	}

	memset(m_pData, 0, G_SizeToB);
}

AllocManager::~AllocManager()
{
	delete m_pData;
	m_pData = nullptr;

	if (m_iBlockCount > 0)
	{
		printf("\n----- �ڴ�й¶ -----\n");
		printf("block count = %d\n",m_iBlockCount);
	}
}

uint AllocManager::getMemoryCapity() const 
{
	return G_SizeToB;
}

void * AllocManager::AllocBuff(uint size)
{
	size = (((size + 3) >> 2) << 2);
	void * pData = malloc(size);
	if (pData == nullptr)
	{
		printf("\n----- AllocBuff �����ڴ�ʧ�� -----\n");
		return nullptr;
	}
	memset(pData, 0, size);
	return pData;
}

bool AllocManager::FreeBuff(void ** pBuf)
{
	if (nullptr != (*pBuf))
	{
		return false;
	}

	delete (*pBuf);
	*pBuf = nullptr;
	return true;
}

// ����size��С���ڴ�
// �����жϵ�ǰ�ڴ���Ƿ�������󣬷��������ڴ������
// ������������һ��
void * AllocManager::Alloc(uint size)
{
	MemeryBlock block;
	memset(&block, 0, sizeof(block));
	do 
	{
		size = (((size + 3) >> 2) << 2);	//�ڴ����
		block.size = size;

		if (m_iIndex + size > getMemoryCapity())
		{
			block.data = static_cast<char*>(AllocBuff(size));
			if (nullptr == block.data)
			{
				printf("\n----- error to AllocManager:Alloc -----\n");
				break;
			}
			block.usedMalloc = true;
		}
		else
		{
			block.data = m_pData + m_iIndex;
			block.usedMalloc = false;
			m_iIndex += size;
		}

		block.isRelease = false;
		m_iAllocation += size;

		int address = (int)block.data;
		printf("address is %d\n", address);
		m_memoryMap.insert(std::pair<int, MemeryBlock>(address, block));
		m_memoryList.push_back(address);

		++m_iBlockCount;
		printf("after create, block count = %d\n",m_iBlockCount);
		++G_MallocCount;
	} while (0);

	return block.data;
}

// �ͷ��ڴ�
// ������ڴ�������� �� λ���ڴ����ջ��Ԫ�أ�����ɾ��
// ����ֻ���Ϊ��ɾ��
bool AllocManager::Free(void ** pBuf)
{
	bool rel = false;
	int posIndex = int(*pBuf);
	printf("free address = %d\n", posIndex);

	do 
	{
		IF_BREAK(m_iBlockCount <= 0);

		AllocMapIter iter = m_memoryMap.find(posIndex);
		IF_BREAK(iter == m_memoryMap.end());

		if (iter->second.usedMalloc || m_memoryList.back()==posIndex)
		{
			if (iter->second.usedMalloc)
			{
				FreeBuff(TO_VOID_PTR(&iter->second.data));
				iter->second.data = nullptr;
			}
			else
			{
				m_iIndex -= iter->second.size;
			}

			m_iAllocation -= iter->second.size;
			--m_iBlockCount;
			printf("after free, block count = %d\n",m_iBlockCount);
			*pBuf = nullptr;
			m_memoryMap.erase(iter);

			if (m_memoryList.size() > 0)
			{
				std::vector<int>::iterator sIter = m_memoryList.end() - 1;
				do 
				{
					if (*sIter == posIndex)
					{
						m_memoryList.erase(sIter);
						break;
					}
				} while ((sIter--) != m_memoryList.begin());
			}
			G_FreeCount++;
			rel = true;
			posIndex = 0;

			IF_BREAK(0 == m_memoryList.size());

			// �����Ѿ��ͷ�����һ����������һ��Ԫ���Ƿ���Ҫɾ��
			iter = m_memoryMap.find(m_memoryList.back());
			if (iter != m_memoryMap.end() && iter->second.isRelease)
			{
				rel = false;
				posIndex = m_memoryList.back();
			}
		}
		else
		{
			iter->second.isRelease = true;
			rel = true;
			break;
		}

	} while (posIndex != 0);
	
	return rel;
}

bool AllocManager::Free(char ** pBuf)
{
	return Free(TO_VOID_PTR(pBuf));
}

bool AllocManager::Free(uchar ** pBuf)
{
	return Free(TO_VOID_PTR(pBuf));
}

void AllocManager::PrintMapAndList()
{
	printf("Map is :\n");
	for (AllocMapIter iter = m_memoryMap.begin(); iter != m_memoryMap.end(); iter++)
	{
		printf("%d\n",iter->first);
	}
	printf("List is :\n");
	for (std::vector<int>::iterator iter = m_memoryList.begin(); iter != m_memoryList.end(); iter++)
	{
		printf("%d\n",*iter);
	}
}