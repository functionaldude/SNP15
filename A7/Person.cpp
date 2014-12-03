#include "Person.h"

Person::Person(std::string name, int EmployeeId) :
    Thread(name), aWindow(name, 0, EmployeeId), my_turn_at_the_dishwasher_(true)
{
  log("Employee hired ", EmployeeId);
  name_ = name;
//  pthread_mutex_init(&queue_m, NULL);
//  pthread_cond_init(&queue_cv, NULL);
  queue_m = PTHREAD_MUTEX_INITIALIZER;
  queue_cv = PTHREAD_COND_INITIALIZER;
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
  pthread_mutex_lock(&queue_m);
  my_turn_at_the_dishwasher_ = false;
//  while (!my_turn_at_the_dishwasher_)
//    ; // busy wait solved :)
  while (!my_turn_at_the_dishwasher_) {
    pthread_cond_wait(&queue_cv, &queue_m);
  }
  pthread_mutex_unlock(&queue_m);

}

void Person::wakeup()
{
  pthread_mutex_lock(&queue_m);
  my_turn_at_the_dishwasher_ = true;
  pthread_cond_signal(&queue_cv);
  pthread_mutex_unlock(&queue_m);
}
