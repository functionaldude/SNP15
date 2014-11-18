#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H

#include <string>
#include "Thread.h"
#include "aWindow.h"

class Person;

class CoffeeMachine : public Thread, public aWindow
{
  public:
    const std::string& name() const;

    CoffeeMachine();
    virtual ~CoffeeMachine();

    void fillCoffee();
    int makeCoffee(Person* who);

    void showStatus();
    bool isEmpty();

  private:
    int portions_;
    virtual void run();
    int produceCoffee();
    int coffeeMade_ = 0;
    bool BossIsWaiting_;
    std::string name_;

};

#endif // CoffeeMachine_H
