#ifndef __CONDVAR_HPP__
#define __CONDVAR_HPP__

#include <pthread.h>
#include <stdexcept>

#include "uncopy.h"
#include "Mutex.h"
#include "CondVar.h"

namespace advcpp{

template <class P>
void CondVar::Wait(P _p)
{
	while (_p())
	{
		int res = pthread_cond_wait(&m_cond, &m_mtx.GetMutex());
		if (0 != res)
		{
			throw std::runtime_error("pthread_cond_wait");//return res
		}
	}
}

}
#endif
