#ifndef PERSON_H
#define PERSON_H
#include "Thread.h"
#include "aWindow.h"

class Cup;
class Employee;
class Person : public Thread, public aWindow
{
    friend Employee;
  public:
    Person(std::string name, int EmployeeId);
    virtual ~Person();
    virtual bool isBoss();
    void waitInQueue();
    void wakeup();
    const std::string& name() const;

    void start();
    void showMessage(std::string _message);
    void work();
  protected:

    std::string name_;
    int cups_consumed_ = 0;
    Cup* myCup_ = NULL;
    bool hasNoCup();
    bool my_turn_at_the_dishwasher_;

};

#endif // PERSON_H
