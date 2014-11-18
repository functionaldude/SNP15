#ifndef CUPSTORAGE_H
#define CUPSTORAGE_H
#include "Cup.h"
#include <list>
#include "myLog.h"

class CupStorage
{
  public:
    CupStorage(int initCapacity, std::string name);
    ~CupStorage();
    Cup* getCup();
    Cup* getCleanCup();
    Cup* getDirtyCup();
    unsigned int cups_available();
    bool isEmpty();
    bool isFull();
    virtual void showCupboardContent() = 0;
    std::string getCupboardContent();
    void upgrade(unsigned int numcups);
    bool putCup(Cup*  thisCup);
    unsigned int nCleanCups();
    unsigned int nDirtyCups();
    const std::string& csname() const;
  protected:
    std::list<Cup*> dirtyCups_;
    std::list<Cup*> cleanCups_;
    Log my_logger;
    std::string csname_;
    unsigned int capacity_;
    unsigned int ncleanCups_;
    std::stringstream msg_;
    Cup* getCup(std::list<Cup*>& list);
};

#endif // CUPSTORAGE_H
