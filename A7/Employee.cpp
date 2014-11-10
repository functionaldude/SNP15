#include "Cup.h"
#include "Employee.h"
#include "CoffeeKitchen.h"

extern Window mainWindow;

std::vector<Employee*> Employee::employees_;

Employee::Employee(std::string name, int EmployeeId) :
    Person(name, EmployeeId)
{

}

Employee::~Employee()
{

}

void Employee::emptyDishwasher()
{

  log("emptying dishwasher. Status: ", CoffeeKitchen::instance()->dishwasher().statusText());
  if (CoffeeKitchen::instance()->dishwasher().isFinished())
  {
    // need to unload the dishwasher
    // make sure we are the one who have to do this
    Cup* thisCup;
    showMessage("about to move cups from the dishwasher to the cupboard");
    while ((thisCup = CoffeeKitchen::instance()->dishwasher().getCup()) != NULL)
    {
      CoffeeKitchen::instance()->cupboard().putCup(thisCup);
      // this takes some time....
      usleep(WAITINGTIME);
      if (CoffeeKitchen::instance()->coffeeMaker().isEmpty())
      {
        showMessage("refilling coffee machine");
        CoffeeKitchen::instance()->coffeeMaker().fillCoffee();
      }

    }
    showMessage(" was kind enough to empty the dishwasher...");
    // allow dishwasher to be used again
    CoffeeKitchen::instance()->dishwasher().restart();
  }

}

void Employee::run()
{
  log("Employee running");

  while (true)
  {

    work();

    // wanna drink coffee
    addInfo("trying to enter kitchen");
    if (!CoffeeKitchen::instance()->enterKitchen(this))
    {
      showMessage("is angry since the kitchen is full. Goes working again.");
      addInfo("failed entering kitchen");
    }
    else
    {
      addInfo("successfully entered kitchen");
      while (hasNoCup())
      {
        // got no cup, need to get one
        addInfo(" need a cup.");
        if (CoffeeKitchen::instance()->cupboard().enoughCups())
          myCup_ = CoffeeKitchen::instance()->cupboard().getCup();
        if (hasNoCup())
        {
          addInfo("Angry. Need a cup. No Cup.");
          // no cups --> need to try to start the diswasher in any case
          startAndWaitForDishwasher(true);

        }
        else
        {
          if (myCup_->isDirty())
          {
            addInfo("got dirty cup");
            log("found a dirty cup in the cupboard. These bosses.");
            putCupinDishwasher();
          }
          else
          {
            addInfo("got clean cup");
          }
        }
      }

      log("got cup. trying to make coffee.");
      do
      {
        // check if coffee-machine has beans
        if (CoffeeKitchen::instance()->coffeeMaker().isEmpty())
        {
          showMessage("refilling coffee machine");
          CoffeeKitchen::instance()->coffeeMaker().fillCoffee();
        }

      } while (CoffeeKitchen::instance()->coffeeMaker().makeCoffee(this) == 0);

      cups_consumed_++;
      showMessage("drinking coffee");
      addInfo("");
      usleep(COFFEEDRINKINGTIME);
      myCup_->use_cup();
      if (!myCup_->canBeUsed())
      {
        showMessage("Cup is too dirty, cannot be used again.");
        putCupinDishwasher();
      }
      else
      {
        showMessage("cup is empty. Cup can be used again.");
      }
      CoffeeKitchen::instance()->leaveKitchen(this);
      log("left kitchen");
    }
  }

}

void Employee::putCupinDishwasher()
{
  while (not CoffeeKitchen::instance()->dishwasher().putCup(myCup_))
  {
    addInfo("can't put my cup into the dishwasher");
    startAndWaitForDishwasher(false);
  }

  myCup_ = NULL;
}

void Employee::startAndWaitForDishwasher(bool needCups)
{
  Dishwasher& dw = CoffeeKitchen::instance()->dishwasher();

  if (dw.isEmpty())
  {
    log("not meaningful to start empty dishwasher");
    while (CoffeeKitchen::instance()->cupboard().nDirtyCups() > 0 and not dw.isFull() and not dw.isRunning())
    {
      // hej, there are dirty cups to clean in the cupboard!
      dw.putCup(CoffeeKitchen::instance()->cupboard().getDirtyCup());
    }

  };

  // now lets start the dishwasher

  // but only if it is not already running or finished and waiting for someone to take the cups out
  if (not dw.isRunning() and not dw.isFinished())
  {
    // we ony start it if its full or someone claims she needs a cup
    // in any case we are not starting an empty dishwasher
    if ((needCups or dw.isFull()) and not dw.isEmpty())
    {
      if (dw.pressStartButton())
      {
        log(" pressed startbutton ");
        log("waiting for dw to finish....");
        // we do not want to do busy wait here. so we let us block until the dw is done
        dw.queueMe(this);
        log(" about to empty dishwasher");
        if (dw.isFinished())
          emptyDishwasher();
      }
      else
      {
        addInfo("Error when starting Dishwasher");
        log("Error when starting Dishwasher");
        usleep(WAITINGTIME);
      }
    }
    else
    {
      addInfo("why can't I put a cup into the dishwasher?");
      usleep(WAITINGTIME);
    }
  }
  else
  {
    log("Dishwasher running, I guess ", dw.statusText(), " so I'm gonna wait");
    dw.queueMe(this);
  }

}

bool Employee::isBoss()
{
  return false;
}
