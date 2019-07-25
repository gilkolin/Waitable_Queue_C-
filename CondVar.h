#ifndef __CONDVAR_H__
#define __CONDVAR_H__

#include <pthread.h>
#include "uncopy.h"
#include <stdexcept>
#include <stdexcept> //runtime


#include "Mutex.h"
namespace advcpp{

class CondVar : UnCopyable
{
public:
	explicit CondVar(Mutex& _mtx/*const pthread_condattr_t attr = 0*/);
	~CondVar(){;}
	CondVar(const CondVar& _cond);
	CondVar& operator=(const CondVar& _cond);
	
	void Signal();
	void SignalAll();
	template <class P>void Wait(P _p);			//not get mutex, two threades can use another mutex
	
private:
	Mutex&			m_mtx;
	pthread_cond_t	m_cond;
};



class CondVarException :  public std::runtime_error
{
public:
	CondVarException(std::string msg):runtime_error(msg.c_str()){;};
};


}

#include "CondVar.hpp"
#endif
