#ifndef __UNCOPY_H__
#define __UNCOPY_H__

namespace advcpp{

class UnCopyable
{
public:
	UnCopyable() {};
	~UnCopyable() {};
	
private:

	UnCopyable(const UnCopyable& _uncopy);
	UnCopyable& operator=(const UnCopyable& _uncopy);
	
};
}
#endif
