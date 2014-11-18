#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <sstream>

// Logging Class. TODO: Ensure that std::cout-calls are synchronized

class Log
{
  public:
    template<typename Arg, typename ... Args>
    void log(Arg p1, Args ... args)
    {
      std::cout << p1;
      log(args...);
    };
    void log();

    Log(std::string name);
    Log();
    virtual ~Log();
    void setLogName(std::string);
  private:

    std::string name_;
    static bool initialized_;
};

#endif
