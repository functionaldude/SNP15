#include "CupStorage.h"
#include "aWindow.h"
#include "myLog.h"

CupStorage::CupStorage(int initCapacity, std::string name) :
    my_logger(name), csname_(name), capacity_(initCapacity), ncleanCups_(0)
{
  content_lock = PTHREAD_MUTEX_INITIALIZER;
}

CupStorage::~CupStorage()
{
}

unsigned int CupStorage::cups_available()
{
  return cleanCups_.size() + dirtyCups_.size();
}

bool CupStorage::isEmpty()
{
  return cups_available() == 0;
}

bool CupStorage::isFull()
{
  return cups_available() == capacity_;
}

void CupStorage::upgrade(unsigned int numcups)
{
  capacity_ = numcups;
}

unsigned int CupStorage::nCleanCups()
{
  return cleanCups_.size();
}
unsigned int CupStorage::nDirtyCups()
{
  return dirtyCups_.size();
}

std::string CupStorage::getCupboardContent()
{
  pthread_mutex_lock(&content_lock);
  msg_.str(std::string());

  if (isEmpty())
    msg_ << csname() << " empty. ";
  else if (isFull())
    msg_ << csname() << "  full (" << capacity_ << " cups). ";
  else
    msg_ << csname() << " contains " << cups_available() << " cups. ";
  msg_ << nCleanCups() << " clean " << nDirtyCups() << " dirty ";
  my_logger.log(msg_.str());
  pthread_mutex_unlock(&content_lock);
  return msg_.str();
}

Cup* CupStorage::getCleanCup()
{
  my_logger.log("need clean cup. Let's Check: ", getCupboardContent());
  return getCup(cleanCups_);
}
Cup* CupStorage::getDirtyCup()
{
  my_logger.log("need dirty cup. Let's Check: ", getCupboardContent());
  return getCup(dirtyCups_);
}

Cup* CupStorage::getCup(std::list<Cup*>& list)
{
  Cup* thisCup;

  if (list.size() > 0)
  {
    thisCup = list.front();
    list.pop_front();
    my_logger.log("Clean cup ", thisCup->name(), " taken");
    showCupboardContent();
  }
  else
  {
    thisCup = NULL;
    my_logger.log("Sorry. No Cups");

  }
  //showCupboardContent();
  return thisCup;
}
Cup* CupStorage::getCup()
{
  Cup* thisCup;
  thisCup = getCleanCup();
  if (thisCup == NULL)
    thisCup = getDirtyCup();

  return thisCup;
}

bool CupStorage::putCup(Cup* thisCup)
{
  bool retval = false;

  if (isFull())
  { // we are full already
    my_logger.log("trying to load ", thisCup->name(), " into the full storage.");
  }
  else
  {
    pthread_mutex_lock(&content_lock);
    if (thisCup->isDirty())
      dirtyCups_.push_back(thisCup);
    else
      cleanCups_.push_back(thisCup);
    pthread_mutex_unlock(&content_lock);

    my_logger.log("Cup ", thisCup->name(), " put in");
    retval = true;
  }
  showCupboardContent();
  return retval;
}

const std::string& CupStorage::csname() const
{
  return csname_;
}
