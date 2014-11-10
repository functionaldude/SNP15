#ifndef CoffeeKitchen_H
#define CoffeeKitchen_H

#include "A7.h"
#include "Thread.h"
#include "Employee.h"
#include "Cup.h"
#include "Cupboard.h"
#include "Dishwasher.h"
#include "CoffeeMachine.h"
#include "aWindow.h"
#include "CoffeeKitchen.h"

class CoffeeKitchen : public aWindow
{
  public:

    CoffeeKitchen(unsigned int freeSpace, unsigned int numCups);
    void upgrade(unsigned int freeSpace, unsigned int numCups);
    virtual ~CoffeeKitchen();
    static std::map<std::string, Person*> who_is_here_;
    static CoffeeKitchen* instance();
    Dishwasher& dishwasher();
    CoffeeMachine& coffeeMaker();
    Cupboard& cupboard();

    bool isFull();
    bool enterKitchen(Person* who);
    void leaveKitchen(Person* who);
    bool isInKitchen(Person* who);
  protected:
  private:
    int capacity_;
    int people_in_kitchen_;
    void showWhoIsHere();
    bool findPerson(std::string mName);
    static CoffeeKitchen* instance_;
    Cupboard cupboard_;
    CoffeeMachine coffee_maker_;
    Dishwasher dishwasher_;
};

#endif // CoffeeMachCoffeeKitchen_Hine_H
