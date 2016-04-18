#include <iostream>

void printfBinary(int val, int bit)
{
	unsigned int index = 0x80000000;
	int byte = bit * 8;
	switch (byte)
	{
	case 8:
		index = 0x80;
		break;
	case 16:
		index = 0x8000;
		break;
	case 32:
		index = 0x80000000;
		break;
	}

	while (index > 0)
	{
		putchar(val & index ? '1' : '0');
		index >>= 1;
	}
	printf("\n");
}

int main(void)
{
	char c = 0;
	char cc = '0';
	char ccc = '\0';
	printf("c = %d\n", c);
	printf("c = %c\n", c);
	printf("cc = %d\n", cc);
	printf("cc = %c\n", cc);
	printf("ccc = %d\n", ccc);	
	printf("ccc = %c\n", ccc);

	short sho = 2;
	char s[5] = {};
	memset(s, 0, 5);
	s[0] = (unsigned char)((sho>>8) & 0xFF);
	s[1] = (unsigned char)((sho>>0) & 0xFF);
	for (int i=0; i<5; i++)
	{
		printf("%d\n", s[i]);
		printf("%c\n", s[i]);
	}

	int i0 = 0;
	char c0 = 48;
	printf("i0 = %c\n", i0);
	printf("i0 = %d\n", i0);
	printf("c0 = %c\n", c0);
	printf("c0 = %d\n", c0);

	system("pause");
	return 0;
}