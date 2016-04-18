#include "CByteOutputStream.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

CByteOutputStream::CByteOutputStream():m_iBufLen(32)
{
	Reset();
	m_pBuf = (unsigned char*)malloc(sizeof(char) * m_iBufLen);
	memset(m_pBuf, '0', m_iBufLen);
}

CByteOutputStream::~CByteOutputStream()
{
	DeleteAll();
}

void CByteOutputStream::Reset()
{
	m_iCount = 0;
}

void CByteOutputStream::DeleteAll()
{
	if (m_pBuf)
	{
		delete m_pBuf;
	}
	m_pBuf = nullptr;
}


void CByteOutputStream::ArrayCopy(const unsigned char* pSrc, int iSrcSize, int iSrcPos, unsigned char* pDest, int iDestSize, int iDestPos, int iCopyLen)
{
	if (!pSrc || !pDest)
	{
		return;
	}
	for (int i=0; i<iCopyLen; i++)
	{
		if (iSrcPos>=iSrcSize || iDestPos>=iDestSize)
		{
			break;
		}
		pDest[iDestPos++] = pSrc[iSrcPos++];
	}
}

unsigned char* CByteOutputStream::ToArray()
{
	return m_pBuf;
}

void CByteOutputStream::Write(int aByte)
{
	int newcount = m_iCount + 1;
	if (newcount > m_iBufLen)
	{
		m_iBufLen = m_iBufLen << 1;
		unsigned char* pNewBuf = (unsigned char*)malloc(sizeof(char) * m_iBufLen);
		ArrayCopy(m_pBuf, m_iCount, 0, pNewBuf, m_iBufLen, 0, m_iCount);
		DeleteAll();
		m_pBuf = pNewBuf;
	}
	m_pBuf[m_iCount] = (unsigned char)aByte;
	m_iCount = newcount;
}

void CByteOutputStream::Write(const unsigned char* pData, int iSize, int iOffset, int iLen)
{
	int newcount = m_iCount + iLen;
	if (newcount > m_iBufLen)
	{
		m_iBufLen = m_iBufLen << 1;
		unsigned char* pNewBuf = (unsigned char*)malloc(sizeof(char) * m_iBufLen);
		ArrayCopy(m_pBuf, m_iCount, 0, pNewBuf, m_iBufLen, 0, m_iCount);
		DeleteAll();
		m_pBuf = pNewBuf;
	}
	ArrayCopy(pData, iSize, iOffset, m_pBuf, m_iBufLen, m_iCount, iLen);
	m_iCount = newcount;
}

void CByteOutputStream::WriteByte(char aByte)
{
	Write(aByte);
}

void CByteOutputStream::WriteShort(short aShort)
{
	unsigned short val = (unsigned short)aShort;
	Write((val>>8) & 0xFF);
	Write((val>>0) & 0xFF);
}

void CByteOutputStream::WriteInt(int aInt)
{
	unsigned short val = (unsigned int)aInt;
	Write((val>>24) & 0xFF);
	Write((val>>16) & 0xFF);
	Write((val>> 8) & 0xFF);
	Write((val>> 0) & 0xFF);
}

void CByteOutputStream::WriteLong(long long aLong)
{
	unsigned long long val = (unsigned long long)aLong;
	Write((val>>56) & 0xFF);
	Write((val>>48) & 0xFF);
	Write((val>>40) & 0xFF);
	Write((val>>32) & 0xFF);
	Write((val>>24) & 0xFF);
	Write((val>>16) & 0xFF);
	Write((val>> 8) & 0xFF);
	Write((val>> 0) & 0xFF);
	/*
	Write((unsigned char)(val>>56));
	Write((unsigned char)(val>>48));
	Write((unsigned char)(val>>40));
	Write((unsigned char)(val>>32));
	Write((unsigned char)(val>>24));
	Write((unsigned char)(val>>16));
	Write((unsigned char)(val>> 8));
	Write((unsigned char)(val>> 0));
	*/
}

/* 
* 往流中写入utf8字符串，写入格式：DataLen 和 pData
*
*	DataLen：长度，short类型
*	pData：字符串指针
*/
void CByteOutputStream::WriteUtf8(const char* pUtf8)
{
	unsigned short iLen = strlen(pUtf8);
	if (iLen<=0)
		return;
	WriteShort(iLen);
	Write((unsigned char*)pUtf8, iLen, 0, iLen);
}

