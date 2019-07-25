
#include "CondVar.h"
//#include "mutex.h"
#include <stdexcept> //runtime
#include <pthread.h>
using namespace advcpp;


CondVar::CondVar(Mutex& _mtx)
: m_mtx(_mtx)
//, m_cond(PTHREAD_COND_INITIALIZER)
{
	int res = pthread_cond_init(&m_cond, NULL);//[EAGAIN] [ENOMEM] - no resources/memory - probably not need
	if (0 != res)
	{
	//	throw std::runtime_error("pthread_cond_init");//return res
	}
}



void CondVar::Signal()
{
	pthread_cond_signal(&m_cond);//no error
}

void CondVar::SignalAll()
{
	pthread_cond_broadcast(&m_cond); //no error
}
