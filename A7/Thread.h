#ifndef THREAD_H
#define THREAD_H
#include <string>
#include <pthread.h>
#include <map>

class Thread
{
  public:
    virtual const std::string& name();
    Thread(std::string threadname);
    virtual ~Thread();
    int join();
    void yield();
    std::string thread_status_;
    static std::map<pthread_t, Thread*> threads_;
    static std::string getCurrentThreadName();
    Thread* getCurrentThread();

  protected:
    friend void ThreadStartHack(Thread* thread);
    virtual void run() = 0;
    pthread_t tid_;
    std::string threadname_;
};

#endif // THREAD_H
