#include "CByteInputStream.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

CByteInputStream::CByteInputStream()
{

}

CByteInputStream::~CByteInputStream()
{
	DeleteAll();
}

CByteInputStream* CByteInputStream::newL(const unsigned char* pData, int iSize)
{
	CByteInputStream* self = new CByteInputStream();
	self->constructL(pData, iSize);
	return self;
}

CByteInputStream* CByteInputStream::newL(const unsigned char* pData, int iSize, int iOffset, int iLen)
{
	CByteInputStream* self = new CByteInputStream();
	self->constructL(pData, iSize, iOffset, iLen);
	return self;
}

void CByteInputStream::constructL(const unsigned char* pData, int iSize)
{
	if (!pData)
		return;
	m_pBuf = (unsigned char*)pData;
	m_iSize = iSize;
	m_iPos = 0;
}

void CByteInputStream::constructL(const unsigned char* pData, int iSize, int iOffset, int iLen)
{
	if (!pData)
		return;
	m_pBuf = (unsigned char*)pData;
	m_iSize = iSize;
	m_iPos = iOffset;
}

//这里的m_pBuf只是指向一块内存，所以清除的时候不用是否，只需置空
void CByteInputStream::DeleteAll()
{
	m_pBuf = nullptr;
}

int CByteInputStream::Read()
{
	if (m_iPos>m_iSize)
		return 0;

	int aByte = m_pBuf[m_iPos++];
	return aByte;
}

char* CByteInputStream::Read(const char* pData, int iSize)
{
	if (m_iPos+iSize > m_iSize)
	{
		return nullptr;
	}
	memcpy((void*)pData, m_pBuf+m_iPos, iSize);
	m_iPos += iSize;
	return (char*)pData;
}

char CByteInputStream::ReadByte()
{
	return (char)Read();
}

short CByteInputStream::ReadShort()
{
	int c1 = Read();
	int c2 = Read();
	return ((c1<<8) + c2);
}

short CByteInputStream::ReadShortTGA()
{
	int c2 = Read();
	int c1 = Read();
	return ((c1<<8) + c2);
}

int CByteInputStream::ReadInt()
{
	int c1 = Read();
	int c2 = Read();
	int c3 = Read();
	int c4 = Read();
	return ((c1<<24) + (c2<<16) + (c3<<8) + c4);
}

long long CByteInputStream::ReadLong()
{
	int c1 = Read();
	int c2 = Read();
	int c3 = Read();
	int c4 = Read();
	int c5 = Read();
	int c6 = Read();
	int c7 = Read();
	int c8 = Read();
	return ((c1<<56) + (c2<<48) + (c3<<40) + (c4<<32) + (c5<<24) + (c6<<16) + (c7<<8) + c8);
	return 0;
}

char* CByteInputStream::ReadUtf()
{
	short iLen = ReadShort();
	short iSize = sizeof(char)*iLen + 1;
	char* pUtf = (char*)malloc(iSize);
	memset(pUtf, 0, iSize);
	pUtf = Read(pUtf, iLen);
	return pUtf;
}