#ifndef __WQUEUE_H__
#define __WQUEUE_H__

#include <pthread.h>
#include <queue>
#include "Mutex.h"
#include "CondVar.h"


namespace advcpp{

template <class T>
class WaitableQueue : UnCopyable
{
public:
	
	WaitableQueue();					//throw(MutexException, CondException)
	~WaitableQueue(){}
	
	void Enqueue(const T& _t);
	void Dequeue(T& item);
	void Pop();
	T Front() const;
	T Back() const;
	bool Empty() const;
	size_t Size() const;
	
private:
	size_t			m_counter;
	Mutex			m_mtx;		//uncopyble		//order is important
	CondVar			m_cond;		//uncopyble
	std::queue<T>	m_que;
};

}

#include "WaitableQueue.hpp"

#endif


