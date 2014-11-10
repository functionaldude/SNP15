#ifndef BOSS_H
#define BOSS_H

#include <vector>
#include <string>
#include "Thread.h"
#include "Person.h"

class Boss : public Person
{
  public:
    Boss(std::string name, int EmployeeId);
    virtual ~Boss();

    static std::vector<Boss*> bosses_;
    static void makeBossMap();

    const std::string& name() const;
    virtual bool isBoss();
  public:

    virtual void run();
    void waitForDishwasher(bool needCups);

};

#endif
