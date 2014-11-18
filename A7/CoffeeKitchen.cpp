#include "A7.h"
#include "CoffeeKitchen.h" 

std::map<std::string, Person*> CoffeeKitchen::who_is_here_;

CoffeeKitchen* CoffeeKitchen::instance_;

// the singleton stuff. Sombody thought a global Kitchen just would not buy it...

CoffeeKitchen* CoffeeKitchen::instance()
{
  if (instance_ == NULL)
  {
    instance_ = new CoffeeKitchen(5, 10);
  }
  return instance_;
}

// Construct the Kitchen
CoffeeKitchen::CoffeeKitchen(unsigned int freeSpace, unsigned int numCups) :
    aWindow("Kitchen", 1, 5),
    capacity_(freeSpace),
    people_in_kitchen_(0),
    cupboard_(numCups, "Billy"),  // we need a cupboard that can store all cups requested
    dishwasher_((int) numCups / 2, "Spueli") // install a Dishwasher that can take about half of the cups

{
  log("Kitchen built.", freeSpace, " seats available.");

}
void CoffeeKitchen::upgrade(unsigned int freeSpace, unsigned int numCups)
{
  log("Upgrading Kitchen to ", freeSpace, " seats, ", numCups, " cups");
  capacity_ = freeSpace;
  dishwasher_.upgrade((int) numCups / 2);
  cupboard_.upgrade(numCups);
}

CoffeeKitchen::~CoffeeKitchen()
{
}

void CoffeeKitchen::showWhoIsHere()
{
  std::stringstream msgAddInfo, msgWho;
  std::map<std::string, Person*>::iterator it;
  msgAddInfo << who_is_here_.size() << " people are in the kitchen";
  addInfo(msgAddInfo.str());

  for (it = CoffeeKitchen::who_is_here_.begin(); it != CoffeeKitchen::who_is_here_.end(); ++it)
    msgWho << it->first << ", ";

  showMessage(msgWho.str());
}

bool CoffeeKitchen::findPerson(std::string mName)
{
  std::map<std::string, Employee*>::iterator it;

  return who_is_here_.find(mName) != who_is_here_.end();
}

bool CoffeeKitchen::enterKitchen(Person* who)
{
  bool in;
  log("Employee ", who->name(), " trying to enter kitchen");

  std::string myName = who->name();

  // check for bugs in software ;)
  if (isInKitchen(who))
  {
    log("Employee ", who->name(), " already is in the kitchen");
    return false;
  }

  // is there room? Or is it a Boss - who will always fit in (not clear why, but this is stated)
  if (not isFull() or who->isBoss())
  {
    people_in_kitchen_++;
    std::pair<std::map<std::string, Person*>::iterator, bool> rv;
    rv = CoffeeKitchen::who_is_here_.insert(std::pair<std::string, Person*>(who->name(), who));
    if (!rv.second)
      log(who->name(), " wanted to enter kitchen but insert failed");
    else
      log(who->name(), " entered kitchen ");
    in = true;

  }
  else
  {
    log(who->name(), " tried to enter the kitchen but it is full (");
    in = false;
  }
  showWhoIsHere();
  return in;
}

void CoffeeKitchen::leaveKitchen(Person* who)
{
  log(who->name(), "about to leave...");

  if (findPerson(who->name()))
  {
    people_in_kitchen_--;
    who_is_here_.erase(who->name());
    log("Employee ", who->name(), " left the kitchen ");
  }
  else
  {
    log("Employee ", who->name(), " wanted to leave the the kitchen but was not in there.");
  }
  showWhoIsHere();

}

bool CoffeeKitchen::isFull()
{
  return people_in_kitchen_ >= capacity_;
}

Dishwasher& CoffeeKitchen::dishwasher()
{
  return dishwasher_;
}

CoffeeMachine& CoffeeKitchen::coffeeMaker()
{
  return coffee_maker_;
}

Cupboard& CoffeeKitchen::cupboard()
{
  return cupboard_;
}

bool CoffeeKitchen::isInKitchen(Person* who)
{
  return who_is_here_.find(who->name()) != who_is_here_.end();
}
