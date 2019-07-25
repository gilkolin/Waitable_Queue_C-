#include <iostream>
#include <pthread.h>
#include "CondVar.h"
#include "uncopy.h"
#include "Mutex.h"
#include <exception>
#include <stdexcept> //runtime
#include <cassert>
using namespace advcpp;

Mutex::Mutex()// throw(MutexException)
{
	pthread_mutexattr_init(&m_attr);
	pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
	
	int res = pthread_mutex_init(&m_mutex, &m_attr);	//second argument
	if (0 != res)
	{
		throw MutexException("pthread_mutex_init");// errno
	}
}

Mutex::~Mutex()// NOEXCEPT
{
	int res = pthread_mutex_destroy(&m_mutex);
	assert(0 == res);
	
}

void Mutex::Lock() //throw(MutexException)
{
	int res = pthread_mutex_lock(&m_mutex);
	if (0 != res)
	{
		throw MutexException("pthread_mutex_lock");// errno
	}
}

void Mutex::Unlock()// throw(MutexException)
{
	int res = pthread_mutex_unlock(&m_mutex);
	if (0 != res)
	{
		throw MutexException("pthread_mutex_unlock");// errno
	}
	 
}

pthread_mutex_t& Mutex::GetMutex()
{
	return m_mutex;
}
