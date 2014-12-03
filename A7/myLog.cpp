#include "myLog.h"
#include <iostream>
#include <vector>

Log::Log()
{

}

Log::Log(std::string name)
{
  name_ = "[" + name + "]";

}
Log::~Log()
{
}

void Log::setLogName(std::string name)
{
  name_ = "[" + name + "]";

}

void Log::writer()
{
  std::cout << std::endl;
}