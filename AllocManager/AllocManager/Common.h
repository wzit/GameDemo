#ifndef __COMMON_H__
#define __COMMON_H__

typedef unsigned char uchar;
typedef unsigned int uint;

#ifndef IF_BREAK
#define IF_BREAK(FLAG)\
	if(FLAG) break;
#endif

#define TO_VOID_PTR(ptr) (void**)(ptr)

#endif // !__COMMON_H__
