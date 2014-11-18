#ifndef Cups_H
#define Cups_H
#include "myLog.h"

#include <string>

class Cup : public Log
{
  public:
    virtual const std::string& name() const;
    Cup(unsigned int CupID);
    void use_cup();
    void clean_cup();
    bool canBeUsed();
    bool isDirty();

  private:
    int cups_id_;
    int useCounter_;
    std::string name_;
};

#endif // Cups
