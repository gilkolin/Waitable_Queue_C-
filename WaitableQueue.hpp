#ifndef __WAITABLEQUEUE_HPP__
#define __WAITABLEQUEUE_HPP__

#include <pthread.h>
#include <queue>
#include "Mutex.h"
#include "CondVar.h"

#include "WaitableQueue.h"

namespace advcpp{




template <class T>
WaitableQueue<T>::WaitableQueue()
: m_cond(m_mtx)
{
}


template <class T>
void WaitableQueue<T>::Enqueue(const T& _t)
{
	{
		Locker guard(m_mtx);
		m_que.push(_t);
	}
	m_cond.Signal();
}


template <class T>
struct IsQueueEmpty
{
	IsQueueEmpty(WaitableQueue<T>& wq): m_waitableQueue(wq) {;}
	bool operator()(){return m_waitableQueue.Empty();};
	
	WaitableQueue<T>& m_waitableQueue;
};


template <class T>
void WaitableQueue<T>::Dequeue(T& _item)		//not return byValue - can't fail in return (need CTOR in main)
{
	
	Locker guard(m_mtx);

	m_cond.Wait(IsQueueEmpty<T>(*this));

	_item = m_que.front();
	m_que.pop();
}


template <class T>
T WaitableQueue<T>::Front() const
{
	Locker guard(const_cast<Mutex&>(m_mtx));
	return m_que.front();
}


template <class T>
T WaitableQueue<T>::Back() const
{
	Locker guard(const_cast<Mutex&>(m_mtx));
	return m_que.back();
}


template <class T>
bool WaitableQueue<T>::Empty() const
{
	Locker guard(const_cast<Mutex&>(m_mtx));
	return m_que.empty();
}


template <class T>
size_t WaitableQueue<T>::Size() const
{
	Locker guard(const_cast<Mutex&>(m_mtx));
	return m_que.size();
}

}
#endif


