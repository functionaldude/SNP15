#ifndef DISHWASHER_H
#define DISHWASHER_H

#include <string>
#include <deque>
#include <pthread.h>
#include "Thread.h"
#include "aWindow.h"
#include "Person.h"
#include "CupStorage.h"

class Person;
class Dishwasher : public Thread, public CupStorage, public aWindow
{
  public:
    Dishwasher(unsigned int numcups, std::string name);
    void upgrade(unsigned int numcups);
    virtual ~Dishwasher();

    bool pressStartButton();
    void showCupboardContent();
    bool putCup(Cup* thisCup);

    bool isFinished();
    bool isRunning();
    void restart();

    void queueMe(Person* e);
    std::string statusText();

    //finish
    pthread_mutex_t finish_m;
    pthread_cond_t finish_cv;
  private:
    virtual void run();
    std::deque<Person*> queue_;

    bool running_;
    bool finished_;
    bool started_;
    bool usersWaiting();
    int usersWaiting_ = 0;

    //start
  pthread_mutex_t start_m;
  pthread_cond_t start_cv;
};

#endif // DISHWASHER_H
