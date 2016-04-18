#ifndef _CBYTE_OUTPUT_STREAM_
#define _CBYTE_OUTPUT_STREAM_


/* 
* Packet，将数据输出到流中，并将流发送
*
* 支持类型：1字节（char），2字节（short），4字节（int），8字节（long long），字符串（char数组）
* 
* 原理：不管多少个字节，都拆分成 N × 1个字节存放到缓冲区
* 
* Packet（封包） 和 Unpacket（解包）顺序必须一致
*/
class CByteOutputStream
{
public:
	CByteOutputStream();
	~CByteOutputStream();

	unsigned char* ToArray();
	int GetSize(){return m_iCount;}

public:
	// 写入一个字节
	void Write(int aByte);
	// 写入一块内存（字符串）
	void Write(const unsigned char* pData, int iSize, int iOffset, int iLen);

	void WriteByte(char aByte);
	void WriteShort(short aShort);
	void WriteInt(int aInt);
	void WriteLong(long long aLong);
	void WriteUtf8(const char* pUtf8);

private:
	void Reset();
	void DeleteAll();
	void ArrayCopy(const unsigned char* pSrc, int iSrcSize, int iSrcPos, unsigned char* pDest, int iDestSize, int iDestPos, int iCopyLen);

private:
	unsigned char* m_pBuf;
	short m_iBufLen;
	int m_iCount;
};

#endif // _CBYTE_OUTPUT_STREAM_
