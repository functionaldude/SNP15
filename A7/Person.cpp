#include "Person.h"

Person::Person(std::string name, int EmployeeId) :
    Thread(name), aWindow(name, 0, EmployeeId), my_turn_at_the_dishwasher_(true)
{
  log("Employee hired ", EmployeeId);
  name_ = name;
}

Person::~Person()
{
}

const std::string& Person::name() const
{
  return name_;
}

void Person::showMessage(std::string _message)
{
  std::stringstream msg;
  msg << " (" << cups_consumed_ << " coffees)";

  aWindow::showMessage(_message + msg.str());
}

bool Person::hasNoCup()
{
  return myCup_ == NULL;
}

void Person::work()
{
  int worktime = MAXWORKINGTIME;
  log(" is working for ", worktime, " seconds.");
  showMessage("working");
  sleep(worktime);
  showMessage(" stopped working ");
}

bool Person::isBoss()
{
  return false;
}

void Person::waitInQueue()
{
  my_turn_at_the_dishwasher_ = false;
  while (!my_turn_at_the_dishwasher_)
    ; // busy wait :(
}

void Person::wakeup()
{
  my_turn_at_the_dishwasher_ = true;
}
