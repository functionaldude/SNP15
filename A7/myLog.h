#ifndef LOG_H
#define LOG_H

#include "A7.h"
#include <string>
#include <iostream>
#include <sstream>
#include <pthread.h>

// Logging Class. TODO: Ensure that std::cout-calls are synchronized

class Log
{
  public:
    template<typename Arg, typename ... Args>
    void log(Arg p1, Args ... args)
    {
      pthread_mutex_lock(&cout_lock);
      writer(p1, args...);
      pthread_mutex_unlock(&cout_lock);
    };

    template<typename Arg, typename ... Args>
    void writer(Arg p1, Args ... args)
    {
      std::cout << p1;
      writer(args...);
    };
    void writer();

    Log(std::string name);
    Log();
    virtual ~Log();
    void setLogName(std::string);
  private:
    std::string name_;
    static bool initialized_;
};

#endif
