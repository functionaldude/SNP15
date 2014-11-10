#include <iostream>
#include <unistd.h>
#include <stdlib.h> 
#include <vector>
#include "Cup.h"
#include "Cupboard.h"
#include "Boss.h"
#include "CoffeeKitchen.h"

std::vector<Boss*> Boss::bosses_;

Boss::Boss(std::string name, int EmployeeId) :
    Person(name, EmployeeId)
{
}

Boss::~Boss()
{
}

void Boss::run()
{
  // no cup yet
  myCup_ = NULL;
  log("started working");

  // daily business - but bosses behave slightly differently
  while (true)
  {
    work();
    // wanna drink coffee - enter kitchen. Should always work.
    CoffeeKitchen::instance()->enterKitchen(this);
    while (hasNoCup())
    { // got cup, can use it...
      myCup_ = CoffeeKitchen::instance()->cupboard().getCleanCup();
      if (hasNoCup())
      {
        // still has no cup. WTF is going on here.
        addInfo(" is angry since against all rules there is no (clean) cup in the cupboard.");
        while (CoffeeKitchen::instance()->dishwasher().isRunning())
        {
          showMessage("Angry. Dishwasher running. Waiting.");
          CoffeeKitchen::instance()->dishwasher().queueMe(this);
        }
      }
    }
    addInfo("got Cup");
    showMessage("wants Coffee");
    while (CoffeeKitchen::instance()->coffeeMaker().makeCoffee(this) == 0)
    {
      checkRedrawEvent();
      showMessage("No Coffee. Angry. Waiting");
      usleep(WAITINGTIME);
    }
    log(" got ", cups_consumed_, ". cup coffee.");
    cups_consumed_++;

    showMessage("got Coffee");
    myCup_->use_cup();
    while (!CoffeeKitchen::instance()->dishwasher().putCup(myCup_))
    {
      showMessage("dishwasher full. Putting dirty cup in cupboard.");
      if (CoffeeKitchen::instance()->cupboard().putCup(myCup_))
        break;
      showMessage("cupboard also full. Hmm....");
      sleep(1);

    }
    addInfo("");
    myCup_ = NULL;
    CoffeeKitchen::instance()->leaveKitchen(this);
  }

}

const std::string& Boss::name() const
{
  return name_;
}

void Boss::waitForDishwasher(bool needCups)
{
  CoffeeKitchen::instance()->dishwasher().queueMe(this);
}

bool Boss::isBoss()
{
  return true;
}
