#include "Cup.h"
#include "Cupboard.h"
#include "Boss.h"

Cupboard::Cupboard(unsigned int nCups, std::string name) :
    CupStorage(nCups, name), aWindow(name, 1, 7)

{

  log("Cupboard with a capacity of ", nCups, " cups assembled from 2 IKEA Boxes.");
  for (unsigned int i = 1; i <= nCups; i++)
    putCup(new Cup(i));

  showCupboardContent();
}

void Cupboard::upgrade(unsigned int nCups)
{
  unsigned int oldCap;

  log("Cupboard upgraded to ", nCups, " Cups");
  if (capacity_ < nCups)
  {
    oldCap = capacity_;
    capacity_ = nCups;
    for (unsigned int i = oldCap + 1; i <= nCups; i++)
      putCup(new Cup(i));
  }
  else if (capacity_ > nCups)
  {
    for (unsigned int i = capacity_; i > nCups; i--)
    {
      Cup* thisCup = getCup();
      delete thisCup;
    }
    capacity_ = nCups;

  }

}

Cupboard::~Cupboard()
{
  Cup* thisCup;
// free all cups that are still stored here
  while ((thisCup = getCup()) != NULL)
  {
    delete thisCup;
  }
}

void Cupboard::showCupboardContent()
{
  showMessage(getCupboardContent());
}

bool Cupboard::enoughCups()
{
  log("checking cups. Avail: ", getCupboardContent(), " must have ", Boss::bosses_.size());
  return nCleanCups() >= Boss::bosses_.size();
}

