#include <iostream>
#include <unistd.h>
#include <sstream>
#include "Cup.h"
#include "CoffeeMachine.h"
#include "myLog.h"
#include "Person.h"

CoffeeMachine::CoffeeMachine() :
    Thread("CaPresso"), aWindow("CaPresso", 1, 3), name_("MrBlack")
{
  showMessage("ready to brew");
  log("CoffeeMachine installed.");
  BossIsWaiting_ = false;
  portions_ = 0;
}

CoffeeMachine::~CoffeeMachine()
{

}

bool CoffeeMachine::isEmpty()
{
  return portions_ == 0;
}

int CoffeeMachine::makeCoffee(Person* who)
{
  int coffeeMade;
  // you will need to make a difference between Bosses and Employees. Bosses always have priority
  if (who->isBoss())
  {
    coffeeMade = produceCoffee();
  }
  else
  {
    coffeeMade = produceCoffee();
  }
  return coffeeMade;

}

int CoffeeMachine::produceCoffee()
{

  int retval;

  if (portions_ > 0)
  {
    portions_--;
    log(" produced one cup of coffee");
    coffeeMade_++;
    retval = 1;
  }
  else
  {
    log(" is empty - cannot produce coffee");
    showMessage("empty");
    retval = 0;
  }

  showStatus();
  return retval;
}

void CoffeeMachine::showStatus()
{
  std::stringstream msg;
  msg << "brewed " << coffeeMade_ << " cups of coffee (" << portions_ << " to go)";
  showMessage(msg.str());
  log(msg.str());
}

void CoffeeMachine::fillCoffee()
{

  if (portions_ == 0)
  {
    portions_ = PORTIONS_PER_PACK;
    log("coffee machine full now");
  }
  else
  {
    log("refilling coffee machine that is not empty");
  }

  yield();

  showStatus();

  log("CoffeeMachine filled to deliver ", portions_, " cups of coffee ");
}

void CoffeeMachine::run()
{
  // TODO: implement
}

const std::string& CoffeeMachine::name() const
{
  return name_;
}

