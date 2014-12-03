#include "Cup.h"
#include "Dishwasher.h"

extern Window mainWindow;

Dishwasher::Dishwasher(unsigned int numcups, std::string name) :
    Thread(name), CupStorage(numcups, name), aWindow(name, 1, 0)
{

  std::string cDWName = name;

  running_ = false;
  finished_ = false;
  started_ = false;

//  pthread_mutex_init(&start_m, NULL);
//  pthread_cond_init(&start_cv, NULL);
  start_m = PTHREAD_MUTEX_INITIALIZER;
  start_cv = PTHREAD_COND_INITIALIZER;
  finish_m = PTHREAD_MUTEX_INITIALIZER;
  finish_cv = PTHREAD_COND_INITIALIZER;
}
Dishwasher::~Dishwasher()
{

}
void Dishwasher::upgrade(unsigned int numcups)
{
  CupStorage::upgrade(numcups);
  capacity_ = numcups;
}

bool Dishwasher::pressStartButton()
{
  bool retval = true;
  if (running_)
  {
    addInfo("Can't press startbutton when running");
    log("Can't press startbutton when running");
    retval = false;
  }
  else if (started_)
  {
    addInfo("Can't press startbutton twice");
    log("Can't press startbutton twice");
    retval = false;

  }
  else if (finished_)
  {
    addInfo("Can't press startbutton while dishwasher contains clean dishes");
    log("Can't press startbutton while dishwasher contains clean dishes");
    retval = false;
  }
  else
  {
    pthread_mutex_lock(&start_m);
    started_ = true;
    pthread_cond_signal(&start_cv);
    pthread_mutex_unlock(&start_m);
    log("someone pressed the startbutton");
  }

  return retval;

}

void Dishwasher::queueMe(Person* e)
{
  int me;
  log("Wait Until Dishwasher done, currently: ", statusText(), " for ", e->name());
  if (!isRunning())
  {
    return;
  }
  else
    usersWaiting_++;
  me = usersWaiting_;
  log("Waiting for Dishwasher. Waiter Nr. ", me, " ", e->name());
  if (e->isBoss())
    queue_.push_front(e);
  else
    queue_.push_back(e);
  e->waitInQueue();
  log("Dishwasher woke waiter Nr. ", me);
}

bool Dishwasher::putCup(Cup* thisCup)
{
  bool retval = false;
  if (isFinished())
  {
    log("can't put cup in dishwasher while it is not emptied");
  }
  else if (isRunning())
  {
    log("can't put cup in dishwasher while it is running");
  }
  else
  {
    CupStorage::putCup(thisCup);
    retval = true;
  }

  return retval;
}

bool Dishwasher::isFinished()
{
  return finished_;
}
bool Dishwasher::isRunning()
{
  return running_ || started_;
}
void Dishwasher::restart()
{
  finished_ = false;
}

void Dishwasher::run()
{
  while (1)
  {
    // we have to wait for the startbutton to be pressed
    showMessage("Dishwasher waits for button to be pressedD");

//    while (not started_)
//      ; // busy wait solved :)
    pthread_mutex_lock(&start_m);
    while (not started_) {
      pthread_cond_wait(&start_cv, &start_m);
    }
    showMessage("Dishwasher starting");
    running_ = true;
    started_ = false;
    pthread_mutex_unlock(&start_m);
    if (isEmpty())
    {
      log("The intelligent dishwasher denies working without any cups inside");
      running_ = false;
    }
    else
    {
      showMessage("Dishwasher running");
      if (not isFull())
      {
        addInfo("You could help the environment if you fill the dishwasher to full capacity before starting");
      }
      else
      {
        addInfo("Thank you for helping the environment by filling the dishwasher to full capacity before starting");

      }
      int downtime = DISHWASHERTIME;
      while (downtime--)
      {
        std::stringstream msg;
        msg << "Dishwasher running with " << cups_available() << " cups (" << downtime << ")";
        addInfo(msg.str());
        log(msg.str());
        usleep(DISHWASHERWAITINGTIMEUNIT);
      }

      showMessage("Dishwasher finished");
      addInfo("");

      // clean cups
      pthread_mutex_lock(&content_lock);
      while (dirtyCups_.size() > 0)
      {
        log("cleaned cup ", dirtyCups_.front()->name());
        dirtyCups_.front()->clean_cup();
        cleanCups_.push_back(dirtyCups_.front());
        dirtyCups_.pop_front();
      }
      pthread_mutex_unlock(&content_lock);
      showCupboardContent();
      running_ = false;
      pthread_mutex_lock(&finish_m);
      finished_ = true;
      pthread_cond_broadcast(&finish_cv);
      pthread_mutex_unlock(&finish_m);
      // wake up users in queue
      while (usersWaiting())
      {
        log("waking up Waiter Nr.", usersWaiting_, " (", queue_.front()->name(), ")");
        std::deque<Person*>::iterator it = queue_.begin();
        queue_.front()->wakeup();
        queue_.pop_front();

        usersWaiting_--;
      }

    }

  }

}
bool Dishwasher::usersWaiting()
{
  log(usersWaiting_, " Users are waiting on the dishwasher");
  return usersWaiting_ > 0;
}
std::string Dishwasher::statusText()
{
  if (running_)
    return "Dishwasher running";
  if (finished_)
    return "finished";
  if (started_)
    return "started";
  return "doing nothing";
}

void Dishwasher::showCupboardContent()
{
  showMessage(getCupboardContent());
}
