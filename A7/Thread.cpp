#include "Thread.h"
#include "A7.h"
#include <map>
#include <pthread.h>
#include <iostream>

std::map<pthread_t, Thread*> Thread::threads_;

void ThreadStartHack(Thread* thread)
{
  while (!all_threads_created)
    ; // busy wait :(
  thread->run();
}
;

Thread::Thread(std::string threadname)
{
  threadname_ = threadname;
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
  pthread_yield();
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
