#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include <stdexcept> //runtime
#include "uncopy.h"


namespace advcpp{

class Cond;		//=======can do include?

#define NOEXCEPT throw()

class Mutex : UnCopyable	//friend of Cond
{
public:
	Mutex();// throw(MutexException);
	~Mutex();// NOEXCEPT;
	
	void Lock();// throw(MutexException);
	void Unlock();// throw(MutexException);
	
	//friend template <class P>void Cond::Wait(P _p);		//make sure mutex class name didn't change
															//better to trust all class (now we break incapsulation - we transfer private member)
	
private:

	friend class CondVar;
	pthread_mutex_t& GetMutex();
private:
	pthread_mutex_t m_mutex;
	pthread_mutexattr_t m_attr;
};



class MutexException :  public std::runtime_error
{
public:
	MutexException(std::string msg):runtime_error(msg.c_str()){;};
};


//RAII
class Locker
{
public:
	Locker(Mutex& _m): m(_m) {m.Lock();};
	~Locker() {m.Unlock();};
private:
	Mutex& m;
};

}
#endif
