#ifndef _CBYTE_INPUT_STREAM_
#define _CBYTE_INPUT_STREAM_


// UnPacket，从流中解包数据
class CByteInputStream
{
public:
	CByteInputStream();
	~CByteInputStream();
	
	static CByteInputStream* newL(const unsigned char* pData, int iSize);
	static CByteInputStream* newL(const unsigned char* pData, int iSize, int iOffset, int iLen);

private:
	void constructL(const unsigned char* pData, int iSize);
	void constructL(const unsigned char* pData, int iSize, int iOffset, int iLen);

	void DeleteAll();

public:
	//读一个字节
	int Read();
	//读一个字符串
	char* Read(const char* pData, int iSize);

	char ReadByte();
	short ReadShort();
	short ReadShortTGA();
	int ReadInt();
	long long ReadLong();
	char* ReadUtf();

private:
	unsigned char* m_pBuf;
	int m_iSize;
	int m_iPos;

};

#endif // _CBYTE_INPUT_STREAM_
