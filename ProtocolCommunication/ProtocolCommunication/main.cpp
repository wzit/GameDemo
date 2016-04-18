#include <iostream>
#include "CByteOutputStream.h"
#include "CByteInputStream.h"

#define SAFE_DELETE(p)\
	delete p;\
	p = nullptr;

int main(void)
{
	CByteOutputStream* pOutStream = new CByteOutputStream();
	pOutStream->WriteByte('a');
	pOutStream->WriteShort(100);
	pOutStream->WriteInt(2000);
	pOutStream->WriteUtf8("hello");
	pOutStream->WriteLong(44444);
	pOutStream->WriteUtf8("world");
	pOutStream->WriteInt(3000);
	
	
	unsigned char* str = pOutStream->ToArray();
	int size = pOutStream->GetSize();
	CByteInputStream* pInStream = CByteInputStream::newL(str, size);

	
	char aByte = pInStream->ReadByte();
	short aShort = pInStream->ReadShort();
	int aInt = pInStream->ReadInt();
 	char* aStr = pInStream->ReadUtf();
 	long long aLong = pInStream->ReadLong();
 	char* aStr2 = pInStream->ReadUtf();
 	int aInt2 = pInStream->ReadInt();
	
	printf("aByte=%c\n", aByte);
	printf("aShort=%d\n", aShort);
	printf("aInt=%d\n", aInt);
	printf("aStr=%s\n", aStr);
	printf("aLong=%ld\n", aLong);
	printf("aStr2=%s\n", aStr2);
	printf("aInt2=%d\n", aInt2);

	SAFE_DELETE(aStr);
	SAFE_DELETE(aStr2);

	SAFE_DELETE(pOutStream);
	SAFE_DELETE(pInStream);

	system("pause");
}