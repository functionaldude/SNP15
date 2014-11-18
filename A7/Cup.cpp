#include <iostream>
#include <unistd.h>
#include <sstream>
#include "Cup.h"

Cup::Cup(unsigned int cupID) :
    Log()

{
  std::stringstream sstream("");
  sstream << "Cup " << cupID;
  name_ = sstream.str();
  setLogName(name_);
  log(" created.");

  cups_id_ = cupID;
  useCounter_ = 0;
}

const std::string& Cup::name() const
{
  return name_;
}

void Cup::use_cup()
{
  if (useCounter_ < 2)
    useCounter_++;
  log(" has been used ", useCounter_, " times");
}
void Cup::clean_cup()
{
  useCounter_ = 0;
  log(" has been cleaned");
}

bool Cup::canBeUsed()
{
  return useCounter_ < 2;
}

bool Cup::isDirty()
{
  return useCounter_ > 0;
}
