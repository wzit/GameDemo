#ifndef _REF_H_
#define _REF_H_

class Ref
{
public:
	void retain();
	void release();
	Ref *autorelease();

protected:
	Ref();

private:
	unsigned int _referenceCount;

	friend class AutoreleasePool;
};

#endif // !_REF_H_
