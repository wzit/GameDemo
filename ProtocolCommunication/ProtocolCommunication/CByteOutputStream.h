#ifndef _CBYTE_OUTPUT_STREAM_
#define _CBYTE_OUTPUT_STREAM_


/* 
* Packet����������������У�����������
*
* ֧�����ͣ�1�ֽڣ�char����2�ֽڣ�short����4�ֽڣ�int����8�ֽڣ�long long�����ַ�����char���飩
* 
* ԭ�����ܶ��ٸ��ֽڣ�����ֳ� N �� 1���ֽڴ�ŵ�������
* 
* Packet������� �� Unpacket�������˳�����һ��
*/
class CByteOutputStream
{
public:
	CByteOutputStream();
	~CByteOutputStream();

	unsigned char* ToArray();
	int GetSize(){return m_iCount;}

public:
	// д��һ���ֽ�
	void Write(int aByte);
	// д��һ���ڴ棨�ַ�����
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
