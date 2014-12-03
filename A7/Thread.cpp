#include "Thread.h"
#include "A7.h"
#include <map>
#include <pthread.h>
#include <iostream>

std::map<pthread_t, Thread*> Thread::threads_;

void ThreadStartHack(Thread* thread)
{
//  while (!all_threads_created)
//    ; // busy wait solved :)
  pthread_mutex_lock(&thread_m);
  while (!all_threads_created) {
    pthread_cond_wait(&thread_cv, &thread_m);
  }
  pthread_mutex_unlock(&thread_m);
  thread->run();
}

Thread::Thread(std::string threadname)
{
  threadname_ = threadname;
  pthread_mutex_lock(&start_lock);
  pthread_create(&tid_, 0, (void* (*)(void*)) &ThreadStartHack, this);
  Thread::threads_[tid_] = this;
  std::cout << "Createdn thread object " << threadname << " currently " << Thread::threads_.size() << " threads "
      << std::endl;
}

Thread::~Thread()
{
}

int Thread::join()
{
  return pthread_join(tid_, NULL);

}
void Thread::yield()
{
#ifdef __APPLE__
  pthread_yield_np();
#else
  pthread_yield();
#endif
}

std::string Thread::getCurrentThreadName()
{
  auto it = threads_.find(pthread_self());
  if (it != threads_.end())
  {
    return (it->second)->threadname_;
  }
  return "Thread not found";
}

Thread* Thread::getCurrentThread()
{
  auto it = threads_.find(pthread_self());
  if (it != threads_.end())
  {
    return it->second;
  }
  return NULL;
}

const std::string& Thread::name()
{
  return threadname_;
}
