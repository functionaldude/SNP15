#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <vector>
#include <string>

#include "Person.h"

class Employee : public Person
{
  public:

    static std::vector<Employee*> employees_;

    Employee(std::string name, int EmployeeId);
    Employee(const Employee&);
    virtual ~Employee();

    virtual bool isBoss();
    virtual void run();
    void startAndWaitForDishwasher(bool needCups);
  private:
    void emptyDishwasher();
    void putCupinDishwasher();

};

#endif // EMPLOYEE_H
